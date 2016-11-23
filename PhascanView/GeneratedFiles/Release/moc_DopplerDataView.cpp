/****************************************************************************
** Meta object code from reading C++ file 'DopplerDataView.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DopplerView/DopplerDataView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DopplerDataView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DopplerDataView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      48,   46,   16,   16, 0x05,
     103,   16,   16,   16, 0x05,
     149,  143,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     205,  200,   16,   16, 0x0a,
     234,  228,   16,   16, 0x09,
     270,   16,   16,   16, 0x09,
     305,   16,   16,   16, 0x09,
     345,  340,   16,   16, 0x09,
     377,   46,   16,   16, 0x09,
     431,  416,   16,   16, 0x09,
     465,  416,   16,   16, 0x09,
     523,  501,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DopplerDataView[] = {
    "DopplerDataView\0\0signalMousePressed(QWidget*)\0"
    ",\0signalItemMoved(DopplerDataView*,DopplerGraphicsItem*)\0"
    "signalDataViewResized(DopplerDataView*)\0"
    ",pos_\0signalMouseDoubleClicked(DopplerDataView*,QPointF)\0"
    "rect\0slotZoomAction(QRectF)\0item_\0"
    "slotItemMoved(DopplerGraphicsItem*)\0"
    "slotViewMouseRelease(QMouseEvent*)\0"
    "slotViewMousePressed(QMouseEvent*)\0"
    "pos_\0slotMouseDoubleClicked(QPointF)\0"
    "slotTofdDragProAction(QPointF,QPointF)\0"
    "nStart_,nStop_\0slotLeftRulerMoved(double,double)\0"
    "slotBottomRulerMoved(double,double)\0"
    "nType_,nStart_,nStop_\0"
    "slotScanRangeMove(int,int,int)\0"
};

void DopplerDataView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DopplerDataView *_t = static_cast<DopplerDataView *>(_o);
        switch (_id) {
        case 0: _t->signalMousePressed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->signalItemMoved((*reinterpret_cast< DopplerDataView*(*)>(_a[1])),(*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[2]))); break;
        case 2: _t->signalDataViewResized((*reinterpret_cast< DopplerDataView*(*)>(_a[1]))); break;
        case 3: _t->signalMouseDoubleClicked((*reinterpret_cast< DopplerDataView*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 4: _t->slotZoomAction((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 5: _t->slotItemMoved((*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[1]))); break;
        case 6: _t->slotViewMouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->slotViewMousePressed((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->slotMouseDoubleClicked((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 9: _t->slotTofdDragProAction((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 10: _t->slotLeftRulerMoved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: _t->slotBottomRulerMoved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 12: _t->slotScanRangeMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DopplerDataView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DopplerDataView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DopplerDataView,
      qt_meta_data_DopplerDataView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DopplerDataView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DopplerDataView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DopplerDataView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DopplerDataView))
        return static_cast<void*>(const_cast< DopplerDataView*>(this));
    return QWidget::qt_metacast(_clname);
}

int DopplerDataView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DopplerDataView::signalMousePressed(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DopplerDataView::signalItemMoved(DopplerDataView * _t1, DopplerGraphicsItem * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DopplerDataView::signalDataViewResized(DopplerDataView * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DopplerDataView::signalMouseDoubleClicked(DopplerDataView * _t1, QPointF _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
