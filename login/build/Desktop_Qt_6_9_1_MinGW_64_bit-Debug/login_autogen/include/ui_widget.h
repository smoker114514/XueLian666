/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *profile_label;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QRadioButton *radioButton;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *scan_pushButton;
    QFrame *line_2;
    QPushButton *more_pushButton;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(280, 342);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"QPushButton{\n"
"	\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"QPushButton#pushButton{\n"
"	\n"
"	background-color: rgb(158,218,255);\n"
"	color:rgb(255,255,255); \n"
"	border:none;\n"
"	border-radius: 10px;\n"
"}\n"
"QFrame{\n"
"	border-radius:25px;\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
""));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, -10, 278, 351));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(layoutWidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(205, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton = new QToolButton(widget);
        toolButton->setObjectName("toolButton");

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(widget);
        toolButton_2->setObjectName("toolButton_2");

        horizontalLayout->addWidget(toolButton_2);


        verticalLayout_5->addWidget(widget);

        widget_2 = new QWidget(layoutWidget);
        widget_2->setObjectName("widget_2");
        verticalLayout_4 = new QVBoxLayout(widget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(240, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        profile_label = new QLabel(widget_2);
        profile_label->setObjectName("profile_label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profile_label->sizePolicy().hasHeightForWidth());
        profile_label->setSizePolicy(sizePolicy1);
        profile_label->setMinimumSize(QSize(10, 95));
        QFont font;
        font.setPointSize(9);
        profile_label->setFont(font);
        profile_label->setPixmap(QPixmap(QString::fromUtf8(":/tmp_748272393604771840_1756210040864.svg")));
        profile_label->setScaledContents(true);
        profile_label->setMargin(7);
        profile_label->setOpenExternalLinks(false);

        horizontalLayout_2->addWidget(profile_label);

        horizontalSpacer_4 = new QSpacerItem(240, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setPointSize(13);
        lineEdit->setFont(font1);
        lineEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setMinimumSize(QSize(12, 40));
        lineEdit_2->setFont(font1);
        lineEdit_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lineEdit_2);

        radioButton = new QRadioButton(widget_2);
        radioButton->setObjectName("radioButton");

        verticalLayout->addWidget(radioButton);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        pushButton->setMinimumSize(QSize(0, 35));
        pushButton->setIconSize(QSize(12, 18));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        scan_pushButton = new QPushButton(widget_2);
        scan_pushButton->setObjectName("scan_pushButton");
        scan_pushButton->setMinimumSize(QSize(50, 0));

        horizontalLayout_3->addWidget(scan_pushButton);

        line_2 = new QFrame(widget_2);
        line_2->setObjectName("line_2");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy3);
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line_2);

        more_pushButton = new QPushButton(widget_2);
        more_pushButton->setObjectName("more_pushButton");
        more_pushButton->setMinimumSize(QSize(50, 0));

        horizontalLayout_3->addWidget(more_pushButton);

        horizontalSpacer_5 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(widget_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        toolButton->setText(QCoreApplication::translate("Widget", "\342\232\231", nullptr));
        toolButton_2->setText(QCoreApplication::translate("Widget", "\303\227", nullptr));
        profile_label->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245QQ\345\217\267", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("Widget", "\350\276\223\345\205\245QQ\345\257\206\347\240\201", nullptr));
        radioButton->setText(QCoreApplication::translate("Widget", "\345\267\262\351\230\205\350\257\273\345\271\266\345\220\214\346\204\217\346\234\215\345\212\241\345\215\217\350\256\256\345\222\214QQ\351\232\220\347\247\201\344\277\235\346\212\244\346\214\207\345\274\225", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        scan_pushButton->setText(QCoreApplication::translate("Widget", "\346\211\253\347\240\201\347\231\273\345\275\225", nullptr));
        more_pushButton->setText(QCoreApplication::translate("Widget", "\346\233\264\345\244\232\351\200\211\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
