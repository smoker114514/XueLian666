#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include "ui_chatclient.h" // 仅保留UI头文件

QT_BEGIN_NAMESPACE
namespace Ui { class ChatClient; }
QT_END_NAMESPACE

class ChatClient : public QWidget
{
    Q_OBJECT

public:
    ChatClient(QWidget *parent = nullptr);
    ~ChatClient();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onSendButtonClicked(); // 对应ui->btnSend
    void onConnectButtonClicked(); // 对应ui->btnConnect

private:
    Ui::ChatClient *ui; // 仅保留UI指针
    QTcpSocket *socket; // 仅保留网络Socket
    // 【删除以下手动UI成员】
    // QTextEdit *chatHistory;
    // QLineEdit *messageInput;
    // QLineEdit *serverAddressInput;
    // QPushButton *sendButton;
    // QPushButton *connectButton;
};
#endif // CHATCLIENT_H
