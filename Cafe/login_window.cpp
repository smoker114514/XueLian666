#include "login_window.h"
#include "ui_login_window.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

LoginWindow::LoginWindow(bool isAdmin, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    , isAdmin(isAdmin) {
    ui->setupUi(this);
    this->setAutoFillBackground(true);

    // 2. 加载背景图片（资源路径需与.qrc配置一致）
    QPixmap bgPixmap(":/picture_source/1.jpeg");
    if (bgPixmap.isNull()) {
        qDebug() << "LoginWindow错误：无法加载背景图！请检查资源路径:/picture_source/1.jpeg";
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
    connect(this, &LoginWindow::resizeEvent, [this, bgPixmap](QResizeEvent *event) {
        Q_UNUSED(event);
        QPixmap scaledPixmap = bgPixmap.scaled(
            this->size(),
            Qt::KeepAspectRatio, // 可根据需求调整缩放模式
            Qt::SmoothTransformation
            );
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, QBrush(scaledPixmap));
        this->setPalette(palette);
    });

    // 如果是管理员登录，隐藏注册按钮
    if (isAdmin) {
        ui->registerButton->hide();
    }

    userWindow = new UserWindow();
    adminWindow = new AdminWindow();

    // 连接用户窗口返回信号
    connect(userWindow, &UserWindow::returnToLogin, [this]() {
        userWindow->hide();
        this->show();
    });

    // 连接管理员窗口返回信号
    connect(adminWindow, &AdminWindow::returnToLogin, [this]() {
        adminWindow->hide();
        this->show();
    });
}

LoginWindow::~LoginWindow() {
    delete ui;
    delete userWindow;
    delete adminWindow;
}

void LoginWindow::resetForm() {
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
}

void LoginWindow::on_loginButton_clicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空！");
        return;
    }

    if (isAdmin) {
        // 管理员登录
        if (DatabaseManager::getInstance().loginAdmin(username, password)) {
            this->hide();
            adminWindow->refreshMachineStatus();
            adminWindow->show();
        } else {
            QMessageBox::warning(this, "登录失败", "管理员账号或密码错误！");
        }
    } else {
        // 用户登录
        QString userId;
        if (DatabaseManager::getInstance().loginUser(username, password, userId)) {
            if (userId.isEmpty()) {
                QMessageBox::warning(this, "错误", "获取用户ID失败！");
                return;
            }
            currentUserId = userId;
            this->hide();
            userWindow->setUserId(userId);

            userWindow->refreshUserInfo();
            userWindow->show();

        } else {
            QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    }
}

void LoginWindow::on_cancelButton_clicked() {
    emit returnToMain();
    this->hide();
}

void LoginWindow::on_registerButton_clicked() {
    emit showRegisterWindow();
    this->hide();
}
