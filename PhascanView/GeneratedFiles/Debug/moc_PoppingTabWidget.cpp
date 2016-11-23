/****************************************************************************
** Meta object code from reading C++ file 'PoppingTabWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/PoppingTabWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PoppingTabWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PoppingTabWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      63,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      99,   17,   17,   17, 0x08,
     112,   17,   17,   17, 0x08,
     130,  125,   17,   17, 0x08,
     172,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PoppingTabWidget[] = {
    "PoppingTabWidget\0\0"
    "signalLastTabBottonCliecked(Qt::MouseButton)\0"
    "signalRightButtonDoubleClicked(int)\0"
    "slotExtend()\0slotShrink()\0btn_\0"
    "slotLastTabButtonClicked(Qt::MouseButton)\0"
    "slotRightButtonDoubleClicked(int)\0"
};

void PoppingTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PoppingTabWidget *_t = static_cast<PoppingTabWidget *>(_o);
        switch (_id) {
        case 0: _t->signalLastTabBottonCliecked((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 1: _t->signalRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotExtend(); break;
        case 3: _t->slotShrink(); break;
        case 4: _t->slotLastTabButtonClicked((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 5: _t->slotRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PoppingTabWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PoppingTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_PoppingTabWidget,
      qt_meta_data_PoppingTabWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PoppingTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PoppingTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PoppingTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PoppingTabWidget))
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
    }
    return _id;
}

// SIGNAL 0
void PoppingTabWidget::signalLastTabBottonCliecked(Qt::MouseButton _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PoppingTabWidget::signalRightButtonDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
