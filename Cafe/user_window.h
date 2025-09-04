#ifndef USER_WINDOW_H
#define USER_WINDOW_H

#include <QWidget>
#include <QTimer>
#include "database_manager.h"
#include "chat_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserWindow; }
QT_END_NAMESPACE

class UserWindow : public QWidget {
    Q_OBJECT

public:
    UserWindow(QWidget *parent = nullptr);
    ~UserWindow();
    void updateMachineStatus(const QVector<QVector<QVariant>>& statusList);
    // 设置当前用户ID
    void setUserId(const QString& userId);
    void showEvent(QShowEvent *event) override;

    // 刷新用户信息
    void refreshUserInfo();

signals:
    // 返回登录窗口信号
    void returnToLogin();

private slots:
    // 充值按钮点击
    void on_rechargeButton_clicked();

    // 上机按钮点击
    void on_startButton_clicked();

    // 下机按钮点击
    void on_stopButton_clicked();

    // 退出按钮点击
    void on_exitButton_clicked();

    // 刷新机器状态
    void refreshMachineStatus();

    // 选择机器
    void on_machineSelected(int machineId);
    void onOpenChatButtonClicked();
    // 新增：处理聊天窗口返回的槽函数
    void onChatWindowReturn();

private:
    Ui::UserWindow *ui;
    QString userId; // 当前用户ID
    int selectedMachineId; // 选中的机器ID
    bool isUsingMachine; // 是否正在使用机器
    QTimer* statusTimer; // 状态刷新定时器
    ChatWindow* chatWindow = nullptr;
};
#endif // USER_WINDOW_H
