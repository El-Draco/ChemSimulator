/****************************************************************************
** Meta object code from reading C++ file 'atomentity.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../atomentity.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'atomentity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AtomEntity_t {
    const uint offsetsAndSize[12];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_AtomEntity_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_AtomEntity_t qt_meta_stringdata_AtomEntity = {
    {
QT_MOC_LITERAL(0, 10), // "AtomEntity"
QT_MOC_LITERAL(11, 15), // "draggingChanged"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 7), // "onHover"
QT_MOC_LITERAL(36, 10), // "handleDrag"
QT_MOC_LITERAL(47, 23) // "Qt3DRender::QPickEvent*"

    },
    "AtomEntity\0draggingChanged\0\0onHover\0"
    "handleDrag\0Qt3DRender::QPickEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AtomEntity[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   37,    2, 0x08,    4 /* Private */,
       4,    1,   40,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QVector3D,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void AtomEntity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AtomEntity *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->draggingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVector3D>>(_a[2]))); break;
        case 1: _t->onHover((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->handleDrag((*reinterpret_cast< std::add_pointer_t<Qt3DRender::QPickEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AtomEntity::*)(bool , QVector3D );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AtomEntity::draggingChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AtomEntity::staticMetaObject = { {
    QMetaObject::SuperData::link<Qt3DCore::QEntity::staticMetaObject>(),
    qt_meta_stringdata_AtomEntity.offsetsAndSize,
    qt_meta_data_AtomEntity,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AtomEntity_t
, QtPrivate::TypeAndForceComplete<AtomEntity, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QVector3D, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Qt3DRender::QPickEvent *, std::false_type>


>,
    nullptr
} };


const QMetaObject *AtomEntity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AtomEntity::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AtomEntity.stringdata0))
        return static_cast<void*>(this);
    return Qt3DCore::QEntity::qt_metacast(_clname);
}

int AtomEntity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Qt3DCore::QEntity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AtomEntity::draggingChanged(bool _t1, QVector3D _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
