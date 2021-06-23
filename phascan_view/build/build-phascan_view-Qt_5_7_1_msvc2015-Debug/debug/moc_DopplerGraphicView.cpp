/****************************************************************************
** Meta object code from reading C++ file 'DopplerGraphicView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../doppler_view/DopplerGraphicView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DopplerGraphicView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DopplerGraphicView_t {
    QByteArrayData data[44];
    char stringdata0[634];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DopplerGraphicView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DopplerGraphicView_t qt_meta_stringdata_DopplerGraphicView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DopplerGraphicView"
QT_MOC_LITERAL(1, 19, 17), // "signalViewChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "rect"
QT_MOC_LITERAL(4, 43, 19), // "signalUpdateDrawing"
QT_MOC_LITERAL(5, 63, 15), // "signalItemMoved"
QT_MOC_LITERAL(6, 79, 20), // "DopplerGraphicsItem*"
QT_MOC_LITERAL(7, 100, 5), // "item_"
QT_MOC_LITERAL(8, 106, 17), // "signalItemPressed"
QT_MOC_LITERAL(9, 124, 19), // "signalButtonPressed"
QT_MOC_LITERAL(10, 144, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 157, 5), // "event"
QT_MOC_LITERAL(12, 163, 25), // "signalButtonDoubleClicked"
QT_MOC_LITERAL(13, 189, 4), // "pos_"
QT_MOC_LITERAL(14, 194, 23), // "signalTofdDragProAction"
QT_MOC_LITERAL(15, 218, 4), // "ptS_"
QT_MOC_LITERAL(16, 223, 4), // "ptE_"
QT_MOC_LITERAL(17, 228, 19), // "signalScanPosChange"
QT_MOC_LITERAL(18, 248, 5), // "steps"
QT_MOC_LITERAL(19, 254, 18), // "signalLawPosChange"
QT_MOC_LITERAL(20, 273, 7), // "groupId"
QT_MOC_LITERAL(21, 281, 5), // "lawId"
QT_MOC_LITERAL(22, 287, 22), // "signalCursorScanChange"
QT_MOC_LITERAL(23, 310, 11), // "orientation"
QT_MOC_LITERAL(24, 322, 19), // "signalCursorUChange"
QT_MOC_LITERAL(25, 342, 21), // "signalNotifyOtherView"
QT_MOC_LITERAL(26, 364, 8), // "startPos"
QT_MOC_LITERAL(27, 373, 6), // "endPos"
QT_MOC_LITERAL(28, 380, 10), // "zoomStatus"
QT_MOC_LITERAL(29, 391, 16), // "signalShowCursor"
QT_MOC_LITERAL(30, 408, 6), // "status"
QT_MOC_LITERAL(31, 415, 16), // "signalShowDefect"
QT_MOC_LITERAL(32, 432, 24), // "signalCscanShowallChange"
QT_MOC_LITERAL(33, 457, 17), // "signalMeasureGate"
QT_MOC_LITERAL(34, 475, 20), // "signalMarkNextDefect"
QT_MOC_LITERAL(35, 496, 24), // "signalMarkPreviousDefect"
QT_MOC_LITERAL(36, 521, 12), // "scaleRecover"
QT_MOC_LITERAL(37, 534, 11), // "setDataMode"
QT_MOC_LITERAL(38, 546, 13), // "setShowCursor"
QT_MOC_LITERAL(39, 560, 13), // "setShowDefect"
QT_MOC_LITERAL(40, 574, 17), // "showCoupleInScanA"
QT_MOC_LITERAL(41, 592, 13), // "slotResetView"
QT_MOC_LITERAL(42, 606, 9), // "slotPrint"
QT_MOC_LITERAL(43, 616, 17) // "slotUpdateDrawing"

    },
    "DopplerGraphicView\0signalViewChanged\0"
    "\0rect\0signalUpdateDrawing\0signalItemMoved\0"
    "DopplerGraphicsItem*\0item_\0signalItemPressed\0"
    "signalButtonPressed\0QMouseEvent*\0event\0"
    "signalButtonDoubleClicked\0pos_\0"
    "signalTofdDragProAction\0ptS_\0ptE_\0"
    "signalScanPosChange\0steps\0signalLawPosChange\0"
    "groupId\0lawId\0signalCursorScanChange\0"
    "orientation\0signalCursorUChange\0"
    "signalNotifyOtherView\0startPos\0endPos\0"
    "zoomStatus\0signalShowCursor\0status\0"
    "signalShowDefect\0signalCscanShowallChange\0"
    "signalMeasureGate\0signalMarkNextDefect\0"
    "signalMarkPreviousDefect\0scaleRecover\0"
    "setDataMode\0setShowCursor\0setShowDefect\0"
    "showCoupleInScanA\0slotResetView\0"
    "slotPrint\0slotUpdateDrawing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DopplerGraphicView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x06 /* Public */,
       4,    0,  147,    2, 0x06 /* Public */,
       5,    1,  148,    2, 0x06 /* Public */,
       8,    1,  151,    2, 0x06 /* Public */,
       9,    1,  154,    2, 0x06 /* Public */,
      12,    1,  157,    2, 0x06 /* Public */,
      14,    2,  160,    2, 0x06 /* Public */,
      17,    1,  165,    2, 0x06 /* Public */,
      19,    3,  168,    2, 0x06 /* Public */,
      22,    2,  175,    2, 0x06 /* Public */,
      24,    3,  180,    2, 0x06 /* Public */,
      25,    3,  187,    2, 0x06 /* Public */,
      29,    2,  194,    2, 0x06 /* Public */,
      31,    2,  199,    2, 0x06 /* Public */,
      32,    1,  204,    2, 0x06 /* Public */,
      33,    1,  207,    2, 0x06 /* Public */,
      34,    0,  210,    2, 0x06 /* Public */,
      35,    0,  211,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      36,    0,  212,    2, 0x08 /* Private */,
      37,    1,  213,    2, 0x08 /* Private */,
      38,    1,  216,    2, 0x08 /* Private */,
      39,    1,  219,    2, 0x08 /* Private */,
      40,    1,  222,    2, 0x08 /* Private */,
      41,    0,  225,    2, 0x0a /* Public */,
      42,    0,  226,    2, 0x0a /* Public */,
      43,    0,  227,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRectF,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QPointF,   13,
    QMetaType::Void, QMetaType::QPointF, QMetaType::QPointF,   15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   20,   21,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   20,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   20,   21,   23,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::Bool,   26,   27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   20,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   20,   30,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DopplerGraphicView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DopplerGraphicView *_t = static_cast<DopplerGraphicView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalViewChanged((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->signalUpdateDrawing(); break;
        case 2: _t->signalItemMoved((*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[1]))); break;
        case 3: _t->signalItemPressed((*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[1]))); break;
        case 4: _t->signalButtonPressed((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->signalButtonDoubleClicked((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 6: _t->signalTofdDragProAction((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 7: _t->signalScanPosChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->signalLawPosChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->signalCursorScanChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->signalCursorUChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 11: _t->signalNotifyOtherView((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 12: _t->signalShowCursor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->signalShowDefect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->signalCscanShowallChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->signalMeasureGate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->signalMarkNextDefect(); break;
        case 17: _t->signalMarkPreviousDefect(); break;
        case 18: _t->scaleRecover(); break;
        case 19: _t->setDataMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->setShowCursor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setShowDefect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->showCoupleInScanA((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->slotResetView(); break;
        case 24: _t->slotPrint(); break;
        case 25: _t->slotUpdateDrawing(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DopplerGraphicView::*_t)(QRectF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalViewChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalUpdateDrawing)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(DopplerGraphicsItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalItemMoved)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(DopplerGraphicsItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalItemPressed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalButtonPressed)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalButtonDoubleClicked)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(QPointF , QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalTofdDragProAction)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalScanPosChange)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalLawPosChange)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalCursorScanChange)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalCursorUChange)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(QPoint , QPoint , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalNotifyOtherView)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalShowCursor)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalShowDefect)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalCscanShowallChange)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalMeasureGate)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalMarkNextDefect)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (DopplerGraphicView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DopplerGraphicView::signalMarkPreviousDefect)) {
                *result = 17;
                return;
            }
        }
    }
}

const QMetaObject DopplerGraphicView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_DopplerGraphicView.data,
      qt_meta_data_DopplerGraphicView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DopplerGraphicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DopplerGraphicView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DopplerGraphicView.stringdata0))
        return static_cast<void*>(const_cast< DopplerGraphicView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int DopplerGraphicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void DopplerGraphicView::signalViewChanged(QRectF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DopplerGraphicView::signalUpdateDrawing()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DopplerGraphicView::signalItemMoved(DopplerGraphicsItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DopplerGraphicView::signalItemPressed(DopplerGraphicsItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DopplerGraphicView::signalButtonPressed(QMouseEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DopplerGraphicView::signalButtonDoubleClicked(QPointF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DopplerGraphicView::signalTofdDragProAction(QPointF _t1, QPointF _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DopplerGraphicView::signalScanPosChange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DopplerGraphicView::signalLawPosChange(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DopplerGraphicView::signalCursorScanChange(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DopplerGraphicView::signalCursorUChange(int _t1, int _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void DopplerGraphicView::signalNotifyOtherView(QPoint _t1, QPoint _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void DopplerGraphicView::signalShowCursor(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void DopplerGraphicView::signalShowDefect(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void DopplerGraphicView::signalCscanShowallChange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void DopplerGraphicView::signalMeasureGate(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void DopplerGraphicView::signalMarkNextDefect()
{
    QMetaObject::activate(this, &staticMetaObject, 16, Q_NULLPTR);
}

// SIGNAL 17
void DopplerGraphicView::signalMarkPreviousDefect()
{
    QMetaObject::activate(this, &staticMetaObject, 17, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
