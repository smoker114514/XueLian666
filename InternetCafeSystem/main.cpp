#include <QApplication>
#include "loginwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化数据库
    Database db;
    if (!db.init()) {
        qDebug() << "数据库初始化失败，程序将退出!";
        return -1;
    }

    // 显示登录窗口
    LoginWindow loginWindow(&db);
    loginWindow.show();

    return a.exec();
}
