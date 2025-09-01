#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

// 机器状态枚举
enum MachineStatus {
    IDLE = 0,       // 空闲
    IN_USE = 1,     // 使用中
    MALFUNCTION = 2 // 故障
};

class Database
{
public:
    Database();
    ~Database();

    // 初始化数据库
    bool init(const QString &dbName = "internet_cafe.db");

    // 用户相关操作
    bool registerUser(const QString &username, const QString &password, bool isAdmin = false);
    bool loginUser(const QString &username, const QString &password, bool &isAdmin, int &userId);
    bool rechargeAccount(int userId, double amount);
    double getAccountBalance(int userId);
    QString getUsername(int userId);

    // 机器相关操作
    bool initMachines(int count = 30);
    bool setMachineStatus(int machineId, MachineStatus status, int userId = -1);
    MachineStatus getMachineStatus(int machineId);
    int getMachineUserId(int machineId);
    bool startUsingMachine(int machineId, int userId);
    bool stopUsingMachine(int machineId);
    QList<int> getAllMachineIds();

    // 消费记录相关
    bool addConsumptionRecord(int userId, int machineId, const QDateTime &startTime,
                              const QDateTime &endTime, double cost);
    QList<QMap<QString, QVariant>> getConsumptionRecords(int userId = -1, int limit = 100);

    // 计算费用 (每小时收费标准)
    double calculateCost(const QDateTime &startTime, const QDateTime &endTime, double rate = 5.0);

private:
    QSqlDatabase db;
    bool createTables();
};

#endif // DATABASE_H
