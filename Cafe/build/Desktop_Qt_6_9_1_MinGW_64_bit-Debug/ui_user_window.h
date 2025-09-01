/********************************************************************************
** Form generated from reading UI file 'user_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_WINDOW_H
#define UI_USER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWindow
{
public:
    QLabel *balanceLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QPushButton *rechargeButton;
    QPushButton *startButton;
    QPushButton *exitButton;
    QPushButton *stopButton;
    QTableWidget *machineStatusWidget;

    void setupUi(QWidget *UserWindow)
    {
        if (UserWindow->objectName().isEmpty())
            UserWindow->setObjectName("UserWindow");
        UserWindow->resize(511, 353);
        UserWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
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
"}\n"
"/* \347\252\201\345\207\272\351\207\215\350\246\201\346\214\211\351\222\256\357\274\210\345\246\202\342\200\234\345\205\205\345\200\274\342\200\235\357\274\211 */\n"
"QPushButton {\n"
"    background-color: #2C7AD6;\n"
"    color: white;\n"
"    border: none;\n"
"}\n"
""));
        balanceLabel = new QLabel(UserWindow);
        balanceLabel->setObjectName("balanceLabel");
        balanceLabel->setGeometry(QRect(20, 20, 151, 41));
        QFont font;
        font.setPointSize(10);
        balanceLabel->setFont(font);
        balanceLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);
        layoutWidget = new QWidget(UserWindow);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 470, 304));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(26);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        rechargeButton = new QPushButton(layoutWidget);
        rechargeButton->setObjectName("rechargeButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rechargeButton->sizePolicy().hasHeightForWidth());
        rechargeButton->setSizePolicy(sizePolicy);
        rechargeButton->setMinimumSize(QSize(230, 0));

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, rechargeButton);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName("startButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy1);
        startButton->setMinimumSize(QSize(230, 0));

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, startButton);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName("exitButton");
        sizePolicy.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy);
        exitButton->setMinimumSize(QSize(230, 0));

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, exitButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName("stopButton");
        sizePolicy1.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy1);
        stopButton->setMinimumSize(QSize(230, 0));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, stopButton);


        verticalLayout->addLayout(formLayout);

        machineStatusWidget = new QTableWidget(layoutWidget);
        if (machineStatusWidget->columnCount() < 6)
            machineStatusWidget->setColumnCount(6);
        if (machineStatusWidget->rowCount() < 5)
            machineStatusWidget->setRowCount(5);
        machineStatusWidget->setObjectName("machineStatusWidget");
        machineStatusWidget->setLineWidth(5);
        machineStatusWidget->setMidLineWidth(0);
        machineStatusWidget->setRowCount(5);
        machineStatusWidget->setColumnCount(6);

        verticalLayout->addWidget(machineStatusWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(UserWindow);

        QMetaObject::connectSlotsByName(UserWindow);
    } // setupUi

    void retranslateUi(QWidget *UserWindow)
    {
        UserWindow->setWindowTitle(QCoreApplication::translate("UserWindow", "Form", nullptr));
        balanceLabel->setText(QCoreApplication::translate("UserWindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("UserWindow", "\346\254\242\350\277\216\346\235\245\345\210\260\345\255\246\351\223\276\347\275\221\345\222\226", nullptr));
        rechargeButton->setText(QCoreApplication::translate("UserWindow", "\345\205\205\345\200\274", nullptr));
        startButton->setText(QCoreApplication::translate("UserWindow", "\345\274\200\345\247\213\344\270\212\346\234\272", nullptr));
        exitButton->setText(QCoreApplication::translate("UserWindow", "\351\200\200\345\207\272", nullptr));
        stopButton->setText(QCoreApplication::translate("UserWindow", "\347\273\223\346\235\237\344\270\212\346\234\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserWindow: public Ui_UserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_WINDOW_H
