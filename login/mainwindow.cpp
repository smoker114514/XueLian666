#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    setWindowTitle("主界面");
    setMinimumSize(800, 600);


    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(50);
    layout->setContentsMargins(20, 20, 20, 20);


    welcomeLabel = new QLabel("欢迎使用系统", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; color: #333;");
    layout->addWidget(welcomeLabel);


    returnBtn = new QPushButton("返回登录", this);

    returnBtn->setStyleSheet(
        "font-size: 16px;"
        "padding: 10px 20px;"
        "background-color: #0087ff;"
        "color: white;"
        "border: none;"
        "border-radius: 5px;"
        );

    returnBtn->setMinimumSize(120, 40);

    layout->addWidget(returnBtn, 0, Qt::AlignCenter);


    connect(returnBtn, &QPushButton::clicked, this, &MainWindow::onReturnclicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete welcomeLabel;
    delete returnBtn;
}


void MainWindow::setUsername(const QString &username)
{
    welcomeLabel->setText(QString("欢迎回来，%1！").arg(username));
}


void MainWindow::onReturnclicked()
{

    QMessageBox::information(this, "提示", "返回登录界面！");

    Widget *loginWindow = new Widget();
    loginWindow->show();


    this->close();
}


