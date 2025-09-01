#include "adminwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QDateTime>

AdminWindow::AdminWindow(Database *db, QWidget *parent)
    : QWidget(parent), db(db)
{
    setupUI();
    setWindowTitle("管理员中心");
    resize(1000, 600);

    // 定时器更新机器状态
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &AdminWindow::updateMachineStatus);
    statusTimer->start(5000); // 每5秒更新一次

    refreshMachineStatus();
    refreshRecords();
}

AdminWindow::~AdminWindow()
{
    if (statusTimer) delete statusTimer;
}

void AdminWindow::setupUI()
{
    // 创建标签页
    tabWidget = new QTabWidget();

    // 机器状态标签页
    QWidget *machineWidget = new QWidget();

    // 机器状态表格
    machineTable = new QTableWidget();
    machineTable->setColumnCount(4);
    machineTable->setHorizontalHeaderLabels(QStringList() << "机器编号" << "状态" << "当前用户" << "操作");
    machineTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 按钮
    shutdownButton = new QPushButton("关闭选中机器");
    restartButton = new QPushButton("重启选中机器");
    refreshButton = new QPushButton("刷新状态");
    viewRecordsButton = new QPushButton("查看消费记录");
    logoutButton = new QPushButton("退出登录");

    // 机器标签页布局
    QVBoxLayout *machineLayout = new QVBoxLayout(machineWidget);
    machineLayout->addWidget(machineTable);

    QHBoxLayout *machineButtonLayout = new QHBoxLayout();
    machineButtonLayout->addWidget(shutdownButton);
    machineButtonLayout->addWidget(restartButton);
    machineButtonLayout->addWidget(refreshButton);
    machineButtonLayout->addWidget(viewRecordsButton);
    machineButtonLayout->addWidget(logoutButton);
    machineLayout->addLayout(machineButtonLayout);

    // 消费记录标签页
    QWidget *recordWidget = new QWidget();

    // 记录表格
    recordTable = new QTableWidget();
    recordTable->setColumnCount(6);
    recordTable->setHorizontalHeaderLabels(QStringList() << "记录ID" << "用户ID" << "用户名"
                                                         << "机器ID" << "时间" << "消费金额");
    recordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 记录标签页布局
    QVBoxLayout *recordLayout = new QVBoxLayout(recordWidget);
    recordLayout->addWidget(recordTable);

    // 添加标签页
    tabWidget->addTab(machineWidget, "机器管理");
    tabWidget->addTab(recordWidget, "消费记录");

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);

    // 连接信号槽
    connect(shutdownButton, &QPushButton::clicked, this, &AdminWindow::onShutdownClicked);
    connect(restartButton, &QPushButton::clicked, this, &AdminWindow::onRestartClicked);
    connect(refreshButton, &QPushButton::clicked, this, &AdminWindow::refreshMachineStatus);
    connect(viewRecordsButton, &QPushButton::clicked, [=]() {
        tabWidget->setCurrentIndex(1);
        refreshRecords();
    });
    connect(logoutButton, &QPushButton::clicked, this, &AdminWindow::onLogoutClicked);
}

void AdminWindow::refreshMachineStatus()
{
    // 清空表格
    machineTable->setRowCount(0);

    // 获取所有机器
    QList<int> machineIds = db->getAllMachineIds();

    for (int machineId : machineIds) {
        MachineStatus status = db->getMachineStatus(machineId);
        int currentUserId = db->getMachineUserId(machineId);
        QString username = db->getUsername(currentUserId);

        // 添加行
        int row = machineTable->rowCount();
        machineTable->insertRow(row);

        // 机器编号
        machineTable->setItem(row, 0, new QTableWidgetItem(QString::number(machineId)));

        // 状态
        QString statusText;
        QColor statusColor;

        if (status == IDLE) {
            statusText = "空闲";
            statusColor = Qt::green;
        } else if (status == IN_USE) {
            statusText = "正在使用";
            statusColor = Qt::red;
        } else {
            statusText = "故障";
            statusColor = Qt::gray;
        }

        QTableWidgetItem *statusItem = new QTableWidgetItem(statusText);
        statusItem->setBackground(QBrush(statusColor));
        machineTable->setItem(row, 1, statusItem);

        // 当前用户
        machineTable->setItem(row, 2, new QTableWidgetItem(currentUserId > 0 ? username : "无"));

        // 操作按钮
        QWidget *buttonWidget = new QWidget();
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setContentsMargins(2, 2, 2, 2);

        QPushButton *startButton = new QPushButton("启用");
        QPushButton *stopButton = new QPushButton("停用");

        buttonLayout->addWidget(startButton);
        buttonLayout->addWidget(stopButton);

        // 根据当前状态设置按钮状态
        if (status == MALFUNCTION) {
            startButton->setEnabled(true);
            stopButton->setEnabled(false);
        } else {
            startButton->setEnabled(false);
            stopButton->setEnabled(true);
        }

        // 绑定按钮事件
        connect(startButton, &QPushButton::clicked, [=]() {
            if (db->setMachineStatus(machineId, IDLE)) {
                QMessageBox::information(this, "成功", "机器 " + QString::number(machineId) + " 已启用");
                refreshMachineStatus();
            } else {
                QMessageBox::warning(this, "失败", "无法启用机器 " + QString::number(machineId));
            }
        });

        connect(stopButton, &QPushButton::clicked, [=]() {
            // 如果机器正在使用，先结束使用
            if (status == IN_USE) {
                if (QMessageBox::question(this, "确认", "机器 " + QString::number(machineId) + " 正在被使用，确定要停用吗?")
                    == QMessageBox::Yes) {
                    db->stopUsingMachine(machineId);
                } else {
                    return;
                }
            }

            if (db->setMachineStatus(machineId, MALFUNCTION)) {
                QMessageBox::information(this, "成功", "机器 " + QString::number(machineId) + " 已停用");
                refreshMachineStatus();
            } else {
                QMessageBox::warning(this, "失败", "无法停用机器 " + QString::number(machineId));
            }
        });

        machineTable->setCellWidget(row, 3, buttonWidget);
    }
}

void AdminWindow::refreshRecords()
{
    // 清空表格
    recordTable->setRowCount(0);

    // 获取消费记录
    QList<QMap<QString, QVariant>> records = db->getConsumptionRecords(-1, 100);

    for (const auto &record : records) {
        int row = recordTable->rowCount();
        recordTable->insertRow(row);

        recordTable->setItem(row, 0, new QTableWidgetItem(record["id"].toString()));
        recordTable->setItem(row, 1, new QTableWidgetItem(record["user_id"].toString()));
        recordTable->setItem(row, 2, new QTableWidgetItem(db->getUsername(record["user_id"].toInt())));
        recordTable->setItem(row, 3, new QTableWidgetItem(record["machine_id"].toString()));

        QDateTime startTime = record["start_time"].toDateTime();
        QDateTime endTime = record["end_time"].toDateTime();
        recordTable->setItem(row, 4, new QTableWidgetItem(
                                         QString("%1 至 %2").arg(startTime.toString("yyyy-MM-dd HH:mm"))
                                             .arg(endTime.toString("HH:mm"))));

        recordTable->setItem(row, 5, new QTableWidgetItem(
                                         QString("¥%1").arg(record["cost"].toDouble(), 0, 'f', 2)));
    }
}

void AdminWindow::onShutdownClicked()
{
    QList<QTableWidgetItem *> selectedItems = machineTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择一台机器!");
        return;
    }

    int row = selectedItems.first()->row();
    int machineId = machineTable->item(row, 0)->text().toInt();

    // 如果机器正在使用，先结束使用
    if (db->getMachineStatus(machineId) == IN_USE) {
        if (QMessageBox::question(this, "确认", "机器 " + QString::number(machineId) + " 正在被使用，确定要关闭吗?")
            == QMessageBox::Yes) {
            db->stopUsingMachine(machineId);
        } else {
            return;
        }
    }

    if (db->setMachineStatus(machineId, MALFUNCTION)) {
        QMessageBox::information(this, "成功", "机器 " + QString::number(machineId) + " 已关闭");
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "无法关闭机器 " + QString::number(machineId));
    }
}

void AdminWindow::onRestartClicked()
{
    QList<QTableWidgetItem *> selectedItems = machineTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择一台机器!");
        return;
    }

    int row = selectedItems.first()->row();
    int machineId = machineTable->item(row, 0)->text().toInt();
    int currentUserId = db->getMachineUserId(machineId);

    // 如果机器正在使用，先结束使用
    if (db->getMachineStatus(machineId) == IN_USE) {
        if (QMessageBox::question(this, "确认", "机器 " + QString::number(machineId) + " 正在被使用，确定要重启吗?")
            == QMessageBox::Yes) {
            db->stopUsingMachine(machineId);
        } else {
            return;
        }
    }

    // 先停用再启用，模拟重启
    if (db->setMachineStatus(machineId, MALFUNCTION) &&
        db->setMachineStatus(machineId, IDLE)) {
        QMessageBox::information(this, "成功", "机器 " + QString::number(machineId) + " 已重启");
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "无法重启机器 " + QString::number(machineId));
    }
}

void AdminWindow::onLogoutClicked()
{
    this->hide();
    parentWidget()->show();
}

void AdminWindow::updateMachineStatus()
{
    refreshMachineStatus();
}
