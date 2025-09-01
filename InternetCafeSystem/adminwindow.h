#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTabWidget>
#include "database.h"

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    AdminWindow(Database *db, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void onShutdownClicked();
    void onRestartClicked();
    void onRefreshClicked();
    void onLogoutClicked();
    void updateMachineStatus();
    void onViewRecordsClicked();

private:
    Database *db;
    QTableWidget *machineTable;
    QTableWidget *recordTable;
    QPushButton *shutdownButton;
    QPushButton *restartButton;
    QPushButton *refreshButton;
    QPushButton *viewRecordsButton;
    QPushButton *logoutButton;
    QTimer *statusTimer;
    QTabWidget *tabWidget;

    void setupUI();
    void refreshMachineStatus();
    void refreshRecords();
};

#endif // ADMINWINDOW_H
