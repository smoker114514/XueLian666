/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *titleLabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *userLabel;
    QLineEdit *userEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pwdLabel;
    QLineEdit *pwdEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *userRadio;
    QRadioButton *adminRadio;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *loginBtn;
    QPushButton *registerBtn;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(566, 414);
        Form->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 6px 20px; \n"
"    border: none;     \n"
"    background-color: #4CAF50; \n"
"    color: white;    \n"
"    border-radius: 3px;\n"
"}\n"
"QPushButton:hover { \n"
"    background-color: #45a049;\n"
"}\n"
"QWidget {\n"
"    background-image: url(:/backGround_1.jpeg);\n"
"    background-repeat: no-repeat; \n"
"    background-attachment: fixed;  \n"
"    background-position: center;\n"
"}"));
        titleLabel = new QLabel(Form);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(180, 80, 191, 81));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget = new QWidget(Form);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(80, 170, 411, 231));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        userLabel = new QLabel(widget);
        userLabel->setObjectName("userLabel");

        horizontalLayout->addWidget(userLabel);

        userEdit = new QLineEdit(widget);
        userEdit->setObjectName("userEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userEdit->sizePolicy().hasHeightForWidth());
        userEdit->setSizePolicy(sizePolicy);
        userEdit->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(12);
        userEdit->setFont(font1);

        horizontalLayout->addWidget(userEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pwdLabel = new QLabel(widget);
        pwdLabel->setObjectName("pwdLabel");

        horizontalLayout_2->addWidget(pwdLabel);

        pwdEdit = new QLineEdit(widget);
        pwdEdit->setObjectName("pwdEdit");
        sizePolicy.setHeightForWidth(pwdEdit->sizePolicy().hasHeightForWidth());
        pwdEdit->setSizePolicy(sizePolicy);
        pwdEdit->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setPointSize(10);
        pwdEdit->setFont(font2);
        pwdEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(pwdEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        userRadio = new QRadioButton(widget);
        userRadio->setObjectName("userRadio");

        horizontalLayout_3->addWidget(userRadio);

        adminRadio = new QRadioButton(widget);
        adminRadio->setObjectName("adminRadio");

        horizontalLayout_3->addWidget(adminRadio);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        loginBtn = new QPushButton(widget);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(loginBtn);

        registerBtn = new QPushButton(widget);
        registerBtn->setObjectName("registerBtn");
        registerBtn->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(registerBtn);


        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("Form", "\347\275\221\345\220\247\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        userLabel->setText(QCoreApplication::translate("Form", "\350\264\246\345\217\267\357\274\232", nullptr));
        userEdit->setPlaceholderText(QCoreApplication::translate("Form", "\350\257\267\350\276\223\345\205\245\350\264\246\345\217\267", nullptr));
        pwdLabel->setText(QCoreApplication::translate("Form", "\345\257\206\347\240\201\357\274\232", nullptr));
        pwdEdit->setPlaceholderText(QCoreApplication::translate("Form", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        userRadio->setText(QCoreApplication::translate("Form", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        adminRadio->setText(QCoreApplication::translate("Form", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", nullptr));
        loginBtn->setText(QCoreApplication::translate("Form", "\347\231\273\345\275\225", nullptr));
        registerBtn->setText(QCoreApplication::translate("Form", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
