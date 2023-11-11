/****************************************************************************
** Meta object code from reading C++ file 'my_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Measure_Up/my_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_my_widget_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_my_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_my_widget_t qt_meta_stringdata_my_widget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "my_widget"
QT_MOC_LITERAL(1, 10, 13), // "update_points"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "QList<qint16>"
QT_MOC_LITERAL(4, 39, 10), // "new_points"
QT_MOC_LITERAL(5, 50, 10), // "new_length"
QT_MOC_LITERAL(6, 61, 9), // "new_gears"
QT_MOC_LITERAL(7, 71, 17), // "update_fft_points"
QT_MOC_LITERAL(8, 89, 13), // "QList<quint8>"
QT_MOC_LITERAL(9, 103, 14), // "new_fft_points"
QT_MOC_LITERAL(10, 118, 14) // "new_fre_index2"

    },
    "my_widget\0update_points\0\0QList<qint16>\0"
    "new_points\0new_length\0new_gears\0"
    "update_fft_points\0QList<quint8>\0"
    "new_fft_points\0new_fre_index2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_my_widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x08 /* Private */,
       7,    2,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Short, QMetaType::UChar,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::UInt,    9,   10,

       0        // eod
};

void my_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<my_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_points((*reinterpret_cast< QList<qint16>(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 1: _t->update_fft_points((*reinterpret_cast< QList<quint8>(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<qint16> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<quint8> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject my_widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_my_widget.data,
    qt_meta_data_my_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *my_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *my_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_my_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int my_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
