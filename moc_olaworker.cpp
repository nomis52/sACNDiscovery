/****************************************************************************
** Meta object code from reading C++ file 'olaworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "olaworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'olaworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OLAWorker_t {
    QByteArrayData data[7];
    char stringdata[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OLAWorker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OLAWorker_t qt_meta_stringdata_OLAWorker = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 8),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 14),
QT_MOC_LITERAL(4, 35, 23),
QT_MOC_LITERAL(5, 59, 7),
QT_MOC_LITERAL(6, 67, 7)
    },
    "OLAWorker\0finished\0\0E131SourceList\0"
    "std::vector<E131Source>\0sources\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OLAWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void OLAWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OLAWorker *_t = static_cast<OLAWorker *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->E131SourceList((*reinterpret_cast< const std::vector<E131Source>(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OLAWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OLAWorker::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (OLAWorker::*_t)(const std::vector<E131Source> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OLAWorker::E131SourceList)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject OLAWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OLAWorker.data,
      qt_meta_data_OLAWorker,  qt_static_metacall, 0, 0}
};


const QMetaObject *OLAWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OLAWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OLAWorker.stringdata))
        return static_cast<void*>(const_cast< OLAWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int OLAWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OLAWorker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void OLAWorker::E131SourceList(const std::vector<E131Source> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
