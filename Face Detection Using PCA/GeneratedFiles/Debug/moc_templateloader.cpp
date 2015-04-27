/****************************************************************************
** Meta object code from reading C++ file 'templateloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../templateloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'templateloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TemplateLoader_t {
    QByteArrayData data[11];
    char stringdata[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TemplateLoader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TemplateLoader_t qt_meta_stringdata_TemplateLoader = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 14),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 8),
QT_MOC_LITERAL(4, 40, 18),
QT_MOC_LITERAL(5, 59, 23),
QT_MOC_LITERAL(6, 83, 16),
QT_MOC_LITERAL(7, 100, 27),
QT_MOC_LITERAL(8, 128, 4),
QT_MOC_LITERAL(9, 133, 11),
QT_MOC_LITERAL(10, 145, 3)
    },
    "TemplateLoader\0updateProgress\0\0progress\0"
    "updateTemplateInfo\0QList<QTreeWidgetItem*>\0"
    "templateInfoList\0PCAClassifier::TemplateType\0"
    "type\0postMessage\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TemplateLoader[] = {

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
       4,    2,   32,    2, 0x06 /* Public */,
       9,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void TemplateLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TemplateLoader *_t = static_cast<TemplateLoader *>(_o);
        switch (_id) {
        case 0: _t->updateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateTemplateInfo((*reinterpret_cast< const QList<QTreeWidgetItem*>(*)>(_a[1])),(*reinterpret_cast< PCAClassifier::TemplateType(*)>(_a[2]))); break;
        case 2: _t->postMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TemplateLoader::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateLoader::updateProgress)) {
                *result = 0;
            }
        }
        {
            typedef void (TemplateLoader::*_t)(const QList<QTreeWidgetItem*> & , PCAClassifier::TemplateType );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateLoader::updateTemplateInfo)) {
                *result = 1;
            }
        }
        {
            typedef void (TemplateLoader::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TemplateLoader::postMessage)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject TemplateLoader::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TemplateLoader.data,
      qt_meta_data_TemplateLoader,  qt_static_metacall, 0, 0}
};


const QMetaObject *TemplateLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TemplateLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemplateLoader.stringdata))
        return static_cast<void*>(const_cast< TemplateLoader*>(this));
    return QThread::qt_metacast(_clname);
}

int TemplateLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TemplateLoader::updateProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TemplateLoader::updateTemplateInfo(const QList<QTreeWidgetItem*> & _t1, PCAClassifier::TemplateType _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TemplateLoader::postMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
