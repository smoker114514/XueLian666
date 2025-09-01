#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include "database_manager.h"
#include "user_window.h"
#include "admin_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(bool isAdmin, QWidget *parent = nullptr);
    ~LoginWindow();

    // 重置表单
    void resetForm();

signals:
    // 返回主窗口信号
    void returnToMain();
    // 显示注册窗口信号
    void showRegisterWindow();

private slots:
    // 登录按钮点击
    void on_loginButton_clicked();

    // 取消按钮点击
    void on_cancelButton_clicked();

    // 注册按钮点击（仅用户登录窗口有）
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    bool isAdmin; // 区分是管理员登录还是用户登录
    QString currentUserId; // 当前登录用户ID
    UserWindow* userWindow;
    AdminWindow* adminWindow;
};
#endif // LOGIN_WINDOW_H

