#include "database_manager.h"
#include <QDateTime>
#include <QVariant>
#include <QSqlRecord>
// 初始化数据库
bool DatabaseManager::initDatabase(const QString& dbName) {
    // 检查是否已添加数据库连接
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        // 添加SQLite数据库
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
    }


    // 打开数据库
    if (!db.open()) {
        qDebug() << "数据库打开失败: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // 创建用户表
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE NOT NULL, "
                    "password TEXT NOT NULL, "
                    "name TEXT, "
                    "phone TEXT, "
                    "balance REAL DEFAULT 0)")) {
        qDebug() << "创建用户表失败: " << query.lastError().text();
        return false;
    }

    // 创建管理员表
    if (!query.exec("CREATE TABLE IF NOT EXISTS admins ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE NOT NULL, "
                    "password TEXT NOT NULL)")) {
        qDebug() << "创建管理员表失败: " << query.lastError().text();
        return false;
    }

    // 创建机器表
    if (!query.exec("CREATE TABLE IF NOT EXISTS machines ("
                    "id INTEGER PRIMARY KEY, "
                    "is_running INTEGER DEFAULT 1, "  // 1:运行中 0:关闭
                    "is_used INTEGER DEFAULT 0,      "  // 1:使用中 0:空闲
                    "user_id INTEGER, "
                    "start_time TEXT, "
                    "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        qDebug() << "创建机器表失败: " << query.lastError().text();
        return false;
    }

    // 创建充值记录表
    if (!query.exec("CREATE TABLE IF NOT EXISTS recharges ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER, "
                    "amount REAL NOT NULL, "
                    "time TEXT NOT NULL, "
                    "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        qDebug() << "创建充值表失败: " << query.lastError().text();
        return false;
    }

    // 创建上机记录表
    if (!query.exec("CREATE TABLE IF NOT EXISTS usage_records ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER, "
                    "machine_id INTEGER, "
                    "start_time TEXT NOT NULL, "
                    "end_time TEXT, "
                    "duration INTEGER, "  // 时长(分钟)
                    "cost REAL, "         // 费用
                    "FOREIGN KEY(user_id) REFERENCES users(id), "
                    "FOREIGN KEY(machine_id) REFERENCES machines(id))")) {
        qDebug() << "创建使用记录表失败: " << query.lastError().text();
        return false;
    }

    // 添加 默认管理员账号
    if (!query.exec("SELECT * FROM admins WHERE username = 'admin'")) {
        qDebug() << "查询管理员失败: " << query.lastError().text();
    } else if (!query.next()) {
        // 插入默认管理员(用户名:admin, 密码:admin)
        if (!query.exec("INSERT INTO admins (username, password) VALUES ('admin', 'admin')")) {
            qDebug() << "插入默认管理员失败: " << query.lastError().text();
        }
    }

    return true;
}

// 初始化机器
bool DatabaseManager::initMachines(int count) {
    if (count <= 0) {
        qDebug() << "机器数量必须为正数";
        return false;
    }

    QSqlQuery query;

    // 查询当前最大机器ID（而非数量，避免ID不连续的情况）
    if (!query.exec("SELECT MAX(id) FROM machines")) {
        qDebug() << "查询最大机器ID失败: " << query.lastError().text();
        return false;
    }

    int maxId = 0;
    if (query.next() && !query.isNull(0)) { // 若表中有数据，取最大ID
        maxId = query.value(0).toInt();
    }

    // 若现有机器数量不足，补充插入（确保ID从1到count连续）
    if (maxId < count) {
        db.transaction(); // 事务批量处理，提高效率

        // 准备插入语句（使用参数绑定，避免SQL注入风险）
        query.prepare("INSERT INTO machines (id, is_running, is_used) "
                      "VALUES (:id, 1, 0)");

        for (int i = maxId + 1; i <= count; ++i) {
            query.bindValue(":id", i);
            if (!query.exec()) {
                qDebug() << "插入机器" << i << "失败: " << query.lastError().text();
                db.rollback(); // 插入失败回滚事务
                return false;
            }
        }

        db.commit(); // 全部插入成功后提交事务
    }

    return true;
}

// 用户注册
bool DatabaseManager::registerUser(const QString& username, const QString& password, const QString& name, const QString& phone) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, name, phone, balance) "
                  "VALUES (:username, :password, :name, :phone, 0)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // 实际应用中应加密存储
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);

    return query.exec();
}

// 用户登录
bool DatabaseManager::loginUser(const QString& username, const QString& password, QString& userId) {
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        userId = query.value(0).toString();
        return true;
    }
    return false;
}

// 管理员登录
bool DatabaseManager::loginAdmin(const QString& adminName, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT id FROM admins WHERE username = :username AND password = :password");
    query.bindValue(":username", adminName);
    query.bindValue(":password", password);

    return query.exec() && query.next();
}

// 获取用户余额
double DatabaseManager::getUserBalance(const QString& userId) {
    QSqlQuery query;
    query.prepare("SELECT balance FROM users WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return -1; // 错误
}

// 充值
bool DatabaseManager::rechargeBalance(const QString& userId, double amount) {
    if (amount <= 0) return false;

    db.transaction();

    // 更新余额
    QSqlQuery query;
    query.prepare("UPDATE users SET balance = balance + :amount WHERE id = :id");
    query.bindValue(":amount", amount);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        db.rollback();
        qDebug() << "充值失败: " << query.lastError().text();
        return false;
    }

    // 记录充值记录
    query.prepare("INSERT INTO recharges (user_id, amount, time) "
                  "VALUES (:user_id, :amount, :time)");
    query.bindValue(":user_id", userId);
    query.bindValue(":amount", amount);
    query.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        db.rollback();
        qDebug() << "记录充值失败: " << query.lastError().text();
        return false;
    }

    db.commit();
    return true;
}

// 获取机器状态
bool DatabaseManager::getMachineStatus(int machineId, bool& isRunning, bool& isUsed, QString& userId) {
    QSqlQuery query;
    query.prepare("SELECT is_running, is_used, user_id FROM machines WHERE id = :id");
    query.bindValue(":id", machineId);

    if (query.exec() && query.next()) {
        isRunning = query.value(0).toBool();
        isUsed = query.value(1).toBool();
        userId = query.value(2).toString();
        return true;
    }
    return false;
}

// 设置机器状态
bool DatabaseManager::setMachineStatus(int machineId, bool isRunning, bool isUsed, const QString& userId) {
    QSqlQuery query;
    query.prepare("UPDATE machines SET is_running = :is_running, is_used = :is_used, user_id = :user_id "
                  "WHERE id = :id");
    query.bindValue(":is_running", isRunning);
    query.bindValue(":is_used", isUsed);
    query.bindValue(":user_id", userId.isEmpty() ? QVariant(QVariant::Int) : userId);
    query.bindValue(":id", machineId);

    return query.exec();
}

// 获取所有机器状态
bool DatabaseManager::getAllMachinesStatus(QVector<QVector<QVariant>>& statusList) {
    statusList.clear();
    QSqlQuery query("SELECT id, is_running, is_used, user_id, start_time FROM machines ORDER BY id");

    while (query.next()) {
        QVector<QVariant> status;
        status << query.value(0) << query.value(1) << query.value(2) << query.value(3) << query.value(4);
        statusList.append(status);
    }

    return !statusList.isEmpty();
}

// 开始使用机器
bool DatabaseManager::startUsingMachine(const QString& userId, int machineId) {
    db.transaction();

    // 更新机器状态
    QSqlQuery query;
    query.prepare("UPDATE machines SET is_used = 1, user_id = :user_id, "
                  "start_time = :start_time WHERE id = :id");
    query.bindValue(":user_id", userId);
    query.bindValue(":start_time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":id", machineId);

    if (!query.exec()) {
        db.rollback();
        qDebug() << "更新机器状态失败: " << query.lastError().text();
        return false;
    }

    // 记录上机记录
    query.prepare("INSERT INTO usage_records (user_id, machine_id, start_time) "
                  "VALUES (:user_id, :machine_id, :start_time)");
    query.bindValue(":user_id", userId);
    query.bindValue(":machine_id", machineId);
    query.bindValue(":start_time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        db.rollback();
        qDebug() << "记录上机失败: " << query.lastError().text();
        return false;
    }

    db.commit();
    return true;
}

// 停止使用机器
bool DatabaseManager::stopUsingMachine(int machineId) {
    db.transaction();

    // 获取机器当前信息
    QSqlQuery query;
    query.prepare("SELECT user_id, start_time FROM machines WHERE id = :id");
    query.bindValue(":id", machineId);

    if (!query.exec() || !query.next()) {
        db.rollback();
        return false;
    }

    QString userId = query.value(0).toString();
    QString startTime = query.value(1).toString();

    // 计算时长和费用
    QDateTime start = QDateTime::fromString(startTime, "yyyy-MM-dd hh:mm:ss");
    QDateTime end = QDateTime::currentDateTime();
    int duration = start.secsTo(end) / 60; // 转换为分钟
    double cost = duration * 0.1; // 假设每分钟0.1元

    // 更新机器状态
    if (!query.exec(QString("UPDATE machines SET is_used = 0, user_id = NULL, start_time = NULL WHERE id = %1").arg(machineId))) {
        db.rollback();
        return false;
    }

    // 更新用户余额
    query.prepare("UPDATE users SET balance = balance - :cost WHERE id = :user_id");
    query.bindValue(":cost", cost);
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        db.rollback();
        return false;
    }

    // 更新使用记录
    query.prepare("UPDATE usage_records SET end_time = :end_time, duration = :duration, cost = :cost "
                  "WHERE user_id = :user_id AND machine_id = :machine_id AND end_time IS NULL");
    query.bindValue(":end_time", end.toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":duration", duration);
    query.bindValue(":cost", cost);
    query.bindValue(":user_id", userId);
    query.bindValue(":machine_id", machineId);

    if (!query.exec()) {
        db.rollback();
        return false;
    }

    db.commit();
    return true;
}

// 自动扣费
bool DatabaseManager::autoDeductFees() {
    // 1. 检查数据库连接是否有效
    if (!db.isOpen()) {
        qWarning() << "数据库未打开，无法执行自动扣费：" << db.lastError().text();
        return false;
    }

    // 2. 执行查询并检查是否成功（关键：避免无效查询导致的后续崩溃）
    QSqlQuery query;
    if (!query.exec("SELECT id, user_id, start_time FROM machines WHERE is_used = 1")) {
        qWarning() << "查询在用机器失败：" << query.lastError().text();
        return false; // 查询失败直接返回，避免进入循环
    }

    while (query.next()) {
        // 3. 检查查询结果字段是否存在（防止字段索引越界）
        if (query.record().count() < 3) {
            qWarning() << "查询结果字段不足，跳过当前记录";
            continue;
        }

        // 4. 提取字段值（添加空值检查）
        QVariant machineIdVar = query.value(0);
        QVariant userIdVar = query.value(1);
        QVariant startTimeStrVar = query.value(2);
        if (machineIdVar.isNull() || userIdVar.isNull() || startTimeStrVar.isNull()) {
            qWarning() << "记录包含空值，跳过（机器ID：" << machineIdVar.toString() << "）";
            continue;
        }

        int machineId = machineIdVar.toInt();
        QString userId = userIdVar.toString();
        QString startTimeStr = startTimeStrVar.toString();

        // 5. 解析时间（关键：检查格式是否正确，避免无效QDateTime）
        QDateTime startTime = QDateTime::fromString(startTimeStr, "yyyy-MM-dd hh:mm:ss");
        if (!startTime.isValid()) {
            qWarning() << "时间格式错误（" << startTimeStr << "），跳过机器ID：" << machineId;
            continue;
        }

        QDateTime currentTime = QDateTime::currentDateTime();
        if (currentTime < startTime) { // 防止系统时间异常导致的负时长
            qWarning() << "当前时间早于开始时间，跳过机器ID：" << machineId;
            continue;
        }

        int totalMinutes = startTime.secsTo(currentTime) / 60;
        if (totalMinutes < 30) { // 不足30分钟不扣费
            continue;
        }

        // 6. 计算费用（正常逻辑）
        int deductTimes = totalMinutes / 30;
        double costPerTime = 30 * 0.1; // 3元/30分钟
        double totalCost = deductTimes * costPerTime;

        // 7. 检查用户余额（处理用户不存在的情况）
        double balance = getUserBalance(userId);
        if (balance < 0) { // 假设getUserBalance返回-1表示用户不存在
            qWarning() << "用户不存在（ID：" << userId << "），强制停止机器ID：" << machineId;
            stopUsingMachine(machineId);
            continue;
        }
        if (balance < totalCost) {
            qWarning() << "用户余额不足（ID：" << userId << "），强制停止机器ID：" << machineId;
            stopUsingMachine(machineId);
            continue;
        }

        // 8. 事务处理（强化原子性和错误回滚）
        if (!db.transaction()) {
            qWarning() << "开启事务失败，跳过机器ID：" << machineId << "，错误：" << db.lastError().text();
            continue;
        }

        // 8.1 更新用户余额
        QSqlQuery updateBalance;
        updateBalance.prepare("UPDATE users SET balance = balance - :cost WHERE id = :user_id");
        updateBalance.bindValue(":cost", totalCost);
        updateBalance.bindValue(":user_id", userId);
        if (!updateBalance.exec()) {
            db.rollback();
            qWarning() << "更新用户余额失败（用户ID：" << userId << "），错误：" << updateBalance.lastError().text();
            continue;
        }

        // 8.2 重置机器计时起点
        QDateTime newStartTime = startTime.addSecs(deductTimes * 30 * 60);
        QSqlQuery updateMachine;
        updateMachine.prepare("UPDATE machines SET start_time = :new_time WHERE id = :machine_id");
        updateMachine.bindValue(":new_time", newStartTime.toString("yyyy-MM-dd hh:mm:ss"));
        updateMachine.bindValue(":machine_id", machineId);
        if (!updateMachine.exec()) {
            db.rollback();
            qWarning() << "更新机器时间失败（机器ID：" << machineId << "），错误：" << updateMachine.lastError().text();
            continue;
        }

        // 8.3 更新或创建使用记录
        QSqlQuery checkRecord;
        checkRecord.prepare("SELECT id FROM usage_records WHERE user_id = :user_id AND machine_id = :machine_id AND end_time IS NULL");
        checkRecord.bindValue(":user_id", userId);
        checkRecord.bindValue(":machine_id", machineId);
        if (!checkRecord.exec()) {
            db.rollback();
            qWarning() << "查询使用记录失败，错误：" << checkRecord.lastError().text();
            continue;
        }

        QSqlQuery updateRecord;
        if (checkRecord.next()) {
            updateRecord.prepare("UPDATE usage_records SET duration = duration + :add_minutes, cost = cost + :add_cost "
                                 "WHERE user_id = :user_id AND machine_id = :machine_id AND end_time IS NULL");
        } else {
            updateRecord.prepare("INSERT INTO usage_records (user_id, machine_id, start_time, duration, cost) "
                                 "VALUES (:user_id, :machine_id, :start_time, :duration, :cost)");
            updateRecord.bindValue(":start_time", startTime.toString("yyyy-MM-dd hh:mm:ss"));
        }
        updateRecord.bindValue(":add_minutes", deductTimes * 30);
        updateRecord.bindValue(":add_cost", totalCost);
        updateRecord.bindValue(":user_id", userId);
        updateRecord.bindValue(":machine_id", machineId);
        if (!updateRecord.exec()) {
            db.rollback();
            qWarning() << "更新使用记录失败，错误：" << updateRecord.lastError().text();
            continue;
        }

        // 提交事务
        if (!db.commit()) {
            db.rollback();
            qWarning() << "提交事务失败，机器ID：" << machineId << "，错误：" << db.lastError().text();
            continue;
        }
    }

    return true;
}


// 查询用户记录
QVector<QVector<QVariant>> DatabaseManager::queryUserRecords(const QString& condition) {
    QVector<QVector<QVariant>> result;
    QString sql = "SELECT id, username, name, phone, balance FROM users";
    if (!condition.isEmpty()) {
        sql += " WHERE " + condition;
    }

    QSqlQuery query(sql);
    while (query.next()) {
        QVector<QVariant> row;
        for (int i = 0; i < 5; ++i) {
            row.append(query.value(i));
        }
        result.append(row);
    }

    return result;
}

// 查询机器使用记录
QVector<QVector<QVariant>> DatabaseManager::queryMachineUsage(const QString& condition) {
    QVector<QVector<QVariant>> result;
    QString sql = "SELECT u.id, u.username, m.id, r.start_time, r.end_time, r.duration, r.cost "
                  "FROM usage_records r "
                  "JOIN users u ON r.user_id = u.id "
                  "JOIN machines m ON r.machine_id = m.id";
    if (!condition.isEmpty()) {
        sql += " WHERE " + condition;
    }
    sql += " ORDER BY r.start_time DESC";

    QSqlQuery query(sql);
    while (query.next()) {
        QVector<QVariant> row;
        for (int i = 0; i < 7; ++i) {
            row.append(query.value(i));
        }
        result.append(row);
    }

    return result;
}

// 查询充值记录
QVector<QVector<QVariant>> DatabaseManager::queryRechargeRecords(const QString& condition) {
    QVector<QVector<QVariant>> result;
    QString sql = "SELECT u.id, u.username, r.amount, r.time "
                  "FROM recharges r "
                  "JOIN users u ON r.user_id = u.id";
    if (!condition.isEmpty()) {
        sql += " WHERE " + condition;
    }
    sql += " ORDER BY r.time DESC";

    QSqlQuery query(sql);
    while (query.next()) {
        QVector<QVariant> row;
        for (int i = 0; i < 4; ++i) {
            row.append(query.value(i));
        }
        result.append(row);
    }

    return result;
}
