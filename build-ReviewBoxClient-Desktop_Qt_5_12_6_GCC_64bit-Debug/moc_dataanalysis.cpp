/****************************************************************************
** Meta object code from reading C++ file 'dataanalysis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ReviewBoxClient/dataanalysis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataanalysis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataAnalysis_t {
    QByteArrayData data[15];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataAnalysis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataAnalysis_t qt_meta_stringdata_DataAnalysis = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DataAnalysis"
QT_MOC_LITERAL(1, 13, 10), // "newFrame_x"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "image"
QT_MOC_LITERAL(4, 31, 10), // "newFrame_s"
QT_MOC_LITERAL(5, 42, 18), // "stateCameraXChange"
QT_MOC_LITERAL(6, 61, 5), // "state"
QT_MOC_LITERAL(7, 67, 18), // "stateCameraSChange"
QT_MOC_LITERAL(8, 86, 14), // "newResultFrame"
QT_MOC_LITERAL(9, 101, 7), // "result0"
QT_MOC_LITERAL(10, 109, 7), // "result1"
QT_MOC_LITERAL(11, 117, 7), // "result2"
QT_MOC_LITERAL(12, 125, 7), // "result3"
QT_MOC_LITERAL(13, 133, 7), // "result4"
QT_MOC_LITERAL(14, 141, 7) // "result5"

    },
    "DataAnalysis\0newFrame_x\0\0image\0"
    "newFrame_s\0stateCameraXChange\0state\0"
    "stateCameraSChange\0newResultFrame\0"
    "result0\0result1\0result2\0result3\0result4\0"
    "result5"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataAnalysis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,
       7,    1,   48,    2, 0x06 /* Public */,
       8,    6,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,   13,   14,

       0        // eod
};

void DataAnalysis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataAnalysis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrame_x((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->newFrame_s((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->stateCameraXChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->stateCameraSChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->newResultFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataAnalysis::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::newFrame_x)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataAnalysis::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::newFrame_s)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataAnalysis::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::stateCameraXChange)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataAnalysis::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::stateCameraSChange)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataAnalysis::*)(int , int , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::newResultFrame)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataAnalysis::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataAnalysis.data,
    qt_meta_data_DataAnalysis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataAnalysis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataAnalysis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataAnalysis.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataAnalysis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DataAnalysis::newFrame_x(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataAnalysis::newFrame_s(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataAnalysis::stateCameraXChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataAnalysis::stateCameraSChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataAnalysis::newResultFrame(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
