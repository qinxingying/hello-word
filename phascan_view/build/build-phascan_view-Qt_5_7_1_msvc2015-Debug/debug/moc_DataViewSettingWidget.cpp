/****************************************************************************
** Meta object code from reading C++ file 'DataViewSettingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/DataViewSettingWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataViewSettingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataViewSettingWidget_t {
    QByteArrayData data[5];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataViewSettingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataViewSettingWidget_t qt_meta_stringdata_DataViewSettingWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DataViewSettingWidget"
QT_MOC_LITERAL(1, 22, 22), // "slotButtonMinusClicked"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 21), // "slotButtonPlusClicked"
QT_MOC_LITERAL(4, 68, 22) // "slotSliderValueChanged"

    },
    "DataViewSettingWidget\0slotButtonMinusClicked\0"
    "\0slotButtonPlusClicked\0slotSliderValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataViewSettingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void DataViewSettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataViewSettingWidget *_t = static_cast<DataViewSettingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotButtonMinusClicked(); break;
        case 1: _t->slotButtonPlusClicked(); break;
        case 2: _t->slotSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DataViewSettingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DataViewSettingWidget.data,
      qt_meta_data_DataViewSettingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataViewSettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataViewSettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataViewSettingWidget.stringdata0))
        return static_cast<void*>(const_cast< DataViewSettingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DataViewSettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
