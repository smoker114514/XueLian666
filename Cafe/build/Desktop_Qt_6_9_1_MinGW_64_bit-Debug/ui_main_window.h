/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *userLoginButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *adminLoginButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_6;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(630, 499);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(255, 89, 219);\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 4px;\n"
"    padding: 6px 12px;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"     /*  hover\346\227\266\346\265\205\350\211\262\350\203\214\346\231\257 */\n"
"	background-color: rgb(150, 255, 255);\n"
"    border-color: #2C7AD6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #E8F4F8; /* \347\202\271\345\207\273\346\227\266\346\233\264\346\267\261\350\211\262 */\n"
"}"));
        widget = new QWidget(MainWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(170, 90, 321, 41));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        userLoginButton = new QPushButton(widget);
        userLoginButton->setObjectName("userLoginButton");
        userLoginButton->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(userLoginButton);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        adminLoginButton = new QPushButton(widget);
        adminLoginButton->setObjectName("adminLoginButton");
        adminLoginButton->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(adminLoginButton);

        widget1 = new QWidget(MainWindow);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(140, 130, 376, 52));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName("label");
        label->setMaximumSize(QSize(50, 50));
        label->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/5.jpeg")));
        label->setScaledContents(true);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(50, 50));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/4.jpg")));
        label_2->setScaledContents(true);

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(widget1);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(50, 50));
        label_3->setMaximumSize(QSize(50, 50));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/6.jpeg")));
        label_3->setScaledContents(true);

        horizontalLayout_2->addWidget(label_3);

        label_5 = new QLabel(widget1);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(50, 50));
        label_5->setMaximumSize(QSize(50, 50));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/7.jpg")));
        label_5->setScaledContents(true);

        horizontalLayout_2->addWidget(label_5);

        label_8 = new QLabel(widget1);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(50, 50));
        label_8->setMaximumSize(QSize(50, 50));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/8.jpg")));
        label_8->setScaledContents(true);

        horizontalLayout_2->addWidget(label_8);

        label_7 = new QLabel(widget1);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(50, 50));
        label_7->setMaximumSize(QSize(50, 50));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/9.jpg")));
        label_7->setScaledContents(true);

        horizontalLayout_2->addWidget(label_7);

        label_6 = new QLabel(widget1);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(50, 50));
        label_6->setMaximumSize(QSize(50, 50));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/picture_source/10.png")));
        label_6->setScaledContents(true);

        horizontalLayout_2->addWidget(label_6);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
        userLoginButton->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        adminLoginButton->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\347\231\273\345\275\225", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_5->setText(QString());
        label_8->setText(QString());
        label_7->setText(QString());
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
