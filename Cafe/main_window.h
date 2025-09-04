#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "login_window.h"
#include "register_window.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 点击用户登录按钮
    void on_userLoginButton_clicked();

    // 点击管理员登录按钮
    void on_adminLoginButton_clicked();


    // 从登录/注册窗口返回
    void on_returnToMain();

private:
    Ui::MainWindow *ui;
    LoginWindow* userLoginWindow;
    LoginWindow* adminLoginWindow;
    RegisterWindow* registerWindow;
};
#endif // MAIN_WINDOW_H
