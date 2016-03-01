/****************************************************************************
** Meta object code from reading C++ file 'digital_io.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "digital_io.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'digital_io.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_digital_io[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   40,   40,   40, 0x08,
      41,   40,   40,   40, 0x08,
      69,   40,   40,   40, 0x08,
      97,   40,   40,   40, 0x08,
     126,   40,   40,   40, 0x08,
     154,   40,   40,   40, 0x08,
     183,   40,   40,   40, 0x08,
     211,   40,   40,   40, 0x08,
     240,   40,   40,   40, 0x08,
     268,   40,   40,   40, 0x08,
     296,   40,   40,   40, 0x08,
     325,   40,   40,   40, 0x08,
     353,   40,   40,   40, 0x08,
     382,   40,   40,   40, 0x08,
     410,   40,   40,   40, 0x08,
     439,   40,   40,   40, 0x08,
     467,   40,   40,   40, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_digital_io[] = {
    "digital_io\0on_DO10Chk_stateChanged(int)\0"
    "\0on_DO9Chk_stateChanged(int)\0"
    "on_DO8Chk_stateChanged(int)\0"
    "on_PWM7Chk_stateChanged(int)\0"
    "on_DO7Chk_stateChanged(int)\0"
    "on_PWM6Chk_stateChanged(int)\0"
    "on_DO6Chk_stateChanged(int)\0"
    "on_PWM5Chk_stateChanged(int)\0"
    "on_DO5Chk_stateChanged(int)\0"
    "on_DO4Chk_stateChanged(int)\0"
    "on_PWM3Chk_stateChanged(int)\0"
    "on_DO3Chk_stateChanged(int)\0"
    "on_PWM2Chk_stateChanged(int)\0"
    "on_DO2Chk_stateChanged(int)\0"
    "on_PWM1Chk_stateChanged(int)\0"
    "on_DO1Chk_stateChanged(int)\0"
    "on_GetDigitalInputsBtn_clicked()\0"
};

void digital_io::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        digital_io *_t = static_cast<digital_io *>(_o);
        switch (_id) {
        case 0: _t->on_DO10Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_DO9Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_DO8Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_PWM7Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_DO7Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_PWM6Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_DO6Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_PWM5Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_DO5Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_DO4Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_PWM3Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_DO3Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_PWM2Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_DO2Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_PWM1Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_DO1Chk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_GetDigitalInputsBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData digital_io::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject digital_io::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_digital_io,
      qt_meta_data_digital_io, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &digital_io::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *digital_io::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *digital_io::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_digital_io))
        return static_cast<void*>(const_cast< digital_io*>(this));
    return QDialog::qt_metacast(_clname);
}

int digital_io::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
