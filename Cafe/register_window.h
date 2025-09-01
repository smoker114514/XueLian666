#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QWidget>
#include "database_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWindow; }
QT_END_NAMESPACE

class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

signals:
    // 返回主窗口信号
    void returnToMain();

private slots:
    // 注册按钮点击
    void on_registerButton_clicked();

    // 取消按钮点击
    void on_cancelButton_clicked();

private:
    Ui::RegisterWindow *ui;
};
#endif // REGISTER_WINDOW_H
