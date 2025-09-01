#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDateTime>
#include "ui_chatserver.h" // 仅保留UI头文件

QT_BEGIN_NAMESPACE
namespace Ui { class ChatServer; }
QT_END_NAMESPACE

class ChatServer : public QWidget
{
    Q_OBJECT

public:
    ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

private slots:
    void onNewConnection();     // 新客户端连接
    void onReadyRead();         // 接收客户端消息
    void onSendButtonClicked(); // 发送消息（ui->btnServerSend点击）
    void onStartButtonClicked();// 启动监听（ui->btnStart点击）
    void onStopButtonClicked(); // 停止监听（ui->btnStop点击）
    void handleClientDisconnect(); // 客户端断开

private:
    Ui::ChatServer *ui;                 // 仅保留UI指针
    QTcpServer *server;                 // 服务器核心
    QList<QTcpSocket*> clientSockets;   // 存储所有客户端（支持多客户端）
    // 【删除以下手动UI成员】
    // QTextEdit *chatHistory;
    // QLineEdit *messageInput;
    // QPushButton *sendButton;
};
#endif // CHATSERVER_H
