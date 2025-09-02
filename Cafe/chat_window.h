#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QWidget>
#include <QColor>
#include <QShowEvent>  // 新增：包含QShowEvent头文件
#include <QResizeEvent> // 新增：包含QResizeEvent头文件

// 前向声明
class DeepSeekClient;

QT_BEGIN_NAMESPACE
namespace Ui { class ChatWindow; }
QT_END_NAMESPACE

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    // 构造函数（支持父窗口指针，符合项目窗口创建规范）
    explicit ChatWindow(QWidget *parent = nullptr);
    // 析构函数（使用override确保正确重写）
    ~ChatWindow() override;

    // 设置DeepSeek API密钥（与业务逻辑分离）
    void setApiKey(const QString &apiKey);
    // 设置当前用户ID（用于个性化交互）
    void setUserId(const QString &userId);
    void showEvent(QShowEvent *event) override;

signals:
    // 返回用户主窗口信号（与UserWindow的returnToLogin信号风格一致）
    void returnToUserWindow();

private slots:
    // 发送按钮点击事件（遵循on_<组件名>_<事件>命名规范）
    void on_sendButton_clicked();
    // 返回按钮点击事件
    void on_backButton_clicked();
    // 接收大模型回复的槽函数
    void onReplyReceived(const QString &reply);
    // 错误处理槽函数
    void onErrorOccurred(const QString &errorMsg);

private:
    // 初始化UI组件（封装初始化逻辑）
    void initUI();
    // 初始化信号槽连接（集中管理连接关系）
    void initConnections();
    // 向聊天区域添加消息（统一消息格式化逻辑）
    void addMessageToDisplay(const QString &sender, const QString &message, const QColor &color);
    // 添加系统消息（如状态提示、错误信息）
    void addSystemMessage(const QString &message);

    // UI设计器生成的界面对象
    Ui::ChatWindow *ui;
    // 大模型交互客户端（前向声明，减少头文件依赖）
    DeepSeekClient *deepSeekClient;
    // 当前登录用户ID（与UserWindow保持一致的用户标识方式）
    QString userId;
};

#endif // CHAT_WINDOW_H
