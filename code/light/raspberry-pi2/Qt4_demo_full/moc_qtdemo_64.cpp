/****************************************************************************
** Meta object code from reading C++ file 'qtdemo_64.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtdemo_64.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtdemo_64.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Qtdemo_64[] = {

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
      10,   36,   36,   36, 0x08,
      37,   36,   36,   36, 0x08,
      62,   36,   36,   36, 0x08,
      90,   36,   36,   36, 0x08,
     127,   36,   36,   36, 0x08,
     154,   36,   36,   36, 0x08,
     181,   36,   36,   36, 0x08,
     206,   36,   36,   36, 0x08,
     233,   36,   36,   36, 0x08,
     258,   36,   36,   36, 0x08,
     284,   36,   36,   36, 0x08,
     311,   36,   36,   36, 0x08,
     338,   36,   36,   36, 0x08,
     363,   36,   36,   36, 0x08,
     389,   36,   36,   36, 0x08,
     413,   36,   36,   36, 0x08,
     447,   36,   36,   36, 0x08,
     477,  504,   36,   36, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Qtdemo_64[] = {
    "Qtdemo_64\0on_DigitalIoBtn_clicked()\0"
    "\0on_AnalogIoBtn_clicked()\0"
    "on_WriteEepromBtn_clicked()\0"
    "on_DisableGraphChk_stateChanged(int)\0"
    "on_DeactivateBtn_clicked()\0"
    "on_ReadEepromBtn_clicked()\0"
    "on_ActivateBtn_clicked()\0"
    "on_UpdateListBtn_clicked()\0"
    "on_StopMeasBtn_clicked()\0"
    "on_StartMeasBtn_clicked()\0"
    "on_ShowEepromBtn_clicked()\0"
    "on_ShowSecureBtn_clicked()\0"
    "on_OpenCommBtn_clicked()\0"
    "on_CloseCommBtn_clicked()\0"
    "on_HW_TestBtn_clicked()\0"
    "on_ResetSpectrometerBtn_clicked()\0"
    "on_SpectrometerList_clicked()\0"
    "ReceiveDataIsHere(int,int)\0WParam,LParam\0"
};

void Qtdemo_64::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Qtdemo_64 *_t = static_cast<Qtdemo_64 *>(_o);
        switch (_id) {
        case 0: _t->on_DigitalIoBtn_clicked(); break;
        case 1: _t->on_AnalogIoBtn_clicked(); break;
        case 2: _t->on_WriteEepromBtn_clicked(); break;
        case 3: _t->on_DisableGraphChk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_DeactivateBtn_clicked(); break;
        case 5: _t->on_ReadEepromBtn_clicked(); break;
        case 6: _t->on_ActivateBtn_clicked(); break;
        case 7: _t->on_UpdateListBtn_clicked(); break;
        case 8: _t->on_StopMeasBtn_clicked(); break;
        case 9: _t->on_StartMeasBtn_clicked(); break;
        case 10: _t->on_ShowEepromBtn_clicked(); break;
        case 11: _t->on_ShowSecureBtn_clicked(); break;
        case 12: _t->on_OpenCommBtn_clicked(); break;
        case 13: _t->on_CloseCommBtn_clicked(); break;
        case 14: _t->on_HW_TestBtn_clicked(); break;
        case 15: _t->on_ResetSpectrometerBtn_clicked(); break;
        case 16: _t->on_SpectrometerList_clicked(); break;
        case 17: _t->ReceiveDataIsHere((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Qtdemo_64::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Qtdemo_64::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Qtdemo_64,
      qt_meta_data_Qtdemo_64, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Qtdemo_64::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Qtdemo_64::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Qtdemo_64::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qtdemo_64))
        return static_cast<void*>(const_cast< Qtdemo_64*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Qtdemo_64::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
