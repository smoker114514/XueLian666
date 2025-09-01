#include "main_window.h"
#include "ui_main_window.h"
#include <QPalette>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setAutoFillBackground(true);

    // 2. 加载背景图片（资源路径需与.qrc配置一致）
    QPixmap bgPixmap(":/picture_source/3.png");
    if (bgPixmap.isNull()) {
        qDebug() << "MainWindow错误：无法加载背景图！";
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
    connect(this, &MainWindow::resizeEvent, [this, bgPixmap](QResizeEvent *event) {
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

    // 初始化子窗口
    userLoginWindow = new LoginWindow(false);  // 无父对象
    adminLoginWindow = new LoginWindow(true);
    registerWindow = new RegisterWindow();

    // 连接返回信号
    connect(userLoginWindow, &LoginWindow::returnToMain, this, &MainWindow::on_returnToMain);
    connect(adminLoginWindow, &LoginWindow::returnToMain, this, &MainWindow::on_returnToMain);
    connect(registerWindow, &RegisterWindow::returnToMain, this, &MainWindow::on_returnToMain);

    // 连接注册窗口打开信号
    connect(userLoginWindow, &LoginWindow::showRegisterWindow, [this]() {
        this->hide();
        registerWindow->show();
    });
    QTimer* deductTimer = new QTimer(this); // 父对象设为this，自动管理内存
    // 连接定时器到扣费函数，确保在主线程执行
    connect(deductTimer, &QTimer::timeout, this, []() {
        DatabaseManager::getInstance().autoDeductFees();
        // 扣费后可发送信号通知用户窗口刷新余额（可选）
        // 例如：if (userWindow) userWindow->refreshUserInfo();
    });
    deductTimer->start(60000);
}

MainWindow::~MainWindow() {
    delete ui;

}

void MainWindow::on_userLoginButton_clicked() {
    this->hide();
    userLoginWindow->resetForm();
    userLoginWindow->show();
}

void MainWindow::on_adminLoginButton_clicked() {
    this->hide();
    adminLoginWindow->resetForm();
    adminLoginWindow->show();
}

void MainWindow::on_returnToMain() {
    this->show();
}
