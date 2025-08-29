#include "chatserver.h"
#include "ui_chatserver.h" // 确保包含UI头文件
#include <QMessageBox>
#include <QDateTime>

ChatServer::ChatServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatServer)
{
    ui->setupUi(this); // 加载.ui布局，删除手动布局代码
    setWindowTitle("聊天服务器");

    // 【1. 初始化.ui控件文本和状态】
    ui->lineEditPort->setText("12345");       // 默认端口
    ui->btnStart->setText("启动监听");         // 按钮文本
    ui->btnStop->setText("停止监听");         // 按钮文本
    ui->btnStop->setEnabled(false);           // 初始禁用停止按钮
    ui->btnServerSend->setText("发送");        // 发送按钮文本
    ui->btnClearLog->setText("清空日志");      // 清空按钮文本
    ui->labelStatus->setText("当前状态：未监听"); // 初始状态
    ui->labelStatus->setStyleSheet("color: red;"); // 红色未监听
    ui->labelPort->setText("监听端口：");      // 端口标签文本
    ui->labelClients->setText("已连接客户端：");// 客户端列表标签
    ui->labelLog->setText("消息日志：");       // 日志标签文本
    ui->textEditLog->setReadOnly(true);       // 日志区只读
    ui->lineEditServerInput->setPlaceholderText("输入消息发送给选中客户端..."); // 输入提示

    // 【2. 初始化服务器】
    server = new QTcpServer(this);

    // 【3. 连接信号槽（关联.ui控件！）】
    connect(server, &QTcpServer::newConnection, this, &ChatServer::onNewConnection);
    connect(ui->btnStart, &QPushButton::clicked, this, &ChatServer::onStartButtonClicked); // 启动监听
    connect(ui->btnStop, &QPushButton::clicked, this, &ChatServer::onStopButtonClicked);   // 停止监听
    connect(ui->btnServerSend, &QPushButton::clicked, this, &ChatServer::onSendButtonClicked); // 发送消息
    connect(ui->btnClearLog, &QPushButton::clicked, this, [=](){ ui->textEditLog->clear(); }); // 清空日志
}

ChatServer::~ChatServer()
{
    // 析构时清理资源
    server->close();
    qDeleteAll(clientSockets);
    delete ui;
    delete server;
}

// 启动监听（ui->btnStart点击）
void ChatServer::onStartButtonClicked()
{
    int port = ui->lineEditPort->text().toInt();
    if (port < 1 || port > 65535) {
        QMessageBox::warning(this, "错误", "端口号必须在 1-65535 之间！");
        return;
    }

    if (server->listen(QHostAddress::Any, port)) {
        ui->textEditLog->append(QString("[%1] 服务器启动成功，监听端口：%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(port));
        ui->labelStatus->setText(QString("当前状态：已监听（端口：%1）").arg(port));
        ui->labelStatus->setStyleSheet("color: green;");
        ui->btnStart->setEnabled(false);
        ui->btnStop->setEnabled(true);
        ui->lineEditPort->setEnabled(false); // 监听中禁止改端口
    } else {
        ui->textEditLog->append(QString("[%1] 服务器启动失败：%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(server->errorString()));
        ui->labelStatus->setText("当前状态：监听失败");
        ui->labelStatus->setStyleSheet("color: red;");
    }
}

// 停止监听（ui->btnStop点击）
void ChatServer::onStopButtonClicked()
{
    server->close();
    qDeleteAll(clientSockets); // 断开所有客户端
    clientSockets.clear();
    ui->listWidgetClients->clear(); // 清空客户端列表

    ui->textEditLog->append(QString("[%1] 服务器已停止监听").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    ui->labelStatus->setText("当前状态：未监听");
    ui->labelStatus->setStyleSheet("color: red;");
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->lineEditPort->setEnabled(true);
    ui->btnServerSend->setEnabled(false); // 无客户端，禁用发送
}

// 新客户端连接
void ChatServer::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clientSockets.append(clientSocket); // 加入客户端列表

    // 显示客户端信息（IP:端口）
    QString clientInfo = QString("%1:%2").arg(clientSocket->peerAddress().toString()).arg(clientSocket->peerPort());
    ui->listWidgetClients->addItem(clientInfo);
    ui->textEditLog->append(QString("[%1] 新客户端连接：%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(clientInfo));

    // 关联客户端信号
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::handleClientDisconnect);
    connect(clientSocket, &QTcpSocket::errorOccurred, this, [=](){
        ui->textEditLog->append(QString("[%1] 客户端 %2 错误：%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(clientInfo).arg(clientSocket->errorString()));
    });

    ui->btnServerSend->setEnabled(true); // 有客户端，启用发送
}

// 接收客户端消息
void ChatServer::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    QString clientInfo = QString("%1:%2").arg(clientSocket->peerAddress().toString()).arg(clientSocket->peerPort());
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textEditLog->append(QString("[%1] 客户端 %2：%3").arg(time).arg(clientInfo).arg(QString(data)));
}

// 客户端断开连接
void ChatServer::handleClientDisconnect()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QString clientInfo = QString("%1:%2").arg(clientSocket->peerAddress().toString()).arg(clientSocket->peerPort());
    // 从列表和UI中移除
    clientSockets.removeOne(clientSocket);
    for (int i = 0; i < ui->listWidgetClients->count(); i++) {
        if (ui->listWidgetClients->item(i)->text() == clientInfo) {
            delete ui->listWidgetClients->takeItem(i);
            break;
        }
    }

    ui->textEditLog->append(QString("[%1] 客户端 %2 断开连接").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(clientInfo));
    clientSocket->deleteLater();

    // 无客户端时禁用发送
    if (clientSockets.isEmpty()) {
        ui->btnServerSend->setEnabled(false);
    }
}

// 发送消息给选中客户端（ui->btnServerSend点击）
void ChatServer::onSendButtonClicked()
{
    QListWidgetItem *selectedItem = ui->listWidgetClients->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "提示", "请先选中一个客户端！");
        return;
    }

    QString msg = ui->lineEditServerInput->text().trimmed();
    if (msg.isEmpty()) return;

    // 找到选中的客户端Socket
    QString targetClient = selectedItem->text();
    QTcpSocket *targetSocket = nullptr;
    foreach (QTcpSocket *socket, clientSockets) {
        QString clientInfo = QString("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        if (clientInfo == targetClient) {
            targetSocket = socket;
            break;
        }
    }

    if (targetSocket && targetSocket->state() == QAbstractSocket::ConnectedState) {
        targetSocket->write(msg.toUtf8());
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->textEditLog->append(QString("[%1] 发送给 %2：%3").arg(time).arg(targetClient).arg(msg));
        ui->lineEditServerInput->clear();
    } else {
        QMessageBox::critical(this, "错误", "选中的客户端已断开！");
    }
}
