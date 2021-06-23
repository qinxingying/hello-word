/****************************************************************************
** Meta object code from reading C++ file 'DopplerDrawScan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../draw_scan/DopplerDrawScan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DopplerDrawScan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DopplerDrawScan_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DopplerDrawScan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DopplerDrawScan_t qt_meta_stringdata_DopplerDrawScan = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DopplerDrawScan"
QT_MOC_LITERAL(1, 16, 19), // "signalScanRangeMove"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "nType_"
QT_MOC_LITERAL(4, 44, 7), // "nStart_"
QT_MOC_LITERAL(5, 52, 6), // "nStop_"
QT_MOC_LITERAL(6, 59, 20), // "signalIndexRangeMove"
QT_MOC_LITERAL(7, 80, 5) // "cType"

    },
    "DopplerDrawScan\0signalScanRangeMove\0"
    "\0nType_\0nStart_\0nStop_\0signalIndexRangeMove\0"
    "cType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DopplerDrawScan[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       6,    4,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double,    3,    7,    4,    5,

       0        // eod
};

void DopplerDrawScan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DopplerDrawScan *_t = static_cast<DopplerDrawScan *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalScanRangeMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->signalIndexRangeMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DopplerDrawScan::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerDrawScan::signalScanRangeMove)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DopplerDrawScan::*_t)(int , int , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerDrawScan::signalIndexRangeMove)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DopplerDrawScan::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DopplerDrawScan.data,
      qt_meta_data_DopplerDrawScan,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DopplerDrawScan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DopplerDrawScan::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DopplerDrawScan.stringdata0))
        return static_cast<void*>(const_cast< DopplerDrawScan*>(this));
    return QObject::qt_metacast(_clname);
}

int DopplerDrawScan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DopplerDrawScan::signalScanRangeMove(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DopplerDrawScan::signalIndexRangeMove(int _t1, int _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
