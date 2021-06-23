/****************************************************************************
** Meta object code from reading C++ file 'RemoteMonitoring.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../remote_monitoring/RemoteMonitoring.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RemoteMonitoring.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RemoteMonitoring_t {
    QByteArrayData data[7];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RemoteMonitoring_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RemoteMonitoring_t qt_meta_stringdata_RemoteMonitoring = {
    {
QT_MOC_LITERAL(0, 0, 16), // "RemoteMonitoring"
QT_MOC_LITERAL(1, 17, 16), // "remote_connected"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 19), // "remote_disconnected"
QT_MOC_LITERAL(4, 55, 22), // "connect_remote_monitor"
QT_MOC_LITERAL(5, 78, 25), // "disconnect_remote_monitor"
QT_MOC_LITERAL(6, 104, 11) // "do_finished"

    },
    "RemoteMonitoring\0remote_connected\0\0"
    "remote_disconnected\0connect_remote_monitor\0"
    "disconnect_remote_monitor\0do_finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RemoteMonitoring[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x09 /* Protected */,
       5,    0,   42,    2, 0x09 /* Protected */,
       6,    0,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RemoteMonitoring::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RemoteMonitoring *_t = static_cast<RemoteMonitoring *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->remote_connected(); break;
        case 1: _t->remote_disconnected(); break;
        case 2: _t->connect_remote_monitor(); break;
        case 3: _t->disconnect_remote_monitor(); break;
        case 4: _t->do_finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RemoteMonitoring::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RemoteMonitoring::remote_connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RemoteMonitoring::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RemoteMonitoring::remote_disconnected)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RemoteMonitoring::staticMetaObject = {
    { &QProcess::staticMetaObject, qt_meta_stringdata_RemoteMonitoring.data,
      qt_meta_data_RemoteMonitoring,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RemoteMonitoring::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RemoteMonitoring::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RemoteMonitoring.stringdata0))
        return static_cast<void*>(const_cast< RemoteMonitoring*>(this));
    return QProcess::qt_metacast(_clname);
}

int RemoteMonitoring::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProcess::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void RemoteMonitoring::remote_connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void RemoteMonitoring::remote_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
