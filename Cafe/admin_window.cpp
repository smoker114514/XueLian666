#include "admin_window.h"
#include "ui_admin_window.h"
#include <QMessageBox>
#include <QDateTime>

AdminWindow::AdminWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminWindow)
    , selectedMachineId(-1) {
    ui->setupUi(this);
    ui->machineMonitorWidget->setRowCount(5);
    ui->machineMonitorWidget->setColumnCount(6);
    ui->machineMonitorWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->machineMonitorWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->machineMonitorWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    refreshTimer = new QTimer();
    connect(refreshTimer, &QTimer::timeout, this, &AdminWindow::on_refreshTimer_timeout);
    connect(ui->machineMonitorWidget, &QTableWidget::itemClicked, this, [this](QTableWidgetItem *item) {
        if (item) {
            // 从"机器X"中提取ID（如"机器1"→1）
            QString text = item->text();
            int machineId = text.remove("机器").toInt();
            this->selectedMachineId = machineId; // 更新选中的机器ID
            item->setSelected(true); // 高亮选中项
        }
    });
    refreshTimer->start(10000);
}

AdminWindow::~AdminWindow() {
    delete ui;
    delete refreshTimer;
}

void AdminWindow::refreshMachineStatus()
{
    QVector<QVector<QVariant>> statusList;
    if (DatabaseManager::getInstance().getAllMachinesStatus(statusList)) {
        updateMachineMonitor(statusList); // 调用自定义更新方法
    }
}
void AdminWindow::updateMachineMonitor(const QVector<QVector<QVariant>>& statusList)
{
    ui->machineMonitorWidget->clearContents(); // 清空表格内容

    for (const auto& status : statusList) {
        int machineId = status[0].toInt();
        bool isRunning = status[1].toBool();
        bool isUsed = status[2].toBool();

        // 计算表格行列（机器ID 1-30对应5行6列）
        int row = (machineId - 1) / 6;
        int col = (machineId - 1) % 6;

        QTableWidgetItem* item = new QTableWidgetItem(QString("机器%1").arg(machineId));
        item->setTextAlignment(Qt::AlignCenter); // 文字居中

        // 设置背景色：绿色=空闲，红色=使用中，灰色=关闭
        if (!isRunning) {
            item->setBackground(QColor(200, 200, 200));
        } else if (isUsed) {
            item->setBackground(QColor(255, 100, 100));
        } else {
            item->setBackground(QColor(100, 255, 100));
        }

        ui->machineMonitorWidget->setItem(row, col, item);
    }
}
void AdminWindow::on_startMachineButton_clicked() {
    if (selectedMachineId == -1) {
        QMessageBox::warning(this, "警告", "请先选择一台机器！");
        return;
    }


    // 启动机器（设置为运行状态，不改变使用状态）
    bool isRunning, isUsed;
    QString userId;
    DatabaseManager::getInstance().getMachineStatus(selectedMachineId, isRunning, isUsed, userId);

    if (DatabaseManager::getInstance().setMachineStatus(selectedMachineId, true, isUsed, userId)) {
        QMessageBox::information(this, "成功", QString("机器 %1 已启动！").arg(selectedMachineId));
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "操作失败！");
    }
}

void AdminWindow::on_shutdownMachineButton_clicked() {
    if (selectedMachineId == -1) {
        QMessageBox::warning(this, "警告", "请先选择一台机器！");
        return;
    }

    // 如果机器正在被使用，提示
    bool isRunning, isUsed;
    QString userId;
    DatabaseManager::getInstance().getMachineStatus(selectedMachineId, isRunning, isUsed, userId);

    if (isUsed) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认", "该机器正在被使用，确定要关闭吗？将强制下机。",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }

        // 强制下机
        DatabaseManager::getInstance().stopUsingMachine(selectedMachineId);
    }

    // 关闭机器
    if (DatabaseManager::getInstance().setMachineStatus(selectedMachineId, false, false)) {
        QMessageBox::information(this, "成功", QString("机器 %1 已关闭！").arg(selectedMachineId));
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "操作失败！");
    }
}

void AdminWindow::on_forceLogoutButton_clicked() {
    if (selectedMachineId == -1) {
        QMessageBox::warning(this, "警告", "请先选择一台机器！");
        return;
    }

    // 检查机器是否在使用中
    bool isRunning, isUsed;
    QString userId;
    DatabaseManager::getInstance().getMachineStatus(selectedMachineId, isRunning, isUsed, userId);

    if (!isUsed) {
        QMessageBox::information(this, "提示", "该机器当前未被使用！");
        return;
    }

    if (DatabaseManager::getInstance().stopUsingMachine(selectedMachineId)) {
        QMessageBox::information(this, "成功", "已强制用户下机！");
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "操作失败！");
    }
}
void AdminWindow::populateDataTable(const QVector<QVector<QVariant>>& data, const QStringList& headers) {
    ui->dataTableWidget->setColumnCount(headers.size());
    ui->dataTableWidget->setHorizontalHeaderLabels(headers);
    ui->dataTableWidget->setRowCount(data.size());

    for (int row = 0; row < data.size(); ++row) {
        for (int col = 0; col < data[row].size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(data[row][col].toString());
            ui->dataTableWidget->setItem(row, col, item);
        }
    }
}
void AdminWindow::on_queryUsersButton_clicked() {
    QVector<QVector<QVariant>> userData = DatabaseManager::getInstance().queryUserRecords();
    QStringList headers = {"ID", "用户名", "姓名", "电话", "余额"};
    populateDataTable(userData, headers);
}

void AdminWindow::on_queryMachinesButton_clicked() {
    QVector<QVector<QVariant>> machineData = DatabaseManager::getInstance().queryMachineUsage();
    QStringList headers = {"用户ID", "用户名", "机器ID", "开始时间", "结束时间", "时长(分钟)", "费用"};
    populateDataTable(machineData, headers);
}

void AdminWindow::on_queryRechargesButton_clicked() {
    QVector<QVector<QVariant>> rechargeData = DatabaseManager::getInstance().queryRechargeRecords();
    QStringList headers = {"用户ID", "用户名", "金额", "时间"};
    populateDataTable(rechargeData, headers);
}

void AdminWindow::on_exitButton_clicked() {
    emit returnToLogin();
    this->hide();
}

void AdminWindow::on_refreshTimer_timeout() {
    refreshMachineStatus();
    DatabaseManager::getInstance().autoDeductFees();
}

void AdminWindow::on_machineSelected(int machineId) {
    selectedMachineId = machineId;
}
