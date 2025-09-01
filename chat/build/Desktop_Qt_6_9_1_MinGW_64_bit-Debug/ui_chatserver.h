/********************************************************************************
** Form generated from reading UI file 'chatserver.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATSERVER_H
#define UI_CHATSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatServer
{
public:
    QWidget *widgetMainContent;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widgetClientList;
    QLabel *labelClients;
    QListWidget *listWidgetClients;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widgetListen;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPort;
    QLineEdit *lineEditPort;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QLabel *labelStatus;
    QWidget *widgetLog;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLog;
    QTextEdit *textEditLog;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditServerInput;
    QPushButton *btnServerSend;
    QPushButton *btnClearLog;

    void setupUi(QWidget *ChatServer)
    {
        if (ChatServer->objectName().isEmpty())
            ChatServer->setObjectName("ChatServer");
        ChatServer->resize(437, 600);
        ChatServer->setMinimumSize(QSize(400, 600));
        widgetMainContent = new QWidget(ChatServer);
        widgetMainContent->setObjectName("widgetMainContent");
        widgetMainContent->setGeometry(QRect(10, 40, 371, 161));
        horizontalLayout_5 = new QHBoxLayout(widgetMainContent);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        widgetClientList = new QWidget(widgetMainContent);
        widgetClientList->setObjectName("widgetClientList");
        labelClients = new QLabel(widgetClientList);
        labelClients->setObjectName("labelClients");
        labelClients->setGeometry(QRect(30, 10, 91, 16));
        listWidgetClients = new QListWidget(widgetClientList);
        listWidgetClients->setObjectName("listWidgetClients");
        listWidgetClients->setGeometry(QRect(20, 30, 321, 91));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidgetClients->sizePolicy().hasHeightForWidth());
        listWidgetClients->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(widgetClientList);

        widget = new QWidget(ChatServer);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 190, 401, 111));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widgetListen = new QWidget(widget);
        widgetListen->setObjectName("widgetListen");
        horizontalLayout = new QHBoxLayout(widgetListen);
        horizontalLayout->setObjectName("horizontalLayout");
        labelPort = new QLabel(widgetListen);
        labelPort->setObjectName("labelPort");

        horizontalLayout->addWidget(labelPort);

        lineEditPort = new QLineEdit(widgetListen);
        lineEditPort->setObjectName("lineEditPort");

        horizontalLayout->addWidget(lineEditPort);

        btnStart = new QPushButton(widgetListen);
        btnStart->setObjectName("btnStart");

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(widgetListen);
        btnStop->setObjectName("btnStop");
        btnStop->setEnabled(false);

        horizontalLayout->addWidget(btnStop);

        labelStatus = new QLabel(widgetListen);
        labelStatus->setObjectName("labelStatus");

        horizontalLayout->addWidget(labelStatus);


        verticalLayout->addWidget(widgetListen);


        horizontalLayout_2->addLayout(verticalLayout);

        widgetLog = new QWidget(ChatServer);
        widgetLog->setObjectName("widgetLog");
        widgetLog->setGeometry(QRect(0, 370, 371, 191));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetLog->sizePolicy().hasHeightForWidth());
        widgetLog->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(widgetLog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelLog = new QLabel(widgetLog);
        labelLog->setObjectName("labelLog");

        verticalLayout_2->addWidget(labelLog);

        textEditLog = new QTextEdit(widgetLog);
        textEditLog->setObjectName("textEditLog");
        sizePolicy.setHeightForWidth(textEditLog->sizePolicy().hasHeightForWidth());
        textEditLog->setSizePolicy(sizePolicy);
        textEditLog->setMaximumSize(QSize(16777215, 16777215));
        textEditLog->setReadOnly(true);

        verticalLayout_2->addWidget(textEditLog);

        widget1 = new QWidget(ChatServer);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(0, 300, 401, 61));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEditServerInput = new QLineEdit(widget1);
        lineEditServerInput->setObjectName("lineEditServerInput");

        horizontalLayout_4->addWidget(lineEditServerInput);

        btnServerSend = new QPushButton(widget1);
        btnServerSend->setObjectName("btnServerSend");

        horizontalLayout_4->addWidget(btnServerSend);

        btnClearLog = new QPushButton(widget1);
        btnClearLog->setObjectName("btnClearLog");

        horizontalLayout_4->addWidget(btnClearLog);


        retranslateUi(ChatServer);

        QMetaObject::connectSlotsByName(ChatServer);
    } // setupUi

    void retranslateUi(QWidget *ChatServer)
    {
        ChatServer->setWindowTitle(QCoreApplication::translate("ChatServer", "\350\201\212\345\244\251\346\234\215\345\212\241\345\231\250", nullptr));
        labelClients->setText(QCoreApplication::translate("ChatServer", "TextLabel", nullptr));
        labelPort->setText(QCoreApplication::translate("ChatServer", "TextLabel", nullptr));
        btnStart->setText(QCoreApplication::translate("ChatServer", "PushButton", nullptr));
        btnStop->setText(QCoreApplication::translate("ChatServer", "PushButton", nullptr));
        labelStatus->setText(QCoreApplication::translate("ChatServer", "TextLabel", nullptr));
        labelLog->setText(QCoreApplication::translate("ChatServer", "TextLabel", nullptr));
        btnServerSend->setText(QCoreApplication::translate("ChatServer", "PushButton", nullptr));
        btnClearLog->setText(QCoreApplication::translate("ChatServer", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatServer: public Ui_ChatServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATSERVER_H
