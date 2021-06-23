/****************************************************************************
** Meta object code from reading C++ file 'dialogdefectmethodselect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/dialog/dialogdefectmethodselect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogdefectmethodselect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogDefectMethodSelect_t {
    QByteArrayData data[13];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogDefectMethodSelect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogDefectMethodSelect_t qt_meta_stringdata_DialogDefectMethodSelect = {
    {
QT_MOC_LITERAL(0, 0, 24), // "DialogDefectMethodSelect"
QT_MOC_LITERAL(1, 25, 25), // "on_halfWaveRadioL_clicked"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 28), // "on_endHalfWaveRadioL_clicked"
QT_MOC_LITERAL(4, 81, 28), // "on_sensitivityRadioL_clicked"
QT_MOC_LITERAL(5, 110, 25), // "on_halfWaveRadioH_clicked"
QT_MOC_LITERAL(6, 136, 28), // "on_endHalfWaveRadioH_clicked"
QT_MOC_LITERAL(7, 165, 28), // "on_sensitivityRadioH_clicked"
QT_MOC_LITERAL(8, 194, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(9, 216, 34), // "on_scaleDoubleSpinBox_valueCh..."
QT_MOC_LITERAL(10, 251, 4), // "arg1"
QT_MOC_LITERAL(11, 256, 26), // "on_tipDiffractionH_clicked"
QT_MOC_LITERAL(12, 283, 20) // "on_autoMerge_clicked"

    },
    "DialogDefectMethodSelect\0"
    "on_halfWaveRadioL_clicked\0\0"
    "on_endHalfWaveRadioL_clicked\0"
    "on_sensitivityRadioL_clicked\0"
    "on_halfWaveRadioH_clicked\0"
    "on_endHalfWaveRadioH_clicked\0"
    "on_sensitivityRadioH_clicked\0"
    "on_pushButton_clicked\0"
    "on_scaleDoubleSpinBox_valueChanged\0"
    "arg1\0on_tipDiffractionH_clicked\0"
    "on_autoMerge_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogDefectMethodSelect[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogDefectMethodSelect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogDefectMethodSelect *_t = static_cast<DialogDefectMethodSelect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_halfWaveRadioL_clicked(); break;
        case 1: _t->on_endHalfWaveRadioL_clicked(); break;
        case 2: _t->on_sensitivityRadioL_clicked(); break;
        case 3: _t->on_halfWaveRadioH_clicked(); break;
        case 4: _t->on_endHalfWaveRadioH_clicked(); break;
        case 5: _t->on_sensitivityRadioH_clicked(); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_scaleDoubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_tipDiffractionH_clicked(); break;
        case 9: _t->on_autoMerge_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject DialogDefectMethodSelect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogDefectMethodSelect.data,
      qt_meta_data_DialogDefectMethodSelect,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogDefectMethodSelect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogDefectMethodSelect::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogDefectMethodSelect.stringdata0))
        return static_cast<void*>(const_cast< DialogDefectMethodSelect*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogDefectMethodSelect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
