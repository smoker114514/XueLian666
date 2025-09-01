#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUsername(const QString &username);

private slots:

    void onReturnclicked();

private:
    Ui::MainWindow *ui;
    QLabel *welcomeLabel;
    QPushButton *returnBtn;
};
#endif
