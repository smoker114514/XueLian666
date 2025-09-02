#include "deepseek_client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>
#include <QDebug>

DeepSeekClient::DeepSeekClient(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this)) {
    // 连接网络响应信号
    connect(manager, &QNetworkAccessManager::finished,
            this, &DeepSeekClient::onReplyFinished);
}

void DeepSeekClient::setApiKey(const QString &apiKey) {
    this->apiKey = apiKey;
}

void DeepSeekClient::sendMessage(const QString &prompt) {
    if (apiKey.isEmpty()) {
        emit errorOccurred("API密钥未设置");
        return;
    }

    // 关键修改：用列表初始化替代括号初始化，消除C++语法歧义
    QNetworkRequest request{QUrl(apiUrl)};  // 这里将()改为{}

    // 设置请求头（修正后可以正常调用成员函数）
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

    // 构建请求体（符合DeepSeek API格式）
    QJsonObject jsonBody;
    jsonBody["model"] = "deepseek-chat"; // 模型名称
    jsonBody["stream"] = false;         // 非流式响应

    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = prompt;
    messages.append(message);
    jsonBody["messages"] = messages;

    // 发送POST请求
    QByteArray data = QJsonDocument(jsonBody).toJson();
    manager->post(request, data);
}

void DeepSeekClient::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        // 网络错误处理
        emit errorOccurred(QString("网络错误: %1").arg(reply->errorString()));
        reply->deleteLater();
        return;
    }

    // 解析API响应
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    reply->deleteLater();

    if (jsonDoc.isNull()) {
        emit errorOccurred("响应解析失败");
        return;
    }

    // 提取回复内容（根据API文档调整字段）
    QJsonObject jsonObj = jsonDoc.object();
    if (jsonObj.contains("choices") && jsonObj["choices"].isArray()) {
        QJsonArray choices = jsonObj["choices"].toArray();
        if (!choices.isEmpty()) {
            QJsonObject choice = choices[0].toObject();
            QJsonObject message = choice["message"].toObject();
            QString content = message["content"].toString();
            emit replyReceived(content);
            return;
        }
    }

    // API返回错误信息
    if (jsonObj.contains("error")) {
        QJsonObject error = jsonObj["error"].toObject();
        emit errorOccurred(QString("API错误: %1").arg(error["message"].toString()));
    } else {
        emit errorOccurred("未知错误");
    }
}

