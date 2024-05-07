/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[409];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 18), // "setupAtomTableView"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 14), // "QItemSelection"
QT_MOC_LITERAL(46, 19), // "resetViewsAndModels"
QT_MOC_LITERAL(66, 6), // "from3d"
QT_MOC_LITERAL(73, 18), // "setupBondTableView"
QT_MOC_LITERAL(92, 8), // "selected"
QT_MOC_LITERAL(101, 10), // "deselected"
QT_MOC_LITERAL(112, 25), // "validateMoleculeSelection"
QT_MOC_LITERAL(138, 5), // "index"
QT_MOC_LITERAL(144, 24), // "on_viewAllButton_clicked"
QT_MOC_LITERAL(169, 18), // "on_addBond_clicked"
QT_MOC_LITERAL(188, 21), // "on_deleteBond_clicked"
QT_MOC_LITERAL(210, 18), // "on_addAtom_clicked"
QT_MOC_LITERAL(229, 21), // "on_deleteAtom_clicked"
QT_MOC_LITERAL(251, 22), // "on_addMolecule_clicked"
QT_MOC_LITERAL(274, 25), // "on_deleteMolecule_clicked"
QT_MOC_LITERAL(300, 41), // "on_actionAdd_Molecule_From_Fi..."
QT_MOC_LITERAL(342, 22), // "on_startButton_clicked"
QT_MOC_LITERAL(365, 43) // "on_actionExport_Molecules_To_..."

    },
    "MainWindow\0setupAtomTableView\0\0"
    "QItemSelection\0resetViewsAndModels\0"
    "from3d\0setupBondTableView\0selected\0"
    "deselected\0validateMoleculeSelection\0"
    "index\0on_viewAllButton_clicked\0"
    "on_addBond_clicked\0on_deleteBond_clicked\0"
    "on_addAtom_clicked\0on_deleteAtom_clicked\0"
    "on_addMolecule_clicked\0on_deleteMolecule_clicked\0"
    "on_actionAdd_Molecule_From_File_triggered\0"
    "on_startButton_clicked\0"
    "on_actionExport_Molecules_To_File_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   98,    2, 0x0a,    1 /* Public */,
       4,    1,  103,    2, 0x0a,    4 /* Public */,
       6,    2,  106,    2, 0x0a,    6 /* Public */,
       9,    1,  111,    2, 0x0a,    9 /* Public */,
      11,    0,  114,    2, 0x08,   11 /* Private */,
      12,    0,  115,    2, 0x08,   12 /* Private */,
      13,    0,  116,    2, 0x08,   13 /* Private */,
      14,    0,  117,    2, 0x08,   14 /* Private */,
      15,    0,  118,    2, 0x08,   15 /* Private */,
      16,    0,  119,    2, 0x08,   16 /* Private */,
      17,    0,  120,    2, 0x08,   17 /* Private */,
      18,    0,  121,    2, 0x08,   18 /* Private */,
      19,    0,  122,    2, 0x08,   19 /* Private */,
      20,    0,  123,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setupAtomTableView((*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[2]))); break;
        case 1: _t->resetViewsAndModels((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->setupBondTableView((*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[2]))); break;
        case 3: _t->validateMoleculeSelection((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->on_viewAllButton_clicked(); break;
        case 5: _t->on_addBond_clicked(); break;
        case 6: _t->on_deleteBond_clicked(); break;
        case 7: _t->on_addAtom_clicked(); break;
        case 8: _t->on_deleteAtom_clicked(); break;
        case 9: _t->on_addMolecule_clicked(); break;
        case 10: _t->on_deleteMolecule_clicked(); break;
        case 11: _t->on_actionAdd_Molecule_From_File_triggered(); break;
        case 12: _t->on_startButton_clicked(); break;
        case 13: _t->on_actionExport_Molecules_To_File_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QItemSelection >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QItemSelection >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QItemSelection &, std::false_type>, QtPrivate::TypeAndForceComplete<const QItemSelection &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QItemSelection &, std::false_type>, QtPrivate::TypeAndForceComplete<const QItemSelection &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
