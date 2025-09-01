#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTableWidget>
#include "database.h"

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    UserWindow(Database *db, int userId, QWidget *parent = nullptr);
    ~UserWindow();

    void setUserId(int userId);

private slots:
    void onRechargeClicked();
    void onUseMachineClicked();
    void onLogoutClicked();
    void updateMachineStatus();
    void onEndSessionClicked();
    void checkBalance();

private:
    Database *db;
    int userId;
    QLabel *usernameLabel;
    QLabel *balanceLabel;
    QTableWidget *machineTable;
    QPushButton *rechargeButton;
    QPushButton *useMachineButton;
    QPushButton *endSessionButton;
    QPushButton *logoutButton;
    QTimer *statusTimer;
    QTimer *balanceTimer;

    void setupUI();
    void refreshMachineStatus();
    void refreshBalance();
};

#endif // USERWINDOW_H

