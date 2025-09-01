/********************************************************************************
** Form generated from reading UI file 'login_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_WINDOW_H
#define UI_LOGIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *usernameEdit;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QPushButton *registerButton;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(511, 353);
        LoginWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(69, 140, 255);\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 4px;\n"
"    padding: 6px 12px;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(150, 255, 255);\n"
"    border-color: #2C7AD6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #E8F4F8; \n"
"}\n"
"QLineEdit {\n"
"    border: 1px solid #DDD;\n"
"    border-radius: 4px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"	\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"QLabel#label_3{\n"
"	\n"
"	color: rgb(85, 255, 0);\n"
"\n"
"}\n"
"QLabel#label_4{\n"
"	\n"
"	color: rgb(56, 228, 255);\n"
"}"));
        label_3 = new QLabel(LoginWindow);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 250, 371, 41));
        QFont font;
        font.setPointSize(11);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4 = new QLabel(LoginWindow);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 40, 101, 31));
        QFont font1;
        font1.setPointSize(21);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget = new QWidget(LoginWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 100, 351, 81));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(15);
        label->setFont(font2);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        usernameEdit = new QLineEdit(widget);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameEdit);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font2);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        passwordEdit = new QLineEdit(widget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, passwordEdit);

        widget1 = new QWidget(LoginWindow);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(120, 190, 250, 34));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loginButton = new QPushButton(widget1);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        cancelButton = new QPushButton(widget1);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        registerButton = new QPushButton(widget1);
        registerButton->setObjectName("registerButton");

        horizontalLayout->addWidget(registerButton);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWindow", "\345\277\230\350\256\260\345\257\206\347\240\201\350\257\267\345\210\260\345\211\215\345\217\260\347\241\256\350\256\244\350\272\253\344\273\275\345\220\216\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("LoginWindow", "\346\254\242\350\277\216\345\233\236\346\235\245", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        cancelButton->setText(QCoreApplication::translate("LoginWindow", "\345\217\226\346\266\210", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H
