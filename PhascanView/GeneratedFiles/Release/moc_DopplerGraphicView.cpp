/****************************************************************************
** Meta object code from reading C++ file 'DopplerGraphicView.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DopplerView/DopplerGraphicView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DopplerGraphicView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DopplerGraphicView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x05,
      51,   19,   19,   19, 0x05,
      79,   73,   19,   19, 0x05,
     123,  117,   19,   19, 0x05,
     157,  117,   19,   19, 0x05,
     196,  191,   19,   19, 0x05,
     241,  231,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     282,   19,   19,   19, 0x0a,
     298,   19,   19,   19, 0x0a,
     310,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DopplerGraphicView[] = {
    "DopplerGraphicView\0\0rect\0"
    "signalViewChanged(QRectF)\0"
    "signalUpdateDrawing()\0item_\0"
    "signalItemMoved(DopplerGraphicsItem*)\0"
    "event\0signalButtonRelease(QMouseEvent*)\0"
    "signalButtonPressed(QMouseEvent*)\0"
    "pos_\0signalButtonDoubleClicked(QPointF)\0"
    "ptS_,ptE_\0signalTofdDragProAction(QPointF,QPointF)\0"
    "slotResetView()\0slotPrint()\0"
    "slotUpdateDrawing()\0"
};

void DopplerGraphicView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DopplerGraphicView *_t = static_cast<DopplerGraphicView *>(_o);
        switch (_id) {
        case 0: _t->signalViewChanged((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->signalUpdateDrawing(); break;
        case 2: _t->signalItemMoved((*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[1]))); break;
        case 3: _t->signalButtonRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->signalButtonPressed((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->signalButtonDoubleClicked((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 6: _t->signalTofdDragProAction((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 7: _t->slotResetView(); break;
        case 8: _t->slotPrint(); break;
        case 9: _t->slotUpdateDrawing(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DopplerGraphicView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DopplerGraphicView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_DopplerGraphicView,
      qt_meta_data_DopplerGraphicView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DopplerGraphicView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DopplerGraphicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DopplerGraphicView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DopplerGraphicView))
        return static_cast<void*>(const_cast< DopplerGraphicView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int DopplerGraphicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DopplerGraphicView::signalViewChanged(QRectF _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DopplerGraphicView::signalUpdateDrawing()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DopplerGraphicView::signalItemMoved(DopplerGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DopplerGraphicView::signalButtonRelease(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DopplerGraphicView::signalButtonPressed(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DopplerGraphicView::signalButtonDoubleClicked(QPointF _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DopplerGraphicView::signalTofdDragProAction(QPointF _t1, QPointF _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
