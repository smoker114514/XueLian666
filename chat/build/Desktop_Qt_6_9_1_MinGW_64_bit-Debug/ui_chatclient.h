/********************************************************************************
** Form generated from reading UI file 'chatclient.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCLIENT_H
#define UI_CHATCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatClient
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widgetConnect;
    QHBoxLayout *horizontalLayout;
    QLabel *labelStatus;
    QPushButton *btnConnect;
    QLabel *labelPort;
    QLineEdit *lineEditPort;
    QTextEdit *textEditChat;
    QWidget *widgetInput;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditInput;
    QPushButton *btnSend;
    QPushButton *btnClear;
    QLabel *labelIP;
    QLineEdit *lineEditIP;

    void setupUi(QWidget *ChatClient)
    {
        if (ChatClient->objectName().isEmpty())
            ChatClient->setObjectName("ChatClient");
        ChatClient->resize(628, 600);
        ChatClient->setMinimumSize(QSize(400, 600));
        ChatClient->setMaximumSize(QSize(800, 800));
        layoutWidget = new QWidget(ChatClient);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 40, 381, 541));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widgetConnect = new QWidget(layoutWidget);
        widgetConnect->setObjectName("widgetConnect");
        horizontalLayout = new QHBoxLayout(widgetConnect);
        horizontalLayout->setObjectName("horizontalLayout");
        labelStatus = new QLabel(widgetConnect);
        labelStatus->setObjectName("labelStatus");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelStatus->sizePolicy().hasHeightForWidth());
        labelStatus->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(labelStatus);

        btnConnect = new QPushButton(widgetConnect);
        btnConnect->setObjectName("btnConnect");

        horizontalLayout->addWidget(btnConnect);

        labelPort = new QLabel(widgetConnect);
        labelPort->setObjectName("labelPort");

        horizontalLayout->addWidget(labelPort);

        lineEditPort = new QLineEdit(widgetConnect);
        lineEditPort->setObjectName("lineEditPort");

        horizontalLayout->addWidget(lineEditPort);


        verticalLayout->addWidget(widgetConnect);

        textEditChat = new QTextEdit(layoutWidget);
        textEditChat->setObjectName("textEditChat");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEditChat->sizePolicy().hasHeightForWidth());
        textEditChat->setSizePolicy(sizePolicy1);
        textEditChat->setReadOnly(true);

        verticalLayout->addWidget(textEditChat);


        verticalLayout_2->addLayout(verticalLayout);

        widgetInput = new QWidget(layoutWidget);
        widgetInput->setObjectName("widgetInput");
        horizontalLayout_2 = new QHBoxLayout(widgetInput);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lineEditInput = new QLineEdit(widgetInput);
        lineEditInput->setObjectName("lineEditInput");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditInput->sizePolicy().hasHeightForWidth());
        lineEditInput->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(lineEditInput);

        btnSend = new QPushButton(widgetInput);
        btnSend->setObjectName("btnSend");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnSend->sizePolicy().hasHeightForWidth());
        btnSend->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(btnSend);

        btnClear = new QPushButton(widgetInput);
        btnClear->setObjectName("btnClear");
        sizePolicy3.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(btnClear);


        verticalLayout_2->addWidget(widgetInput);

        labelIP = new QLabel(ChatClient);
        labelIP->setObjectName("labelIP");
        labelIP->setGeometry(QRect(10, 10, 40, 22));
        lineEditIP = new QLineEdit(ChatClient);
        lineEditIP->setObjectName("lineEditIP");
        lineEditIP->setGeometry(QRect(60, 10, 231, 22));

        retranslateUi(ChatClient);

        QMetaObject::connectSlotsByName(ChatClient);
    } // setupUi

    void retranslateUi(QWidget *ChatClient)
    {
        ChatClient->setWindowTitle(QCoreApplication::translate("ChatClient", "\350\201\212\345\244\251\345\256\242\346\210\267\347\253\257", nullptr));
        labelStatus->setText(QCoreApplication::translate("ChatClient", "TextLabel", nullptr));
        btnConnect->setText(QCoreApplication::translate("ChatClient", "PushButton", nullptr));
        labelPort->setText(QCoreApplication::translate("ChatClient", "TextLabel", nullptr));
        btnSend->setText(QCoreApplication::translate("ChatClient", "PushButton", nullptr));
        btnClear->setText(QCoreApplication::translate("ChatClient", "PushButton", nullptr));
        labelIP->setText(QCoreApplication::translate("ChatClient", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatClient: public Ui_ChatClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
