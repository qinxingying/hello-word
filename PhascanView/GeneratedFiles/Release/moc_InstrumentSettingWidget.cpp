/****************************************************************************
** Meta object code from reading C++ file 'InstrumentSettingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/InstrumentSettingWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstrumentSettingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InstrumentSettingWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x08,
      71,   25,   24,   24, 0x08,
     114,   25,   24,   24, 0x08,
     164,   25,   24,   24, 0x08,
     211,   25,   24,   24, 0x08,
     259,   25,   24,   24, 0x08,
     300,   25,   24,   24, 0x08,
     341,   24,   24,   24, 0x08,
     371,   24,   24,   24, 0x08,
     407,   24,   24,   24, 0x08,
     441,   24,   24,   24, 0x08,
     482,   24,   24,   24, 0x08,
     519,   24,   24,   24, 0x08,
     555,   24,   24,   24, 0x08,
     597,   24,   24,   24, 0x08,
     641,   24,   24,   24, 0x08,
     683,  678,   24,   24, 0x08,
     735,  729,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InstrumentSettingWidget[] = {
    "InstrumentSettingWidget\0\0index\0"
    "on_ComScanType_currentIndexChanged(int)\0"
    "on_ComEncoderType_currentIndexChanged(int)\0"
    "on_ComEncoderTypeSetting_currentIndexChanged(int)\0"
    "on_ComEncoderPolarity_currentIndexChanged(int)\0"
    "on_ComEncoderDirection_currentIndexChanged(int)\0"
    "on_ComVoltagePa_currentIndexChanged(int)\0"
    "on_ComVoltageUt_currentIndexChanged(int)\0"
    "on_ValuePrf_editingFinished()\0"
    "on_ValueScanStart_editingFinished()\0"
    "on_ValueScanEnd_editingFinished()\0"
    "on_ValueScanResolution_editingFinished()\0"
    "on_ValueIndexStart_editingFinished()\0"
    "on_ValueIndexStop_editingFinished()\0"
    "on_ValueIndexResolution_editingFinished()\0"
    "on_ValueEncoderResolution_editingFinished()\0"
    "on_ValueEncoderOrg_editingFinished()\0"
    "arg1\0on_SpinBoxCurrentScanPos_valueChanged(double)\0"
    "value\0on_SliderCurrentScanPos_valueChanged(int)\0"
};

void InstrumentSettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InstrumentSettingWidget *_t = static_cast<InstrumentSettingWidget *>(_o);
        switch (_id) {
        case 0: _t->on_ComScanType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ComEncoderType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_ComEncoderTypeSetting_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_ComEncoderPolarity_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_ComEncoderDirection_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_ComVoltagePa_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_ComVoltageUt_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_ValuePrf_editingFinished(); break;
        case 8: _t->on_ValueScanStart_editingFinished(); break;
        case 9: _t->on_ValueScanEnd_editingFinished(); break;
        case 10: _t->on_ValueScanResolution_editingFinished(); break;
        case 11: _t->on_ValueIndexStart_editingFinished(); break;
        case 12: _t->on_ValueIndexStop_editingFinished(); break;
        case 13: _t->on_ValueIndexResolution_editingFinished(); break;
        case 14: _t->on_ValueEncoderResolution_editingFinished(); break;
        case 15: _t->on_ValueEncoderOrg_editingFinished(); break;
        case 16: _t->on_SpinBoxCurrentScanPos_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->on_SliderCurrentScanPos_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InstrumentSettingWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InstrumentSettingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InstrumentSettingWidget,
      qt_meta_data_InstrumentSettingWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InstrumentSettingWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InstrumentSettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InstrumentSettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InstrumentSettingWidget))
        return static_cast<void*>(const_cast< InstrumentSettingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int InstrumentSettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
