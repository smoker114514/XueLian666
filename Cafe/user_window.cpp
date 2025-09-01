#include "user_window.h"
#include "ui_user_window.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QPalette>

UserWindow::UserWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
    , selectedMachineId(-1)
    , isUsingMachine(false) {
    ui->setupUi(this);
    this->setAutoFillBackground(true);

    // 2. 加载背景图片（从资源文件）
    QPixmap bgPixmap(":/picture_source/1.jpeg"); // 资源路径必须正确
    if (bgPixmap.isNull()) {
        qDebug() << "错误：无法加载背景图！";
        return; // 加载失败则退出
    }

    // 3. 缩放图片（根据需求调整缩放模式）
    QPixmap scaledPixmap = bgPixmap.scaled(
        this->size(),        // 缩放至窗口大小
        Qt::IgnoreAspectRatio,

        Qt::SmoothTransformation // 平滑缩放，画质更好
        );

    // 4. 设置为窗口背景
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scaledPixmap)); // 将图片设为窗口背景
    this->setPalette(palette);

    // 5. 窗口大小变化时，重新缩放背景图（可选，确保自适应窗口）
    connect(this, &UserWindow::resizeEvent, [this, bgPixmap](QResizeEvent *event) {
        Q_UNUSED(event); // 忽略未使用的参数
        QPixmap scaledPixmap = bgPixmap.scaled(
            this->size(),
            Qt::KeepAspectRatio, // 与上面缩放模式保持一致
            Qt::SmoothTransformation
            );
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, QBrush(scaledPixmap));
        this->setPalette(palette);
    });
    if (!ui->machineStatusWidget) {
        qFatal("Error: machineStatusWidget not found in UI!"); // 强制退出并提示
    }

    // ########## 新增表格初始化代码 ##########
    // 设置表格行列数（5行6列，对应30台机器）
    ui->machineStatusWidget->setRowCount(5);
    ui->machineStatusWidget->setColumnCount(6);
    // 禁止表格编辑（避免用户误操作）
    ui->machineStatusWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表头拉伸模式（填满窗口）
    ui->machineStatusWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->machineStatusWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // #######################################

    // 初始化定时器（先停止，显示后再启动）
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, [this]() {
        refreshMachineStatus(); // 只刷新机器状态
        // 移除 DatabaseManager::getInstance().autoDeductFees(); 调用
    });
    // 绑定表格点击事件（保持原逻辑）
    connect(ui->machineStatusWidget, &QTableWidget::itemClicked, this, [this](QTableWidgetItem *item) {
        if (item) {
            int machineId = item->text().remove("机器").toInt();
            this->selectedMachineId = machineId;
            item->setSelected(true);
        }
    });
    statusTimer->stop(); // 初始不启动，避免提前触发
}

UserWindow::~UserWindow() {
    delete ui;
    delete statusTimer;
}

void UserWindow::setUserId(const QString& userId) {
    this->userId = userId;
}

void UserWindow::refreshUserInfo() {
    if (userId.isEmpty()) return;
    if (!ui->balanceLabel) {
        qWarning("balanceLabel is not initialized!");
        return;
    }

    // 刷新余额信息
    double balance = DatabaseManager::getInstance().getUserBalance(userId);
    ui->balanceLabel->setText(QString("当前余额: ¥%1").arg(balance));

    // 刷新机器状态
    refreshMachineStatus();
}

void UserWindow::on_rechargeButton_clicked() {
    bool ok;
    double amount = QInputDialog::getDouble(this, "充值", "请输入充值金额:", 50, 10, 1000, 1, &ok);

    if (ok && amount > 0) {
        if (DatabaseManager::getInstance().rechargeBalance(userId, amount)) {
            QMessageBox::information(this, "成功", QString("充值成功！当前余额: ¥%1")
                                                       .arg(DatabaseManager::getInstance().getUserBalance(userId)));
            refreshUserInfo();
        } else {
            QMessageBox::warning(this, "失败", "充值失败！");
        }
    }
}

void UserWindow::on_startButton_clicked() {
    if (isUsingMachine) {
        QMessageBox::information(this, "提示", "您已经在使用一台机器了！");
        return;
    }

    if (selectedMachineId == -1) {
        QMessageBox::warning(this, "警告", "请先选择一台机器！");
        return;
    }

    // 检查机器是否可用
    bool isRunning, isUsed;
    QString usingUserId;
    if (!DatabaseManager::getInstance().getMachineStatus(selectedMachineId, isRunning, isUsed, usingUserId) ||
        !isRunning || isUsed) {
        QMessageBox::warning(this, "警告", "选中的机器不可用！");
        return;
    }

    // 检查余额
    if (DatabaseManager::getInstance().getUserBalance(userId) < 5) { // 最低5元
        QMessageBox::warning(this, "警告", "余额不足，请先充值！");
        return;
    }

    if (DatabaseManager::getInstance().startUsingMachine(userId, selectedMachineId)) {
        QMessageBox::information(this, "成功", "开始使用机器！");
        isUsingMachine = true;
        refreshMachineStatus();
    } else {
        QMessageBox::warning(this, "失败", "操作失败！");
    }
}

void UserWindow::on_stopButton_clicked() {
    if (!isUsingMachine) {
        QMessageBox::information(this, "提示", "您没有在使用任何机器！");
        return;
    }

    if (DatabaseManager::getInstance().stopUsingMachine(selectedMachineId)) {
        QMessageBox::information(this, "成功", "已停止使用机器！");
        isUsingMachine = false;
        selectedMachineId = -1;
        refreshMachineStatus();
        refreshUserInfo(); // 刷新余额
    } else {
        QMessageBox::warning(this, "失败", "操作失败！");
    }
}

void UserWindow::on_exitButton_clicked() {
    // 如果正在使用机器，提示下机
    if (isUsingMachine) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认", "您正在使用机器，确定要退出吗？将自动下机。",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            DatabaseManager::getInstance().stopUsingMachine(selectedMachineId);
        } else {
            return;
        }
    }

    emit returnToLogin();
    this->hide();
}
void UserWindow::updateMachineStatus(const QVector<QVector<QVariant>>& statusList) {
    ui->machineStatusWidget->clearContents(); // 清空表格

    for (const auto& status : statusList) {
        int machineId = status[0].toInt();
        // ########## 新增ID范围检查 ##########
        if (machineId < 1 || machineId > 30) {
            // 跳过无效ID，避免越界
            continue;
        }
        // ####################################

        bool isRunning = status[1].toBool();
        bool isUsed = status[2].toBool();

        // 计算行列（仅对1-30有效）
        int row = (machineId - 1) / 6;
        int col = (machineId - 1) % 6;

        QTableWidgetItem* item = new QTableWidgetItem(QString("机器%1").arg(machineId));
        item->setTextAlignment(Qt::AlignCenter);

        // 设置背景色（保持原逻辑）
        if (!isRunning) {
            item->setBackground(QColor(200, 200, 200));
        } else if (isUsed) {
            item->setBackground(QColor(255, 100, 100));
        } else {
            item->setBackground(QColor(100, 255, 100));
        }

        ui->machineStatusWidget->setItem(row, col, item);
    }
}
void UserWindow::refreshMachineStatus() {
    QVector<QVector<QVariant>> statusList;
    if (DatabaseManager::getInstance().getAllMachinesStatus(statusList)) {
        updateMachineStatus(statusList);
    }

    // 自动扣费

}

void UserWindow::on_machineSelected(int machineId) {
    selectedMachineId = machineId;
}
void UserWindow::showEvent(QShowEvent *event) {
    // 先调用父类方法完成窗口初始化
    QWidget::showEvent(event);
    // 启动定时器（30秒刷新一次）
    statusTimer->start(30000);
    // 立即刷新一次状态，避免初始空白
    refreshMachineStatus();
}
