/****************************************************************************
** Meta object code from reading C++ file 'qtdemo.h'
**
** Created: Mon Apr 11 14:08:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtdemo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtdemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Qtdemo[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      33,    7,    7,    7, 0x08,
      59,    7,    7,    7, 0x08,
      85,    7,    7,    7, 0x08,
     119,  110,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Qtdemo[] = {
    "Qtdemo\0\0on_StopMeasBtn_clicked()\0"
    "on_StartMeasBtn_clicked()\0"
    "on_CloseCommBtn_clicked()\0"
    "on_OpenCommBtn_clicked()\0newValue\0"
    "on_DataIsHere(int)\0"
};

const QMetaObject Qtdemo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Qtdemo,
      qt_meta_data_Qtdemo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Qtdemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Qtdemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Qtdemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qtdemo))
        return static_cast<void*>(const_cast< Qtdemo*>(this));
    return QDialog::qt_metacast(_clname);
}

int Qtdemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_StopMeasBtn_clicked(); break;
        case 1: on_StartMeasBtn_clicked(); break;
        case 2: on_CloseCommBtn_clicked(); break;
        case 3: on_OpenCommBtn_clicked(); break;
        case 4: on_DataIsHere((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
