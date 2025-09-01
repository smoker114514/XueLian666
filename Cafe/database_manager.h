#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>

class DatabaseManager {
public:
    // 单例模式
    static DatabaseManager& getInstance() {
        static DatabaseManager instance;
        return instance;
    }

    // 初始化数据库
    bool initDatabase(const QString& dbName = "internet_cafe.db");

    // 用户相关操作
    bool registerUser(const QString& username, const QString& password, const QString& name, const QString& phone);
    bool loginUser(const QString& username, const QString& password, QString& userId);
    double getUserBalance(const QString& userId);
    bool rechargeBalance(const QString& userId, double amount);

    // 管理员相关操作
    bool loginAdmin(const QString& adminName, const QString& password);

    // 机器相关操作
    bool initMachines(int count = 30);
    bool getMachineStatus(int machineId, bool& isRunning, bool& isUsed, QString& userId);
    bool setMachineStatus(int machineId, bool isRunning, bool isUsed, const QString& userId = "");
    bool getAllMachinesStatus(QVector<QVector<QVariant>>& statusList);

    // 上机记录相关
    bool startUsingMachine(const QString& userId, int machineId);
    bool stopUsingMachine(int machineId);
    bool autoDeductFees(); // 自动扣费

    // 数据查询
    QVector<QVector<QVariant>> queryUserRecords(const QString& condition = "");
    QVector<QVector<QVariant>> queryMachineUsage(const QString& condition = "");
    QVector<QVector<QVariant>> queryRechargeRecords(const QString& condition = "");

private:
    DatabaseManager() {}
    ~DatabaseManager() {
        if (db.isOpen()) {
            db.close();
        }
    }

    // 禁止拷贝
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
