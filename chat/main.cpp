#include "chatserver.h"
#include "chatclient.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Qt聊天程序");
    a.setApplicationVersion("1.0");

    // 解析命令行参数，区分启动服务器还是客户端
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt聊天程序");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption serverOption("server", "启动服务器模式");
    parser.addOption(serverOption);

    QCommandLineOption clientOption("client", "启动客户端模式");
    parser.addOption(clientOption);

    parser.process(a);

    // 如果没有指定模式，默认启动客户端
    if (parser.isSet(serverOption)) {
        ChatServer server;
        server.resize(400, 500);
        server.show();
        return a.exec();
    } else {
        ChatClient client;
        client.resize(400, 500);
        client.show();
        return a.exec();
    }
}
