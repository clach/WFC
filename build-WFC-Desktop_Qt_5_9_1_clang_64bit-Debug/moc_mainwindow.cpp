/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WFC/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 34), // "on_actionCamera_Controls_trig..."
QT_MOC_LITERAL(4, 71, 17), // "slot_setBuildMode"
QT_MOC_LITERAL(5, 89, 27), // "slot_setVisualizeEmptyTiles"
QT_MOC_LITERAL(6, 117, 12), // "slot_setDimX"
QT_MOC_LITERAL(7, 130, 12), // "slot_setDimY"
QT_MOC_LITERAL(8, 143, 12), // "slot_setDimZ"
QT_MOC_LITERAL(9, 156, 16), // "slot_setPeriodic"
QT_MOC_LITERAL(10, 173, 13), // "slot_setClean"
QT_MOC_LITERAL(11, 187, 12), // "slot_setNone"
QT_MOC_LITERAL(12, 200, 23), // "slot_setPeriodicPreview"
QT_MOC_LITERAL(13, 224, 18), // "slot_clearTileGrid"
QT_MOC_LITERAL(14, 243, 22), // "slot_clearNonUserTiles"
QT_MOC_LITERAL(15, 266, 11), // "slot_runWFC"
QT_MOC_LITERAL(16, 278, 15), // "slot_setTileset"
QT_MOC_LITERAL(17, 294, 16), // "slot_setTileset2"
QT_MOC_LITERAL(18, 311, 12), // "slot_setTile"
QT_MOC_LITERAL(19, 324, 18) // "slot_setErrorLabel"

    },
    "MainWindow\0on_actionQuit_triggered\0\0"
    "on_actionCamera_Controls_triggered\0"
    "slot_setBuildMode\0slot_setVisualizeEmptyTiles\0"
    "slot_setDimX\0slot_setDimY\0slot_setDimZ\0"
    "slot_setPeriodic\0slot_setClean\0"
    "slot_setNone\0slot_setPeriodicPreview\0"
    "slot_clearTileGrid\0slot_clearNonUserTiles\0"
    "slot_runWFC\0slot_setTileset\0"
    "slot_setTileset2\0slot_setTile\0"
    "slot_setErrorLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    1,  106,    2, 0x08 /* Private */,
       5,    1,  109,    2, 0x08 /* Private */,
       6,    1,  112,    2, 0x08 /* Private */,
       7,    1,  115,    2, 0x08 /* Private */,
       8,    1,  118,    2, 0x08 /* Private */,
       9,    1,  121,    2, 0x08 /* Private */,
      10,    1,  124,    2, 0x08 /* Private */,
      11,    1,  127,    2, 0x08 /* Private */,
      12,    1,  130,    2, 0x08 /* Private */,
      13,    0,  133,    2, 0x08 /* Private */,
      14,    0,  134,    2, 0x08 /* Private */,
      15,    0,  135,    2, 0x08 /* Private */,
      16,    0,  136,    2, 0x08 /* Private */,
      17,    0,  137,    2, 0x08 /* Private */,
      18,    0,  138,    2, 0x08 /* Private */,
      19,    1,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionQuit_triggered(); break;
        case 1: _t->on_actionCamera_Controls_triggered(); break;
        case 2: _t->slot_setBuildMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slot_setVisualizeEmptyTiles((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_setDimX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_setDimY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_setDimZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_setPeriodic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_setClean((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->slot_setNone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->slot_setPeriodicPreview((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->slot_clearTileGrid(); break;
        case 12: _t->slot_clearNonUserTiles(); break;
        case 13: _t->slot_runWFC(); break;
        case 14: _t->slot_setTileset(); break;
        case 15: _t->slot_setTileset2(); break;
        case 16: _t->slot_setTile(); break;
        case 17: _t->slot_setErrorLabel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
