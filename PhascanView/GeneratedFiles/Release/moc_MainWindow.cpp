/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   11,   11,   11, 0x08,
      74,   11,   11,   11, 0x08,
     119,  111,   11,   11, 0x08,
     154,  149,   11,   11, 0x08,
     195,   11,   11,   11, 0x08,
     212,  149,   11,   11, 0x08,
     254,   11,   11,   11, 0x08,
     291,   11,   11,   11, 0x08,
     320,   11,   11,   11, 0x08,
     350,  348,   11,   11, 0x08,
     403,   11,   11,   11, 0x08,
     453,  441,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0pixmap\0setPixmap(QPixmap)\0"
    "slotsLeftTabButton(Qt::MouseButton)\0"
    "slotsRightTabButton(Qt::MouseButton)\0"
    "action_\0slotActionTriggered(QAction*)\0"
    "nId_\0slotLeftTabRightButtonDoubleClicked(int)\0"
    "SetDispTabText()\0"
    "slotRightTabRightButtonDoubleClicked(int)\0"
    "slotViewFrameButtonClicked(QWidget*)\0"
    "slotCurrentGroupChanged(int)\0"
    "slotCurrentDispChanged(int)\0,\0"
    "slotItemMoved(DopplerDataView*,DopplerGraphicsItem*)\0"
    "slotDataViewResized(DopplerDataView*)\0"
    "pView_,pos_\0"
    "slotDataViewMouseDoubleClicked(DopplerDataView*,QPointF)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setPixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: _t->slotsLeftTabButton((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 2: _t->slotsRightTabButton((*reinterpret_cast< Qt::MouseButton(*)>(_a[1]))); break;
        case 3: _t->slotActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->slotLeftTabRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SetDispTabText(); break;
        case 6: _t->slotRightTabRightButtonDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slotViewFrameButtonClicked((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 8: _t->slotCurrentGroupChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotCurrentDispChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slotItemMoved((*reinterpret_cast< DopplerDataView*(*)>(_a[1])),(*reinterpret_cast< DopplerGraphicsItem*(*)>(_a[2]))); break;
        case 11: _t->slotDataViewResized((*reinterpret_cast< DopplerDataView*(*)>(_a[1]))); break;
        case 12: _t->slotDataViewMouseDoubleClicked((*reinterpret_cast< DopplerDataView*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void MainWindow::setPixmap(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
