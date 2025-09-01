#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QMessageBox>
#include "database.h"

class UserWindow;
class AdminWindow;

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(Database *db, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Database *db;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QRadioButton *userRadio;
    QRadioButton *adminRadio;
    QPushButton *loginButton;
    QPushButton *registerButton;

    UserWindow *userWindow;
    AdminWindow *adminWindow;

    void setupUI();
};

#endif // LOGINWINDOW_H
