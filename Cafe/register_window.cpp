#include "register_window.h"
#include "ui_register_window.h"
#include <QMessageBox>
#include <QPalette>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow) {
    ui->setupUi(this);
    this->setAutoFillBackground(true);

    // 2. 加载背景图片（资源路径需与你的.qrc配置一致）
    QPixmap bgPixmap(":/picture_source/1.jpeg");
    if (bgPixmap.isNull()) {
        qDebug() << "RegisterWindow错误：无法加载背景图！请检查资源路径:/picture_source/1.jpeg";
        return;
    }

    // 3. 缩放图片（忽略比例，拉伸填充窗口）
    QPixmap scaledPixmap = bgPixmap.scaled(
        this->size(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    // 4. 设置为窗口背景
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scaledPixmap));
    this->setPalette(palette);

    // 5. 窗口大小变化时，重新缩放背景图（保持自适应）
    connect(this, &RegisterWindow::resizeEvent, [this, bgPixmap](QResizeEvent *event) {
        Q_UNUSED(event);
        QPixmap scaledPixmap = bgPixmap.scaled(
            this->size(),
            Qt::KeepAspectRatio, // 可根据需求调整缩放模式（如与上方一致用Qt::IgnoreAspectRatio）
            Qt::SmoothTransformation
            );
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, QBrush(scaledPixmap));
        this->setPalette(palette);
    });
}

RegisterWindow::~RegisterWindow() {
    delete ui;
}

void RegisterWindow::on_registerButton_clicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirmPwd = ui->confirmEdit->text();
    QString name = ui->nameEdit->text();
    QString phone = ui->phoneEdit->text();

    // 简单验证
    if (username.isEmpty() || password.isEmpty() || confirmPwd.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空！");
        return;
    }

    if (password != confirmPwd) {
        QMessageBox::warning(this, "警告", "两次输入的密码不一致！");
        return;
    }

    if (DatabaseManager::getInstance().registerUser(username, password, name, phone)) {
        QMessageBox::information(this, "成功", "注册成功！");
        emit returnToMain();
        this->hide();
    } else {
        QMessageBox::warning(this, "失败", "注册失败！用户名可能已存在。");
    }
}

void RegisterWindow::on_cancelButton_clicked() {
    emit returnToMain();
    this->hide();
}
