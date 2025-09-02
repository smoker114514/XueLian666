#include "chat_window.h"
#include "ui_chat_window.h"
#include "deepseek_client.h"
#include <QDateTime>
#include <QScrollBar>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
    , deepSeekClient(new DeepSeekClient(this)) {
    ui->setupUi(this);
    setWindowTitle("智能客服");
    initUI();
    initConnections();
    deepSeekClient->setApiKey("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::initUI() {
    // 设置背景图片（与其他窗口保持一致）
    setAutoFillBackground(true);
    QPixmap bgPixmap(":/picture_source/1.jpeg");
    if (bgPixmap.isNull()) {
        qDebug() << "ChatWindow错误：无法加载背景图！";
    } else {
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, QBrush(
                                               bgPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                                               ));
        setPalette(palette);
    }

    // 初始化聊天区域
    ui->chatDisplay->setReadOnly(true);
    ui->chatDisplay->setStyleSheet("background-color: rgba(255, 255, 255, 0.8);"
                                   "border-radius: 5px; padding: 8px;");
    ui->inputEdit->setStyleSheet("border-radius: 5px; padding: 5px;");

    // 隐藏滚动条但保留滚动功能
    ui->chatDisplay->verticalScrollBar()->setStyleSheet("QScrollBar {width: 0px;}");
}

void ChatWindow::initConnections() {
    // 连接DeepSeek客户端信号
    connect(deepSeekClient, &DeepSeekClient::replyReceived,
            this, &ChatWindow::onReplyReceived);
    connect(deepSeekClient, &DeepSeekClient::errorOccurred,
            this, &ChatWindow::onErrorOccurred);

    // 窗口大小变化时重绘背景
    connect(this, &ChatWindow::resizeEvent, [this](QResizeEvent *event) {
        Q_UNUSED(event);
        QPixmap bgPixmap(":/picture_source/1.jpeg");
        if (!bgPixmap.isNull()) {
            QPalette palette = this->palette();
            palette.setBrush(QPalette::Window, QBrush(
                                                   bgPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                                                   ));
            setPalette(palette);
        }
    });
}

void ChatWindow::setApiKey(const QString &apiKey) {
    deepSeekClient->setApiKey(apiKey);
}

void ChatWindow::setUserId(const QString &userId) {
    this->userId = userId;
    addSystemMessage(QString("欢迎使用智能客服！您的用户ID：%1").arg(userId));
}

void ChatWindow::addMessageToDisplay(const QString &sender, const QString &message, const QColor &color) {
    // 获取当前时间
    QString timeStr = QDateTime::currentDateTime().toString("[HH:mm:ss]");

    // 格式化消息
    ui->chatDisplay->setTextColor(color);
    ui->chatDisplay->append(QString("%1 %2：").arg(timeStr).arg(sender));
    ui->chatDisplay->setTextColor(Qt::black);
    ui->chatDisplay->append(message + "\n");

    // 自动滚动到底部
    QScrollBar *scrollBar = ui->chatDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void ChatWindow::addSystemMessage(const QString &message) {
    ui->chatDisplay->setTextColor(Qt::gray);
    ui->chatDisplay->append(QString("[系统消息] %1\n").arg(message));

    QScrollBar *scrollBar = ui->chatDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void ChatWindow::on_sendButton_clicked() {
    QString prompt = ui->inputEdit->toPlainText().trimmed();
    if (prompt.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入消息内容！");
        return;
    }

    // 显示用户消息
    addMessageToDisplay("您", prompt, Qt::blue);

    // 清空输入框
    ui->inputEdit->clear();

    // 发送请求到DeepSeek
    deepSeekClient->sendMessage(prompt);

    // 显示"正在输入"提示
    addSystemMessage("客服正在回复...");
}

void ChatWindow::onReplyReceived(const QString &reply) {
    // 移除"正在输入"提示
    QString currentText = ui->chatDisplay->toPlainText();
    currentText.remove(currentText.lastIndexOf("[系统消息] 客服正在回复...\n"),
                       QString("[系统消息] 客服正在回复...\n").length());
    ui->chatDisplay->setPlainText(currentText);

    // 显示客服回复
    addMessageToDisplay("智能客服", reply, Qt::green);
}

void ChatWindow::onErrorOccurred(const QString &errorMsg) {
    addSystemMessage(QString("错误：%1").arg(errorMsg));
}

void ChatWindow::on_backButton_clicked() {
    emit returnToUserWindow();
    this->hide();
}

void ChatWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // 显示时刷新一次背景（解决初始显示问题）
    QResizeEvent resizeEvent(size(), QSize());
    QCoreApplication::sendEvent(this, &resizeEvent);
}
