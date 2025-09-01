#include "loginwindow.h"
#include "userwindow.h"
#include "adminwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

LoginWindow::LoginWindow(Database *db, QWidget *parent)
    : QWidget(parent), db(db)
{
    userWindow = nullptr;
    adminWindow = nullptr;
    setupUI();
    setWindowTitle("网吧管理系统 - 登录");
    resize(300, 250);
}

LoginWindow::~LoginWindow()
{
    if (userWindow) delete userWindow;
    if (adminWindow) delete adminWindow;
}

void LoginWindow::setupUI()
{
    // 创建控件
    QLabel *titleLabel = new QLabel("网吧管理系统");
    QFont font = titleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("请输入用户名");

    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("请输入密码");

    userRadio = new QRadioButton("用户登录");
    adminRadio = new QRadioButton("管理员登录");
    userRadio->setChecked(true);

    loginButton = new QPushButton("登录");
    registerButton = new QPushButton("注册");

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("用户名:", usernameEdit);
    formLayout->addRow("密码:", passwordEdit);
    mainLayout->addLayout(formLayout);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->addWidget(userRadio);
    radioLayout->addWidget(adminRadio);
    mainLayout->addLayout(radioLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);
    mainLayout->addLayout(buttonLayout);

    mainLayout->addStretch();

    // 连接信号槽
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
}

void LoginWindow::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空!");
        return;
    }

    bool isAdmin;
    int userId;

    if (db->loginUser(username, password, isAdmin, userId)) {
        // 检查登录类型是否匹配
        if ((userRadio->isChecked() && !isAdmin) || (adminRadio->isChecked() && isAdmin)) {
            if (isAdmin) {
                if (!adminWindow) {
                    adminWindow = new AdminWindow(db, this);
                }
                adminWindow->show();
            } else {
                if (!userWindow) {
                    userWindow = new UserWindow(db, userId, this);
                } else {
                    userWindow->setUserId(userId);
                }
                userWindow->show();
            }
            this->hide();
            usernameEdit->clear();
            passwordEdit->clear();
        } else {
            QMessageBox::warning(this, "登录失败", "登录类型不匹配!");
        }
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误!");
    }
}

void LoginWindow::onRegisterClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空!");
        return;
    }

    if (db->registerUser(username, password)) {
        QMessageBox::information(this, "注册成功", "用户注册成功，请登录!");
    } else {
        QMessageBox::warning(this, "注册失败", "用户名已存在或注册失败!");
    }
}
