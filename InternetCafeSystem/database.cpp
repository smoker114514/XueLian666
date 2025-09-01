#include "database.h"

Database::Database()
{
    // 初始化数据库连接
}

Database::~Database()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::init(const QString &dbName)
{
    // 添加SQLite数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    // 打开数据库
    if (!db.open()) {
        qDebug() << "数据库打开失败:" << db.lastError().text();
        return false;
    }

    // 创建数据表
    if (!createTables()) {
        return false;
    }

    // 初始化机器（如果不存在）
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM machines");
    if (query.next() && query.value(0).toInt() == 0) {
        return initMachines(30);
    }

    return true;
}

bool Database::createTables()
{
    QSqlQuery query;

    // 创建用户表
    QString userTable = "CREATE TABLE IF NOT EXISTS users ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "username TEXT UNIQUE NOT NULL, "
                        "password TEXT NOT NULL, "
                        "balance REAL DEFAULT 0, "
                        "is_admin INTEGER DEFAULT 0, "
                        "register_time DATETIME DEFAULT CURRENT_TIMESTAMP)";

    if (!query.exec(userTable)) {
        qDebug() << "创建用户表失败:" << query.lastError().text();
        return false;
    }

    // 创建机器表
    QString machineTable = "CREATE TABLE IF NOT EXISTS machines ("
                           "id INTEGER PRIMARY KEY, "
                           "status INTEGER DEFAULT 0, "
                           "current_user_id INTEGER, "
                           "start_time DATETIME, "
                           "FOREIGN KEY(current_user_id) REFERENCES users(id))";

    if (!query.exec(machineTable)) {
        qDebug() << "创建机器表失败:" << query.lastError().text();
        return false;
    }

    // 创建消费记录表
    QString consumptionTable = "CREATE TABLE IF NOT EXISTS consumption ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "user_id INTEGER, "
                               "machine_id INTEGER, "
                               "start_time DATETIME, "
                               "end_time DATETIME, "
                               "cost REAL, "
                               "FOREIGN KEY(user_id) REFERENCES users(id), "
                               "FOREIGN KEY(machine_id) REFERENCES machines(id))";

    if (!query.exec(consumptionTable)) {
        qDebug() << "创建消费记录表失败:" << query.lastError().text();
        return false;
    }

    // 创建默认管理员账号 admin/admin
    query.exec("SELECT * FROM users WHERE username = 'admin'");
    if (!query.next()) {
        query.prepare("INSERT INTO users (username, password, is_admin, balance) "
                      "VALUES (:username, :password, :is_admin, :balance)");
        query.bindValue(":username", "admin");
        query.bindValue(":password", "admin"); // 实际应用中应加密存储
        query.bindValue(":is_admin", 1);
        query.bindValue(":balance", 0);

        if (!query.exec()) {
            qDebug() << "创建管理员账号失败:" << query.lastError().text();
        }
    }

    return true;
}

bool Database::registerUser(const QString &username, const QString &password, bool isAdmin)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, is_admin, balance) "
                  "VALUES (:username, :password, :is_admin, :balance)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // 实际应用中应加密存储
    query.bindValue(":is_admin", isAdmin ? 1 : 0);
    query.bindValue(":balance", 0.0);

    return query.exec();
}

bool Database::loginUser(const QString &username, const QString &password, bool &isAdmin, int &userId)
{
    QSqlQuery query;
    query.prepare("SELECT id, is_admin FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec() || !query.next()) {
        return false;
    }

    userId = query.value(0).toInt();
    isAdmin = query.value(1).toInt() == 1;
    return true;
}

bool Database::rechargeAccount(int userId, double amount)
{
    if (amount <= 0) return false;

    QSqlQuery query;
    query.prepare("UPDATE users SET balance = balance + :amount WHERE id = :id");
    query.bindValue(":amount", amount);
    query.bindValue(":id", userId);

    return query.exec();
}

double Database::getAccountBalance(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return -1;
}

QString Database::getUsername(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

bool Database::initMachines(int count)
{
    QSqlQuery query;

    // 清空现有机器记录
    if (!query.exec("DELETE FROM machines")) {
        qDebug() << "清空机器表失败:" << query.lastError().text();
        return false;
    }

    // 插入新机器记录
    for (int i = 1; i <= count; ++i) {
        query.prepare("INSERT INTO machines (id, status) VALUES (:id, :status)");
        query.bindValue(":id", i);
        query.bindValue(":status", IDLE);

        if (!query.exec()) {
            qDebug() << "插入机器记录失败:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

bool Database::setMachineStatus(int machineId, MachineStatus status, int userId)
{
    QSqlQuery query;
    query.prepare("UPDATE machines SET status = :status, current_user_id = :user_id "
                  "WHERE id = :id");
    query.bindValue(":status", status);
    query.bindValue(":user_id", userId > 0 ? userId : QVariant(QVariant::Int));
    query.bindValue(":id", machineId);

    return query.exec();
}

MachineStatus Database::getMachineStatus(int machineId)
{
    QSqlQuery query;
    query.prepare("SELECT status FROM machines WHERE id = :id");
    query.bindValue(":id", machineId);

    if (query.exec() && query.next()) {
        return (MachineStatus)query.value(0).toInt();
    }
    return MALFUNCTION;
}

int Database::getMachineUserId(int machineId)
{
    QSqlQuery query;
    query.prepare("SELECT current_user_id FROM machines WHERE id = :id");
    query.bindValue(":id", machineId);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool Database::startUsingMachine(int machineId, int userId)
{
    // 检查机器是否空闲
    if (getMachineStatus(machineId) != IDLE) {
        return false;
    }

    // 检查用户余额是否充足
    if (getAccountBalance(userId) <= 0) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE machines SET status = :status, current_user_id = :user_id, "
                  "start_time = CURRENT_TIMESTAMP WHERE id = :id");
    query.bindValue(":status", IN_USE);
    query.bindValue(":user_id", userId);
    query.bindValue(":id", machineId);

    return query.exec();
}

bool Database::stopUsingMachine(int machineId)
{
    QSqlQuery query;

    // 获取机器使用信息
    query.prepare("SELECT current_user_id, start_time FROM machines WHERE id = :id");
    query.bindValue(":id", machineId);
    if (!query.exec() || !query.next()) {
        return false;
    }

    int userId = query.value(0).toInt();
    QDateTime startTime = query.value(1).toDateTime();
    QDateTime endTime = QDateTime::currentDateTime();

    // 计算费用
    double cost = calculateCost(startTime, endTime);

    // 更新用户余额
    query.prepare("UPDATE users SET balance = balance - :cost WHERE id = :user_id");
    query.bindValue(":cost", cost);
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        return false;
    }

    // 记录消费
    addConsumptionRecord(userId, machineId, startTime, endTime, cost);

    // 更新机器状态
    return setMachineStatus(machineId, IDLE, -1);
}

QList<int> Database::getAllMachineIds()
{
    QList<int> machineIds;
    QSqlQuery query("SELECT id FROM machines ORDER BY id");

    while (query.next()) {
        machineIds.append(query.value(0).toInt());
    }

    return machineIds;
}

bool Database::addConsumptionRecord(int userId, int machineId, const QDateTime &startTime,
                                    const QDateTime &endTime, double cost)
{
    QSqlQuery query;
    query.prepare("INSERT INTO consumption (user_id, machine_id, start_time, end_time, cost) "
                  "VALUES (:user_id, :machine_id, :start_time, :end_time, :cost)");
    query.bindValue(":user_id", userId);
    query.bindValue(":machine_id", machineId);
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);
    query.bindValue(":cost", cost);

    return query.exec();
}

QList<QMap<QString, QVariant>> Database::getConsumptionRecords(int userId, int limit)
{
    QList<QMap<QString, QVariant>> records;
    QSqlQuery query;

    if (userId == -1) {
        // 查询所有用户的记录
        query.prepare("SELECT * FROM consumption ORDER BY end_time DESC LIMIT :limit");
    } else {
        // 查询特定用户的记录
        query.prepare("SELECT * FROM consumption WHERE user_id = :user_id "
                      "ORDER BY end_time DESC LIMIT :limit");
        query.bindValue(":user_id", userId);
    }

    query.bindValue(":limit", limit);

    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> record;
            record["id"] = query.value("id");
            record["user_id"] = query.value("user_id");
            record["machine_id"] = query.value("machine_id");
            record["start_time"] = query.value("start_time");
            record["end_time"] = query.value("end_time");
            record["cost"] = query.value("cost");
            records.append(record);
        }
    }

    return records;
}

double Database::calculateCost(const QDateTime &startTime, const QDateTime &endTime, double rate)
{
    // 计算使用分钟数
    qint64 seconds = startTime.secsTo(endTime);
    double hours = seconds / 3600.0;

    // 按小时计费，不足1小时按1小时计算
    return ceil(hours * rate);
}
