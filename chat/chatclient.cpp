#include "chatclient.h"
#include "./ui_chatclient.h" // 确保包含UI头文件
#include <QMessageBox>
#include <QDateTime>

ChatClient::ChatClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatClient)
{
    ui->setupUi(this); // 加载.ui布局，无需手动设置布局
    setWindowTitle("聊天客户端");

    // 【1. 删除所有手动创建UI的代码】
    // （删掉 chatHistory = new QTextEdit...、serverAddressInput = new...、布局相关代码）

    // 【2. 初始化UI状态（用.ui控件）】
    ui->textEditChat->setReadOnly(true); // 消息显示区只读
    ui->btnSend->setEnabled(false);      // 初始禁用发送按钮
    ui->lineEditIP->setText("127.0.0.1");// 默认IP
    ui->lineEditPort->setText("12345");  // 默认端口
    ui->labelStatus->setText("当前状态：未连接"); // 初始状态
    ui->labelStatus->setStyleSheet("color: red;"); // 红色未连接
    ui->labelIP->setText("服务器IP：");   // 标签文本
    ui->labelPort->setText("端口：");     // 标签文本
    ui->btnConnect->setText("连接服务器");// 按钮文本
    ui->btnSend->setText("发送");         // 按钮文本
    ui->btnClear->setText("清空消息");    // 按钮文本
    ui->lineEditInput->setPlaceholderText("请输入消息..."); // 输入提示

    // 【3. 初始化Socket】
    socket = new QTcpSocket(this);

    // 【4. 连接信号槽（关联.ui控件！）】
    connect(socket, &QTcpSocket::connected, this, &ChatClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ChatClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &ChatClient::onErrorOccurred);
    connect(ui->btnSend, &QPushButton::clicked, this, &ChatClient::onSendButtonClicked); // 关联ui按钮
    connect(ui->lineEditInput, &QLineEdit::returnPressed, this, &ChatClient::onSendButtonClicked); // 回车发送
    connect(ui->btnConnect, &QPushButton::clicked, this, &ChatClient::onConnectButtonClicked); // 关联ui连接按钮
    connect(ui->btnClear, &QPushButton::clicked, this, [=](){ ui->textEditChat->clear(); }); // 清空消息槽（匿名）
}

ChatClient::~ChatClient()
{
    socket->disconnectFromHost();
    delete ui;
    delete socket;
}

// 连接成功回调
void ChatClient::onConnected()
{
    ui->textEditChat->append("已连接到服务器！");
    ui->btnConnect->setText("断开连接");
    ui->btnSend->setEnabled(true);
    ui->labelStatus->setText("当前状态：已连接");
    ui->labelStatus->setStyleSheet("color: green;");
}

// 断开连接回调
void ChatClient::onDisconnected()
{
    ui->textEditChat->append("与服务器断开连接！");
    ui->btnConnect->setText("连接服务器");
    ui->btnSend->setEnabled(false);
    ui->labelStatus->setText("当前状态：未连接");
    ui->labelStatus->setStyleSheet("color: red;");
}

// 接收服务器消息
void ChatClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textEditChat->append(QString("[%1] 服务器：%2").arg(time).arg(QString(data)));
}

// 错误回调
void ChatClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    ui->textEditChat->append(QString("错误：%1").arg(socket->errorString()));
}

// 发送消息（ui->btnSend点击）
void ChatClient::onSendButtonClicked()
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        QMessageBox::warning(this, "错误", "未连接到服务器！");
        return;
    }

    QString msg = ui->lineEditInput->text().trimmed(); // 从ui输入框取消息
    if (msg.isEmpty()) return;

    socket->write(msg.toUtf8()); // 发送消息
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textEditChat->append(QString("[%1] 我：%2").arg(time).arg(msg)); // 本地显示
    ui->lineEditInput->clear(); // 清空输入框
}

// 连接/断开按钮点击（ui->btnConnect点击）
void ChatClient::onConnectButtonClicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // 断开连接
        socket->disconnectFromHost();
    } else {
        // 连接服务器：从ui取IP和端口（不再分割字符串！）
        QString ip = ui->lineEditIP->text().trimmed();
        quint16 port = ui->lineEditPort->text().toUInt(); // 直接取端口输入框

        if (ip.isEmpty() || port == 0) { // 端口无效（0是toUInt失败的返回）
            QMessageBox::warning(this, "错误", "IP或端口无效！");
            return;
        }

        ui->textEditChat->append(QString("正在连接 %1:%2...").arg(ip).arg(port));
        socket->connectToHost(QHostAddress(ip), port);
    }
}
