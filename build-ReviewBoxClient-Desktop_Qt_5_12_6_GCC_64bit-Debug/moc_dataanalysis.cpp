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
    QByteArrayData data[16];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataAnalysis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataAnalysis_t qt_meta_stringdata_DataAnalysis = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DataAnalysis"
QT_MOC_LITERAL(1, 13, 9), // "newFrameX"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "image"
QT_MOC_LITERAL(4, 30, 9), // "newFrameS"
QT_MOC_LITERAL(5, 40, 18), // "stateCameraXChange"
QT_MOC_LITERAL(6, 59, 5), // "state"
QT_MOC_LITERAL(7, 65, 18), // "stateCameraSChange"
QT_MOC_LITERAL(8, 84, 14), // "newResultFrame"
QT_MOC_LITERAL(9, 99, 7), // "result0"
QT_MOC_LITERAL(10, 107, 7), // "result1"
QT_MOC_LITERAL(11, 115, 7), // "result2"
QT_MOC_LITERAL(12, 123, 7), // "result3"
QT_MOC_LITERAL(13, 131, 7), // "result4"
QT_MOC_LITERAL(14, 139, 7), // "result5"
QT_MOC_LITERAL(15, 147, 6) // "boxStr"

    },
    "DataAnalysis\0newFrameX\0\0image\0newFrameS\0"
    "stateCameraXChange\0state\0stateCameraSChange\0"
    "newResultFrame\0result0\0result1\0result2\0"
    "result3\0result4\0result5\0boxStr"
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
       8,    7,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,    9,   10,   11,   12,   13,   14,   15,

       0        // eod
};

void DataAnalysis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataAnalysis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrameX((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->newFrameS((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->stateCameraXChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->stateCameraSChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->newResultFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataAnalysis::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::newFrameX)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataAnalysis::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataAnalysis::newFrameS)) {
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
            using _t = void (DataAnalysis::*)(int , int , int , int , int , int , QString );
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
void DataAnalysis::newFrameX(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataAnalysis::newFrameS(const QImage & _t1)
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
void DataAnalysis::newResultFrame(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
