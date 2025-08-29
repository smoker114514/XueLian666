#ifndef WIDGET_H
#define WIDGET_H
#include<QEvent>
#include<QMouseEvent>

#include <QWidget>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_radioButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
class DragWidgetFilter :public QObject{
public:
    DragWidgetFilter(QObject* parent)
        :QObject(parent){}
    bool eventFilter(QObject* object, QEvent* event)
    {
       auto w = dynamic_cast<QWidget*>(object);
        if(!w){
           return false;
        }
        if(event->type()==QEvent::MouseButtonPress)
        {
            auto ev = dynamic_cast<QMouseEvent*>(event);
            if(!ev)
                return false;

            pos=ev->pos();
        }
        else if(event->type()==QEvent::MouseMove)
        {
            auto ev = dynamic_cast<QMouseEvent*>(event);
            if(!ev)
                return false;
            if(ev->buttons()&Qt::MouseButton::LeftButton)
            {
                w->move(ev->globalPosition().toPoint()-pos);
            }

        }
        return QObject::eventFilter(object,event);
    }
private:
    QPoint pos;
};

#endif // WIDGET_H
