/****************************************************************************
** Meta object code from reading C++ file 'DialogDxfFileLoad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/dialog/DialogDxfFileLoad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogDxfFileLoad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogDxfFileLoad_t {
    QByteArrayData data[19];
    char stringdata0[446];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogDxfFileLoad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogDxfFileLoad_t qt_meta_stringdata_DialogDxfFileLoad = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DialogDxfFileLoad"
QT_MOC_LITERAL(1, 18, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 5), // "index"
QT_MOC_LITERAL(4, 57, 34), // "on_ComWeldType_currentIndexCh..."
QT_MOC_LITERAL(5, 92, 37), // "on_ComWeldSymetry_currentInde..."
QT_MOC_LITERAL(6, 130, 27), // "on_SpinWHeight_valueChanged"
QT_MOC_LITERAL(7, 158, 4), // "arg1"
QT_MOC_LITERAL(8, 163, 27), // "on_SpinWoffset_valueChanged"
QT_MOC_LITERAL(9, 191, 27), // "on_SpinFHeight_valueChanged"
QT_MOC_LITERAL(10, 219, 27), // "on_SpinFRadius_valueChanged"
QT_MOC_LITERAL(11, 247, 26), // "on_SpinFAngle_valueChanged"
QT_MOC_LITERAL(12, 274, 29), // "on_SpinFHeight_2_valueChanged"
QT_MOC_LITERAL(13, 304, 28), // "on_SpinFAngle_2_valueChanged"
QT_MOC_LITERAL(14, 333, 24), // "on_PartFileListDbClicked"
QT_MOC_LITERAL(15, 358, 20), // "on_BtnNccPathClicked"
QT_MOC_LITERAL(16, 379, 27), // "on_BtnNccDefaultPathClicked"
QT_MOC_LITERAL(17, 407, 32), // "slot_doubleSpinBox_zoom_setValue"
QT_MOC_LITERAL(18, 440, 5) // "value"

    },
    "DialogDxfFileLoad\0on_comboBox_currentIndexChanged\0"
    "\0index\0on_ComWeldType_currentIndexChanged\0"
    "on_ComWeldSymetry_currentIndexChanged\0"
    "on_SpinWHeight_valueChanged\0arg1\0"
    "on_SpinWoffset_valueChanged\0"
    "on_SpinFHeight_valueChanged\0"
    "on_SpinFRadius_valueChanged\0"
    "on_SpinFAngle_valueChanged\0"
    "on_SpinFHeight_2_valueChanged\0"
    "on_SpinFAngle_2_valueChanged\0"
    "on_PartFileListDbClicked\0on_BtnNccPathClicked\0"
    "on_BtnNccDefaultPathClicked\0"
    "slot_doubleSpinBox_zoom_setValue\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogDxfFileLoad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    1,   87,    2, 0x08 /* Private */,
       5,    1,   90,    2, 0x08 /* Private */,
       6,    1,   93,    2, 0x08 /* Private */,
       8,    1,   96,    2, 0x08 /* Private */,
       9,    1,   99,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      11,    1,  105,    2, 0x08 /* Private */,
      12,    1,  108,    2, 0x08 /* Private */,
      13,    1,  111,    2, 0x08 /* Private */,
      14,    1,  114,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    1,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,

       0        // eod
};

void DialogDxfFileLoad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogDxfFileLoad *_t = static_cast<DialogDxfFileLoad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ComWeldType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_ComWeldSymetry_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_SpinWHeight_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_SpinWoffset_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_SpinFHeight_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_SpinFRadius_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_SpinFAngle_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_SpinFHeight_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_SpinFAngle_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_PartFileListDbClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_BtnNccPathClicked(); break;
        case 12: _t->on_BtnNccDefaultPathClicked(); break;
        case 13: _t->slot_doubleSpinBox_zoom_setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DialogDxfFileLoad::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogDxfFileLoad.data,
      qt_meta_data_DialogDxfFileLoad,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogDxfFileLoad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogDxfFileLoad::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogDxfFileLoad.stringdata0))
        return static_cast<void*>(const_cast< DialogDxfFileLoad*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogDxfFileLoad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
