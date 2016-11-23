/****************************************************************************
** Meta object code from reading C++ file 'DialogWeldPartLoad.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/dialog/DialogWeldPartLoad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialogWeldPartLoad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogWeldPartLoad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x08,
      63,   20,   19,   19, 0x08,
     103,   20,   19,   19, 0x08,
     151,  146,   19,   19, 0x08,
     187,  146,   19,   19, 0x08,
     223,  146,   19,   19, 0x08,
     259,  146,   19,   19, 0x08,
     295,  146,   19,   19, 0x08,
     330,   20,   19,   19, 0x08,
     368,   19,   19,   19, 0x08,
     391,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogWeldPartLoad[] = {
    "DialogWeldPartLoad\0\0index\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "on_ComWeldType_currentIndexChanged(int)\0"
    "on_ComWeldSymetry_currentIndexChanged(int)\0"
    "arg1\0on_SpinWHeight_valueChanged(double)\0"
    "on_SpinWoffset_valueChanged(double)\0"
    "on_SpinFHeight_valueChanged(double)\0"
    "on_SpinFRadius_valueChanged(double)\0"
    "on_SpinFAngle_valueChanged(double)\0"
    "on_PartFileListDbClicked(QModelIndex)\0"
    "on_BtnNccPathClicked()\0"
    "on_BtnNccDefaultPathClicked()\0"
};

void DialogWeldPartLoad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DialogWeldPartLoad *_t = static_cast<DialogWeldPartLoad *>(_o);
        switch (_id) {
        case 0: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ComWeldType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_ComWeldSymetry_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_SpinWHeight_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_SpinWoffset_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->on_SpinFHeight_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->on_SpinFRadius_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_SpinFAngle_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_PartFileListDbClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 9: _t->on_BtnNccPathClicked(); break;
        case 10: _t->on_BtnNccDefaultPathClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DialogWeldPartLoad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DialogWeldPartLoad::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogWeldPartLoad,
      qt_meta_data_DialogWeldPartLoad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogWeldPartLoad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogWeldPartLoad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogWeldPartLoad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogWeldPartLoad))
        return static_cast<void*>(const_cast< DialogWeldPartLoad*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogWeldPartLoad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
