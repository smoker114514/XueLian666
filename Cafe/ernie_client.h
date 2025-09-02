#ifndef ERNIE_CLIENT_H
#define ERNIE_CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class ErnieClient : public QObject {
    Q_OBJECT
public:
    explicit ErnieClient(QObject *parent = nullptr);
    // 设置API密钥（从百度智能云获取）
    void setApiKeys(const QString &apiKey, const QString &secretKey);
    // 发送对话请求
    void sendMessage(const QString &prompt);

signals:
    // 接收回复信号（成功时）
    void replyReceived(const QString &reply);
    // 错误信号（失败时）
    void errorOccurred(const QString &errorMsg);

private slots:
    // 处理令牌请求响应
    void onTokenReplyFinished(QNetworkReply *reply);
    // 处理对话请求响应
    void onChatReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString apiKey;       // 百度API Key
    QString secretKey;    // 百度Secret Key
    QString accessToken;  // 访问令牌（动态获取）
    QString currentPrompt;// 当前待发送的提问（等待令牌获取后发送）
};

#endif // ERNIE_CLIENT_H
