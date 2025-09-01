/********************************************************************************
** Form generated from reading UI file 'register_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_WINDOW_H
#define UI_REGISTER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QLabel *label_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmEdit;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(511, 353);
        QFont font;
        font.setPointSize(16);
        RegisterWindow->setFont(font);
        RegisterWindow->setStyleSheet(QString::fromUtf8("/* \346\240\207\347\255\276\346\240\267\345\274\217\357\274\232\346\270\205\346\231\260\345\217\257\350\257\273 */\n"
"QLabel {\n"
"    color: #333; \n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\346\240\267\345\274\217\357\274\232\345\270\246\350\276\271\346\241\206\343\200\201\345\234\206\350\247\222\357\274\214\347\204\246\347\202\271\346\227\266\346\234\211\344\272\244\344\272\222\345\217\215\351\246\210 */\n"
"QLineEdit {\n"
"    border: 1px solid #DDD;\n"
"    border-radius: 4px;\n"
"    padding: 6px 10px;\n"
"    font-size: 14px;\n"
"    background-color: white;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #2C7AD6; /* \347\204\246\347\202\271\346\227\266\350\223\235\350\211\262\350\276\271\346\241\206\357\274\214\346\230\216\347\241\256\344\272\244\344\272\222\347\212\266\346\200\201 */\n"
"    outline: none;\n"
"}\n"
"\n"
"/* \346\214\211\351\222\256\346\240\267\345\274\217\357\274\232\345\214\272\345\210\206\342\200\234\346\263\250\345\206\214\342\200\235\345\222"
                        "\214\342\200\234\345\217\226\346\266\210\342\200\235\357\274\214hover\346\227\266\346\234\211\345\217\215\351\246\210 */\n"
"QPushButton {\n"
"    border-radius: 4px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"/* \346\263\250\345\206\214\346\214\211\351\222\256\357\274\210\344\270\273\346\223\215\344\275\234\357\274\211- \350\223\235\350\211\262\347\252\201\345\207\272 */\n"
"QPushButton#registerButton {\n"
"    background-color: #2C7AD6;\n"
"    color: white;\n"
"    border: none;\n"
"}\n"
"QPushButton#registerButton:hover {\n"
"    background-color: #1E65CC; /* hover\346\227\266\345\212\240\346\267\261\351\242\234\350\211\262 */\n"
"}\n"
"/* \345\217\226\346\266\210\346\214\211\351\222\256\357\274\210\346\254\241\350\246\201\346\223\215\344\275\234\357\274\211- \346\265\205\347\201\260\345\274\261\345\214\226 */\n"
"QPushButton#cancelButton {\n"
"    background-color: #DDD;\n"
"    color: #666;\n"
"    border: none;\n"
"}\n"
"QPushButton#cancelButton:hover {\n"
""
                        "    background-color: #CCC;\n"
"}\n"
"QLabel#label_6 {\n"
"    \n"
"	color: rgb(155, 255, 252);\n"
"    font-size: 28px;\n"
"}"));
        label_6 = new QLabel(RegisterWindow);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 10, 401, 31));
        QFont font1;
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget = new QWidget(RegisterWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 50, 421, 301));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        usernameEdit = new QLineEdit(widget);
        usernameEdit->setObjectName("usernameEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernameEdit->sizePolicy().hasHeightForWidth());
        usernameEdit->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(usernameEdit);

        passwordEdit = new QLineEdit(widget);
        passwordEdit->setObjectName("passwordEdit");
        sizePolicy.setHeightForWidth(passwordEdit->sizePolicy().hasHeightForWidth());
        passwordEdit->setSizePolicy(sizePolicy);
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(passwordEdit);

        confirmEdit = new QLineEdit(widget);
        confirmEdit->setObjectName("confirmEdit");
        sizePolicy.setHeightForWidth(confirmEdit->sizePolicy().hasHeightForWidth());
        confirmEdit->setSizePolicy(sizePolicy);
        confirmEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout_2->addWidget(confirmEdit);

        nameEdit = new QLineEdit(widget);
        nameEdit->setObjectName("nameEdit");
        sizePolicy.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(nameEdit);

        phoneEdit = new QLineEdit(widget);
        phoneEdit->setObjectName("phoneEdit");
        sizePolicy.setHeightForWidth(phoneEdit->sizePolicy().hasHeightForWidth());
        phoneEdit->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(phoneEdit);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        registerButton = new QPushButton(widget);
        registerButton->setObjectName("registerButton");

        horizontalLayout->addWidget(registerButton);

        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);


        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("RegisterWindow", "\346\254\242\350\277\216\346\235\245\345\210\260\345\255\246\351\223\276\347\275\221\345\222\226", nullptr));
        label->setText(QCoreApplication::translate("RegisterWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterWindow", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterWindow", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterWindow", "\345\247\223\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterWindow", "\347\224\265\350\257\235", nullptr));
        phoneEdit->setInputMask(QCoreApplication::translate("RegisterWindow", "\350\257\267\350\276\223\345\205\245\346\234\211\346\225\210\347\224\265\350\257\235", nullptr));
        registerButton->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("RegisterWindow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_WINDOW_H
