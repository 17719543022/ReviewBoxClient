/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ReviewBoxClient/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "baggageTrackerResponse"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 50, 5), // "reply"
QT_MOC_LITERAL(5, 56, 9), // "display_x"
QT_MOC_LITERAL(6, 66, 5), // "image"
QT_MOC_LITERAL(7, 72, 16), // "onNewResultFrame"
QT_MOC_LITERAL(8, 89, 7), // "result0"
QT_MOC_LITERAL(9, 97, 7), // "result1"
QT_MOC_LITERAL(10, 105, 7), // "result2"
QT_MOC_LITERAL(11, 113, 7), // "result3"
QT_MOC_LITERAL(12, 121, 7), // "result4"
QT_MOC_LITERAL(13, 129, 7), // "result5"
QT_MOC_LITERAL(14, 137, 6), // "boxStr"
QT_MOC_LITERAL(15, 144, 9), // "display_s"
QT_MOC_LITERAL(16, 154, 16), // "on_NewSerialData"
QT_MOC_LITERAL(17, 171, 10), // "strRequest"
QT_MOC_LITERAL(18, 182, 18), // "updateStateCameraX"
QT_MOC_LITERAL(19, 201, 5), // "state"
QT_MOC_LITERAL(20, 207, 18), // "updateStateCameraS"
QT_MOC_LITERAL(21, 226, 23), // "updateStateNetworkError"
QT_MOC_LITERAL(22, 250, 24) // "updateStateNetworkNormal"

    },
    "MainWindow\0baggageTrackerResponse\0\0"
    "QNetworkReply*\0reply\0display_x\0image\0"
    "onNewResultFrame\0result0\0result1\0"
    "result2\0result3\0result4\0result5\0boxStr\0"
    "display_s\0on_NewSerialData\0strRequest\0"
    "updateStateCameraX\0state\0updateStateCameraS\0"
    "updateStateNetworkError\0"
    "updateStateNetworkNormal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       7,    7,   65,    2, 0x08 /* Private */,
      15,    1,   80,    2, 0x08 /* Private */,
      16,    1,   83,    2, 0x08 /* Private */,
      18,    1,   86,    2, 0x08 /* Private */,
      20,    1,   89,    2, 0x08 /* Private */,
      21,    0,   92,    2, 0x08 /* Private */,
      22,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,    8,    9,   10,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->baggageTrackerResponse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->display_x((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->onNewResultFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 3: _t->display_s((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 4: _t->on_NewSerialData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->updateStateCameraX((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->updateStateCameraS((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->updateStateNetworkError(); break;
        case 8: _t->updateStateNetworkNormal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
