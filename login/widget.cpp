#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    this->installEventFilter(new DragWidgetFilter(this));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked()){
        ui->pushButton->setStyleSheet("background-color:rgb(0,135,255)");
        ui->pushButton->setEnabled(true);
    }
    else{
        ui->pushButton->setStyleSheet("background-color:rgb(158,218,255)");
        ui->pushButton->setEnabled(false);
    }
}


void Widget::on_toolButton_2_clicked()
{
    this->close();
}


void Widget::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==tr("xuelian")&&ui->lineEdit_2->text()==tr("88888888")){
        QMessageBox msgBox(QMessageBox::Information, "登录成功", "欢迎回来"+ui->lineEdit->text()+"!", QMessageBox::Ok, this);
        msgBox.setStyleSheet("QMessageBox { background-color: rgb（173，216，230）; } QMessageBox QLabel { background-color: rgb（173，216，230）;color: red; }");
        msgBox.exec();
    }
    else if(ui->lineEdit->text()!=tr("xuelian"))
    {
        QMessageBox::warning(this, "验证失败", "<font color='red'>用户不存在！</font>");
    }
    else if(ui->lineEdit_2->text()!=tr("88888888"))
    {
        QMessageBox::warning(this, "验证失败", "<font color='red'>密码错误！</font>");
    }
}

