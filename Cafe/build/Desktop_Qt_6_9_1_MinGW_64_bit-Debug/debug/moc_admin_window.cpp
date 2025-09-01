/****************************************************************************
** Meta object code from reading C++ file 'admin_window.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../admin_window.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'admin_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11AdminWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto AdminWindow::qt_create_metaobjectdata<qt_meta_tag_ZN11AdminWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AdminWindow",
        "returnToLogin",
        "",
        "on_startMachineButton_clicked",
        "on_shutdownMachineButton_clicked",
        "on_forceLogoutButton_clicked",
        "on_queryUsersButton_clicked",
        "on_queryMachinesButton_clicked",
        "on_queryRechargesButton_clicked",
        "on_exitButton_clicked",
        "on_refreshTimer_timeout",
        "on_machineSelected",
        "machineId"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'returnToLogin'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'on_startMachineButton_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_shutdownMachineButton_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_forceLogoutButton_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_queryUsersButton_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_queryMachinesButton_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_queryRechargesButton_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_exitButton_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_refreshTimer_timeout'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_machineSelected'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AdminWindow, qt_meta_tag_ZN11AdminWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AdminWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AdminWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AdminWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11AdminWindowE_t>.metaTypes,
    nullptr
} };

void AdminWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AdminWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->returnToLogin(); break;
        case 1: _t->on_startMachineButton_clicked(); break;
        case 2: _t->on_shutdownMachineButton_clicked(); break;
        case 3: _t->on_forceLogoutButton_clicked(); break;
        case 4: _t->on_queryUsersButton_clicked(); break;
        case 5: _t->on_queryMachinesButton_clicked(); break;
        case 6: _t->on_queryRechargesButton_clicked(); break;
        case 7: _t->on_exitButton_clicked(); break;
        case 8: _t->on_refreshTimer_timeout(); break;
        case 9: _t->on_machineSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AdminWindow::*)()>(_a, &AdminWindow::returnToLogin, 0))
            return;
    }
}

const QMetaObject *AdminWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AdminWindowE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AdminWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void AdminWindow::returnToLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
