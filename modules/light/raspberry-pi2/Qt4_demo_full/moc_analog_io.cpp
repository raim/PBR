/****************************************************************************
** Meta object code from reading C++ file 'analog_io.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "analog_io.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analog_io.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_analog_io[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,   39,   39,   39, 0x08,
      40,   39,   39,   39, 0x08,
      68,   39,   39,   39, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_analog_io[] = {
    "analog_io\0on_GetOnboardAIBtn_clicked()\0"
    "\0on_GetAnalogInBtn_clicked()\0"
    "on_SetAnalogOutBtn_clicked()\0"
};

void analog_io::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        analog_io *_t = static_cast<analog_io *>(_o);
        switch (_id) {
        case 0: _t->on_GetOnboardAIBtn_clicked(); break;
        case 1: _t->on_GetAnalogInBtn_clicked(); break;
        case 2: _t->on_SetAnalogOutBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData analog_io::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject analog_io::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_analog_io,
      qt_meta_data_analog_io, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &analog_io::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *analog_io::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *analog_io::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_analog_io))
        return static_cast<void*>(const_cast< analog_io*>(this));
    return QDialog::qt_metacast(_clname);
}

int analog_io::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
