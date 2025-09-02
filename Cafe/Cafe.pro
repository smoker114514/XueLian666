QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_window.cpp \
    chat_window.cpp \
    database_manager.cpp \
    deepseek_client.cpp \
    login_window.cpp \
    main.cpp \
    main_window.cpp \
    register_window.cpp \
    user_window.cpp

HEADERS += \
    admin_window.h \
    chat_window.h \
    database_manager.h \
    deepseek_client.h \
    login_window.h \
    main_window.h \
    register_window.h \
    user_window.h

FORMS += \
    admin_window.ui \
    chat_window.ui \
    login_window.ui \
    main_window.ui \
    register_window.ui \
    user_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc
