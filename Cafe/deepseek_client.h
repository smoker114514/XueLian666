#ifndef DEEPSEEK_CLIENT_H
#define DEEPSEEK_CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

class DeepSeekClient : public QObject {
    Q_OBJECT

public:
    explicit DeepSeekClient(QObject *parent = nullptr);
    void setApiKey(const QString &apiKey);
    void sendMessage(const QString &prompt);

signals:
    // 收到回复时触发
    void replyReceived(const QString &reply);
    // 发生错误时触发
    void errorOccurred(const QString &errorMsg);

private slots:
    // 处理网络响应
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager; // 网络请求管理器
    QString apiKey;                 // API密钥
    const QString apiUrl = "https://api.deepseek.com/chat/completions"; // 正确端点 // API端点
};

#endif // DEEPSEEK_CLIENT_H
