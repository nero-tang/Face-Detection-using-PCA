/****************************************************************************
** Meta object code from reading C++ file 'pcadetector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pcadetector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pcadetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PCADetector_t {
    QByteArrayData data[6];
    char stringdata[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PCADetector_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PCADetector_t qt_meta_stringdata_PCADetector = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 11),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 3),
QT_MOC_LITERAL(4, 29, 14),
QT_MOC_LITERAL(5, 44, 15)
    },
    "PCADetector\0postMessage\0\0msg\0"
    "processStarted\0processFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PCADetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,
       5,    0,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PCADetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PCADetector *_t = static_cast<PCADetector *>(_o);
        switch (_id) {
        case 0: _t->postMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->processStarted(); break;
        case 2: _t->processFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PCADetector::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCADetector::postMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (PCADetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCADetector::processStarted)) {
                *result = 1;
            }
        }
        {
            typedef void (PCADetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCADetector::processFinished)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PCADetector::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PCADetector.data,
      qt_meta_data_PCADetector,  qt_static_metacall, 0, 0}
};


const QMetaObject *PCADetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PCADetector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PCADetector.stringdata))
        return static_cast<void*>(const_cast< PCADetector*>(this));
    return QThread::qt_metacast(_clname);
}

int PCADetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void PCADetector::postMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PCADetector::processStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PCADetector::processFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
