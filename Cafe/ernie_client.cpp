#include "ernie_client.h"
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ErnieClient::ErnieClient(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    // 关联网络请求完成信号
    connect(manager, &QNetworkAccessManager::finished,
            this, &ErnieClient::onTokenReplyFinished);
}

void ErnieClient::setApiKeys(const QString &apiKey, const QString &secretKey) {
    this->apiKey = apiKey;
    this->secretKey = secretKey;
}

void ErnieClient::sendMessage(const QString &prompt) {
    if (apiKey.isEmpty() || secretKey.isEmpty()) {
        emit errorOccurred("未设置API密钥，请检查配置");
        return;
    }

    // 如果令牌已获取，直接发送对话请求；否则先获取令牌
    if (accessToken.isEmpty()) {
        currentPrompt = prompt; // 暂存提问
        // 1. 第一步：获取访问令牌（Access Token）
        QUrl tokenUrl("https://aip.baidubce.com/oauth/2.0/token");
        QUrlQuery query;
        query.addQueryItem("grant_type", "client_credentials");
        query.addQueryItem("client_id", apiKey);       // 替换为你的API Key
        query.addQueryItem("client_secret", secretKey); // 替换为你的Secret Key
        tokenUrl.setQuery(query);

        QNetworkRequest request(tokenUrl);
        manager->get(request); // 发送GET请求获取令牌
    } else {
        // 2. 第二步：使用令牌发送对话请求
        QUrl chatUrl(QString("https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro?access_token=%1")
                         .arg(accessToken));

        QNetworkRequest request(chatUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // 构建请求体（参考文心一言API文档）
        QJsonObject json;
        QJsonArray messages;
        messages.append(QJsonObject{{"role", "user"}, {"content", prompt}});
        json["messages"] = messages;
        json["temperature"] = 0.7; // 温度参数（0~1，值越高回复越灵活）

        QByteArray data = QJsonDocument(json).toJson();
        // 发送POST请求时，重新关联finished信号到对话响应处理函数
        connect(manager, &QNetworkAccessManager::finished,
                this, &ErnieClient::onChatReplyFinished);
        manager->post(request, data);
    }
}

void ErnieClient::onTokenReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred("获取令牌失败：" + reply->errorString());
        reply->deleteLater();
        return;
    }

    // 解析令牌响应
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    if (json.contains("access_token")) {
        accessToken = json["access_token"].toString();
        qDebug() << "令牌获取成功，有效期：" << json["expires_in"].toInt() << "秒";
        // 令牌获取后，发送之前暂存的提问
        sendMessage(currentPrompt);
    } else {
        emit errorOccurred("解析令牌失败：" + data);
    }
    reply->deleteLater();
}

void ErnieClient::onChatReplyFinished(QNetworkReply *reply) {
    // 恢复信号关联（下次获取令牌时使用）
    disconnect(manager, &QNetworkAccessManager::finished,
               this, &ErnieClient::onChatReplyFinished);

    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred("对话请求失败：" + reply->errorString());
        reply->deleteLater();
        return;
    }

    // 解析对话响应
    QByteArray data = reply->readAll();
    QJsonObject json = QJsonDocument::fromJson(data).object();
    if (json.contains("result")) {
        // 提取回复内容（文心一言的回复在"result"字段）
        QString replyContent = json["result"].toString();
        emit replyReceived(replyContent);
    } else {
        emit errorOccurred("解析回复失败：" + data);
    }
    reply->deleteLater();
}
