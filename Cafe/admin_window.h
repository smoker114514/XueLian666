#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QWidget>
#include <QTimer>
#include "database_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AdminWindow; }
QT_END_NAMESPACE

class AdminWindow : public QWidget {
    Q_OBJECT

public:
    AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    // 刷新机器状态
    void refreshMachineStatus();
    void updateMachineMonitor(const QVector<QVector<QVariant>>& statusList);
    void populateDataTable(const QVector<QVector<QVariant>>& data, const QStringList& headers);

signals:
    // 返回登录窗口信号
    void returnToLogin();

private slots:
    // 启动机器按钮点击
    void on_startMachineButton_clicked();

    // 关闭机器按钮点击
    void on_shutdownMachineButton_clicked();

    // 强制下机按钮点击
    void on_forceLogoutButton_clicked();

    // 查询用户数据按钮点击
    void on_queryUsersButton_clicked();

    // 查询机器使用数据按钮点击
    void on_queryMachinesButton_clicked();

    // 查询充值记录按钮点击
    void on_queryRechargesButton_clicked();

    // 退出按钮点击
    void on_exitButton_clicked();

    // 刷新定时器槽函数
    void on_refreshTimer_timeout();

    // 选择机器
    void on_machineSelected(int machineId);

private:
    Ui::AdminWindow *ui;
    int selectedMachineId; // 选中的机器ID
    QTimer* refreshTimer; // 状态刷新定时器
};
#endif // ADMIN_WINDOW_H

