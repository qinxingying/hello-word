/****************************************************************************
** Meta object code from reading C++ file 'PoppingTabWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/PoppingTabWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PoppingTabWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PoppingTabWidget_t {
    QByteArrayData data[10];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PoppingTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PoppingTabWidget_t qt_meta_stringdata_PoppingTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PoppingTabWidget"
QT_MOC_LITERAL(1, 17, 27), // "signalLastTabBottonCliecked"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 15), // "Qt::MouseButton"
QT_MOC_LITERAL(4, 62, 30), // "signalRightButtonDoubleClicked"
QT_MOC_LITERAL(5, 93, 10), // "slotExtend"
QT_MOC_LITERAL(6, 104, 10), // "slotShrink"
QT_MOC_LITERAL(7, 115, 24), // "slotLastTabButtonClicked"
QT_MOC_LITERAL(8, 140, 4), // "btn_"
QT_MOC_LITERAL(9, 145, 28) // "slotRightButtonDoubleClicked"

    },
    "PoppingTabWidget\0signalLastTabBottonCliecked\0"
    "\0Qt::MouseButton\0signalRightButtonDoubleClicked\0"
    "slotExtend\0slotShrink\0slotLastTabButtonClicked\0"
    "btn_\0slotRightButtonDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PoppingTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   50,    2, 0x08 /* Private */,
       6,    0,   51,    2, 0x08 /* Private */,
       7,    1,   52,    2, 0x08 /* Private */,
       9,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void PoppingTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PoppingTabWidget *_t = static_cast<PoppingTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLastTabBottonCliecked((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 1: _t->signalRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotExtend(); break;
        case 3: _t->slotShrink(); break;
        case 4: _t->slotLastTabButtonClicked((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 5: _t->slotRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PoppingTabWidget::*_t)(Qt::MouseButton );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PoppingTabWidget::signalLastTabBottonCliecked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PoppingTabWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PoppingTabWidget::signalRightButtonDoubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PoppingTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_PoppingTabWidget.data,
      qt_meta_data_PoppingTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PoppingTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PoppingTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PoppingTabWidget.stringdata0))
        return static_cast<void*>(const_cast< PoppingTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int PoppingTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PoppingTabWidget::signalLastTabBottonCliecked(Qt::MouseButton _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PoppingTabWidget::signalRightButtonDoubleClicked(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
