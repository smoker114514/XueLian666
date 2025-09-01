/********************************************************************************
** Form generated from reading UI file 'admin_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_WINDOW_H
#define UI_ADMIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QPushButton *queryMachinesButton;
    QPushButton *startMachineButton;
    QPushButton *queryRechargesButton;
    QPushButton *shutdownMachineButton;
    QPushButton *queryUsersButton;
    QPushButton *forceLogoutButton;
    QPushButton *exitButton;
    QTableWidget *machineMonitorWidget;
    QTableWidget *dataTableWidget;

    void setupUi(QWidget *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(499, 541);
        widget = new QWidget(AdminWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 50, 258, 480));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        queryMachinesButton = new QPushButton(widget);
        queryMachinesButton->setObjectName("queryMachinesButton");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, queryMachinesButton);

        startMachineButton = new QPushButton(widget);
        startMachineButton->setObjectName("startMachineButton");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, startMachineButton);

        queryRechargesButton = new QPushButton(widget);
        queryRechargesButton->setObjectName("queryRechargesButton");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, queryRechargesButton);

        shutdownMachineButton = new QPushButton(widget);
        shutdownMachineButton->setObjectName("shutdownMachineButton");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, shutdownMachineButton);

        queryUsersButton = new QPushButton(widget);
        queryUsersButton->setObjectName("queryUsersButton");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, queryUsersButton);

        forceLogoutButton = new QPushButton(widget);
        forceLogoutButton->setObjectName("forceLogoutButton");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, forceLogoutButton);

        exitButton = new QPushButton(widget);
        exitButton->setObjectName("exitButton");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, exitButton);


        verticalLayout->addLayout(formLayout);

        machineMonitorWidget = new QTableWidget(widget);
        if (machineMonitorWidget->columnCount() < 6)
            machineMonitorWidget->setColumnCount(6);
        if (machineMonitorWidget->rowCount() < 5)
            machineMonitorWidget->setRowCount(5);
        machineMonitorWidget->setObjectName("machineMonitorWidget");
        machineMonitorWidget->setRowCount(5);
        machineMonitorWidget->setColumnCount(6);

        verticalLayout->addWidget(machineMonitorWidget);

        dataTableWidget = new QTableWidget(widget);
        dataTableWidget->setObjectName("dataTableWidget");

        verticalLayout->addWidget(dataTableWidget);


        retranslateUi(AdminWindow);

        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QWidget *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "Form", nullptr));
        queryMachinesButton->setText(QCoreApplication::translate("AdminWindow", "\346\237\245\350\257\242\346\234\272\345\231\250\350\256\260\345\275\225", nullptr));
        startMachineButton->setText(QCoreApplication::translate("AdminWindow", "\345\220\257\345\212\250\346\234\272\345\231\250", nullptr));
        queryRechargesButton->setText(QCoreApplication::translate("AdminWindow", "\346\237\245\350\257\242\345\205\205\345\200\274\350\256\260\345\275\225", nullptr));
        shutdownMachineButton->setText(QCoreApplication::translate("AdminWindow", "\345\205\263\351\227\255\346\234\272\345\231\250", nullptr));
        queryUsersButton->setText(QCoreApplication::translate("AdminWindow", "\346\237\245\350\257\242\347\224\250\346\210\267", nullptr));
        forceLogoutButton->setText(QCoreApplication::translate("AdminWindow", "\345\274\272\345\210\266\344\270\213\346\234\272", nullptr));
        exitButton->setText(QCoreApplication::translate("AdminWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_WINDOW_H
