/****************************************************************************
** Meta object code from reading C++ file 'pcaclassifier.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pcaclassifier.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pcaclassifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PCAClassifier_t {
    QByteArrayData data[17];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PCAClassifier_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PCAClassifier_t qt_meta_stringdata_PCAClassifier = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 11),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 3),
QT_MOC_LITERAL(4, 31, 14),
QT_MOC_LITERAL(5, 46, 15),
QT_MOC_LITERAL(6, 62, 7),
QT_MOC_LITERAL(7, 70, 5),
QT_MOC_LITERAL(8, 76, 6),
QT_MOC_LITERAL(9, 83, 9),
QT_MOC_LITERAL(10, 93, 7),
QT_MOC_LITERAL(11, 101, 6),
QT_MOC_LITERAL(12, 108, 10),
QT_MOC_LITERAL(13, 119, 6),
QT_MOC_LITERAL(14, 126, 4),
QT_MOC_LITERAL(15, 131, 3),
QT_MOC_LITERAL(16, 135, 7)
    },
    "PCAClassifier\0postMessage\0\0msg\0"
    "processStarted\0processFinished\0SVMType\0"
    "C_SVC\0NU_SVC\0ONE_CLASS\0EPS_SVR\0NU_SVR\0"
    "KernelType\0LINEAR\0POLY\0RBF\0SIGMOID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PCAClassifier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       2,   34, // enums/sets
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

 // enums: name, flags, count, data
       6, 0x0,    5,   42,
      12, 0x0,    4,   52,

 // enum data: key, value
       7, uint(PCAClassifier::C_SVC),
       8, uint(PCAClassifier::NU_SVC),
       9, uint(PCAClassifier::ONE_CLASS),
      10, uint(PCAClassifier::EPS_SVR),
      11, uint(PCAClassifier::NU_SVR),
      13, uint(PCAClassifier::LINEAR),
      14, uint(PCAClassifier::POLY),
      15, uint(PCAClassifier::RBF),
      16, uint(PCAClassifier::SIGMOID),

       0        // eod
};

void PCAClassifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PCAClassifier *_t = static_cast<PCAClassifier *>(_o);
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
            typedef void (PCAClassifier::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCAClassifier::postMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (PCAClassifier::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCAClassifier::processStarted)) {
                *result = 1;
            }
        }
        {
            typedef void (PCAClassifier::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PCAClassifier::processFinished)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PCAClassifier::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PCAClassifier.data,
      qt_meta_data_PCAClassifier,  qt_static_metacall, 0, 0}
};


const QMetaObject *PCAClassifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PCAClassifier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PCAClassifier.stringdata))
        return static_cast<void*>(const_cast< PCAClassifier*>(this));
    return QThread::qt_metacast(_clname);
}

int PCAClassifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PCAClassifier::postMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PCAClassifier::processStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PCAClassifier::processFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
