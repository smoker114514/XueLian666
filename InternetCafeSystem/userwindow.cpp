#include "userwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>

UserWindow::UserWindow(Database *db, int userId, QWidget *parent)
    : QWidget(parent), db(db), userId(userId)
{
    setupUI();
    setWindowTitle("用户中心");
    resize(800, 600);

    // 定时器更新机器状态
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &UserWindow::updateMachineStatus);
    statusTimer->start(5000); // 每5秒更新一次

    // 定时器检查余额
    balanceTimer = new QTimer(this);
    connect(balanceTimer, &QTimer::timeout, this, &UserWindow::checkBalance);
    balanceTimer->start(60000); // 每分钟检查一次

    refreshMachineStatus();
    refreshBalance();
}

UserWindow::~UserWindow()
{
    if (statusTimer) delete statusTimer;
    if (balanceTimer) delete balanceTimer;
}

void UserWindow::setUserId(int userId)
{
    this->userId = userId;
    refreshBalance();
    refreshMachineStatus();
}

void UserWindow::setupUI()
{
    // 创建控件
    usernameLabel = new QLabel();
    balanceLabel = new QLabel();

    QLabel *titleLabel = new QLabel("机器状态列表");
    QFont font = titleLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    titleLabel->setFont(font);

    // 机器状态表格
    machineTable = new QTableWidget();
    machineTable->setColumnCount(3);
    machineTable->setHorizontalHeaderLabels(QStringList() << "机器编号" << "状态" << "操作");
    machineTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    rechargeButton = new QPushButton("充值");
    useMachineButton = new QPushButton("使用选中机器");
    endSessionButton = new QPushButton("结束当前使用");
    logoutButton = new QPushButton("退出登录");

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(usernameLabel);
    infoLayout->addWidget(balanceLabel);
    infoLayout->addStretch();
    mainLayout->addLayout(infoLayout);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(machineTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(rechargeButton);
    buttonLayout->addWidget(useMachineButton);
    buttonLayout->addWidget(endSessionButton);
    buttonLayout->addWidget(logoutButton);
    mainLayout->addLayout(buttonLayout);

    // 连接信号槽
    connect(rechargeButton, &QPushButton::clicked, this, &UserWindow::onRechargeClicked);
    connect(useMachineButton, &QPushButton::clicked, this, &UserWindow::onUseMachineClicked);
    connect(endSessionButton, &QPushButton::clicked, this, &UserWindow::onEndSessionClicked);
    connect(logoutButton, &QPushButton::clicked, this, &UserWindow::onLogoutClicked);
}

void UserWindow::refreshMachineStatus()
{
    usernameLabel->setText("用户名: " + db->getUsername(userId));

    // 清空表格
    machineTable->setRowCount(0);

    // 获取所有机器
    QList<int> machineIds = db->getAllMachineIds();

    for (int machineId : machineIds) {
        MachineStatus status = db->getMachineStatus(machineId);
        int currentUserId = db->getMachineUserId(machineId);

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
            if (currentUserId == userId) {
                statusText = "正在使用 (自己)";
            } else {
                statusText = "正在使用";
            }
            statusColor = Qt::red;
        } else {
            statusText = "故障";
            statusColor = Qt::gray;
        }

        QTableWidgetItem *statusItem = new QTableWidgetItem(statusText);
        statusItem->setBackground(QBrush(statusColor));
        machineTable->setItem(row, 1, statusItem);

        // 操作按钮
        QPushButton *button = new QPushButton();

        if (status == IDLE) {
            button->setText("使用");
            connect(button, &QPushButton::clicked, [=]() {
                if (db->startUsingMachine(machineId, userId)) {
                    QMessageBox::information(this, "成功", "已开始使用机器 " + QString::number(machineId));
                    refreshMachineStatus();
                } else {
                    if (db->getAccountBalance(userId) <= 0) {
                        QMessageBox::warning(this, "失败", "余额不足，请先充值!");
                    } else {
                        QMessageBox::warning(this, "失败", "无法使用该机器!");
                    }
                }
            });
        } else if (status == IN_USE && currentUserId == userId) {
            button->setText("结束使用");
            connect(button, &QPushButton::clicked, [=]() {
                if (QMessageBox::question(this, "确认", "确定要结束使用机器 " + QString::number(machineId) + " 吗?")
                    == QMessageBox::Yes) {
                    if (db->stopUsingMachine(machineId)) {
                        QMessageBox::information(this, "成功", "已结束使用机器 " + QString::number(machineId));
                        refreshMachineStatus();
                        refreshBalance();
                    } else {
                        QMessageBox::warning(this, "失败", "无法结束使用该机器!");
                    }
                }
            });
        } else {
            button->setText("不可用");
            button->setEnabled(false);
        }

        machineTable->setCellWidget(row, 2, button);
    }
}

void UserWindow::refreshBalance()
{
    double balance = db->getAccountBalance(userId);
    balanceLabel->setText(QString("余额: ¥%1").arg(balance, 0, 'f', 2));

    // 如果余额不足，显示警告
    if (balance <= 0) {
        balanceLabel->setStyleSheet("color: red; font-weight: bold;");
    } else {
        balanceLabel->setStyleSheet("");
    }
}

void UserWindow::onRechargeClicked()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "充值", "请输入充值金额:",
                                            50, 10, 10000, 2, &ok);

    if (ok && amount > 0) {
        if (db->rechargeAccount(userId, amount)) {
            QMessageBox::information(this, "成功", QString("充值 ¥%1 成功!").arg(amount));
            refreshBalance();
        } else {
            QMessageBox::warning(this, "失败", "充值失败!");
        }
    }
}

void UserWindow::onUseMachineClicked()
{
    QList<QTableWidgetItem *> selectedItems = machineTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择一台机器!");
        return;
    }

    int row = selectedItems.first()->row();
    int machineId = machineTable->item(row, 0)->text().toInt();

    if (db->getMachineStatus(machineId) != IDLE) {
        QMessageBox::warning(this, "失败", "所选机器不可用!");
        return;
    }

    if (db->startUsingMachine(machineId, userId)) {
        QMessageBox::information(this, "成功", "已开始使用机器 " + QString::number(machineId));
        refreshMachineStatus();
    } else {
        if (db->getAccountBalance(userId) <= 0) {
            QMessageBox::warning(this, "失败", "余额不足，请先充值!");
        } else {
            QMessageBox::warning(this, "失败", "无法使用该机器!");
        }
    }
}

void UserWindow::onEndSessionClicked()
{
    // 查找用户正在使用的机器
    QList<int> machineIds = db->getAllMachineIds();
    bool found = false;

    for (int machineId : machineIds) {
        if (db->getMachineStatus(machineId) == IN_USE && db->getMachineUserId(machineId) == userId) {
            if (QMessageBox::question(this, "确认", "确定要结束使用机器 " + QString::number(machineId) + " 吗?")
                == QMessageBox::Yes) {
                if (db->stopUsingMachine(machineId)) {
                    QMessageBox::information(this, "成功", "已结束使用机器 " + QString::number(machineId));
                    refreshMachineStatus();
                    refreshBalance();
                    found = true;
                } else {
                    QMessageBox::warning(this, "失败", "无法结束使用该机器!");
                }
            }
            return;
        }
    }

    if (!found) {
        QMessageBox::information(this, "提示", "您当前没有使用任何机器!");
    }
}

void UserWindow::onLogoutClicked()
{
    // 检查用户是否正在使用机器
    QList<int> machineIds = db->getAllMachineIds();
    for (int machineId : machineIds) {
        if (db->getMachineStatus(machineId) == IN_USE && db->getMachineUserId(machineId) == userId) {
            if (QMessageBox::question(this, "警告", "您正在使用机器，确定要退出吗?\n退出将结束当前使用 session!")
                == QMessageBox::Yes) {
                db->stopUsingMachine(machineId);
                break;
            } else {
                return;
            }
        }
    }

    this->hide();
    parentWidget()->show();
}

void UserWindow::updateMachineStatus()
{
    refreshMachineStatus();
}

void UserWindow::checkBalance()
{
    refreshBalance();

    // 余额不足提醒
    if (db->getAccountBalance(userId) <= 10) {
        QList<int> machineIds = db->getAllMachineIds();
        for (int machineId : machineIds) {
            if (db->getMachineStatus(machineId) == IN_USE && db->getMachineUserId(machineId) == userId) {
                QMessageBox::warning(this, "余额不足", "您的余额已不足10元，请及时充值!");
                break;
            }
        }
    }
}
