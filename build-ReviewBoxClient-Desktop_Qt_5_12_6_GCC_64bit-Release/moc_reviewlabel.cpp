/****************************************************************************
** Meta object code from reading C++ file 'reviewlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ReviewBoxClient/reviewlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reviewlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReviewLabel_t {
    QByteArrayData data[10];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReviewLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReviewLabel_t qt_meta_stringdata_ReviewLabel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ReviewLabel"
QT_MOC_LITERAL(1, 12, 16), // "onNewResultFrame"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "result0"
QT_MOC_LITERAL(4, 38, 7), // "result1"
QT_MOC_LITERAL(5, 46, 7), // "result2"
QT_MOC_LITERAL(6, 54, 7), // "result3"
QT_MOC_LITERAL(7, 62, 7), // "result4"
QT_MOC_LITERAL(8, 70, 7), // "result5"
QT_MOC_LITERAL(9, 78, 6) // "boxStr"

    },
    "ReviewLabel\0onNewResultFrame\0\0result0\0"
    "result1\0result2\0result3\0result4\0result5\0"
    "boxStr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReviewLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    7,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,    6,    7,    8,    9,

       0        // eod
};

void ReviewLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReviewLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewResultFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ReviewLabel::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_ReviewLabel.data,
    qt_meta_data_ReviewLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ReviewLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReviewLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReviewLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int ReviewLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
