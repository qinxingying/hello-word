/****************************************************************************
** Meta object code from reading C++ file 'PoppingTabBar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/PoppingTabBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PoppingTabBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PoppingTabBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      24,   14,   14,   14, 0x05,
      33,   14,   14,   14, 0x05,
      70,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PoppingTabBar[] = {
    "PoppingTabBar\0\0extend()\0shrink()\0"
    "signalLastTabButton(Qt::MouseButton)\0"
    "signalRightButtonDoubleClicked(int)\0"
};

void PoppingTabBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PoppingTabBar *_t = static_cast<PoppingTabBar *>(_o);
        switch (_id) {
        case 0: _t->extend(); break;
        case 1: _t->shrink(); break;
        case 2: _t->signalLastTabButton((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 3: _t->signalRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PoppingTabBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PoppingTabBar::staticMetaObject = {
    { &QTabBar::staticMetaObject, qt_meta_stringdata_PoppingTabBar,
      qt_meta_data_PoppingTabBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PoppingTabBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PoppingTabBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PoppingTabBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PoppingTabBar))
        return static_cast<void*>(const_cast< PoppingTabBar*>(this));
    return QTabBar::qt_metacast(_clname);
}

int PoppingTabBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PoppingTabBar::extend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PoppingTabBar::shrink()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PoppingTabBar::signalLastTabButton(Qt::MouseButton _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PoppingTabBar::signalRightButtonDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
