#include "main_window.h"
#include <QApplication>
#include "database_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化数据库
    if (!DatabaseManager::getInstance().initDatabase()) {
        qDebug() << "数据库初始化失败！";
        return -1;
    }

    // 初始化30台机器
    DatabaseManager::getInstance().initMachines(30);

    MainWindow w;
    w.show();

    return a.exec();
}
