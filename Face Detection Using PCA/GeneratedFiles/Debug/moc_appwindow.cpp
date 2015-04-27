/****************************************************************************
** Meta object code from reading C++ file 'appwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../appwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_appWindow_t {
    QByteArrayData data[26];
    char stringdata[402];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_appWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_appWindow_t qt_meta_stringdata_appWindow = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 12),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 3),
QT_MOC_LITERAL(4, 28, 19),
QT_MOC_LITERAL(5, 48, 5),
QT_MOC_LITERAL(6, 54, 20),
QT_MOC_LITERAL(7, 75, 6),
QT_MOC_LITERAL(8, 82, 18),
QT_MOC_LITERAL(9, 101, 18),
QT_MOC_LITERAL(10, 120, 9),
QT_MOC_LITERAL(11, 130, 16),
QT_MOC_LITERAL(12, 147, 19),
QT_MOC_LITERAL(13, 167, 20),
QT_MOC_LITERAL(14, 188, 23),
QT_MOC_LITERAL(15, 212, 13),
QT_MOC_LITERAL(16, 226, 27),
QT_MOC_LITERAL(17, 254, 4),
QT_MOC_LITERAL(18, 259, 29),
QT_MOC_LITERAL(19, 289, 16),
QT_MOC_LITERAL(20, 306, 12),
QT_MOC_LITERAL(21, 319, 18),
QT_MOC_LITERAL(22, 338, 20),
QT_MOC_LITERAL(23, 359, 15),
QT_MOC_LITERAL(24, 375, 16),
QT_MOC_LITERAL(25, 392, 9)
    },
    "appWindow\0printMessage\0\0msg\0"
    "updateTemplateWidth\0width\0"
    "updateTemplateHeight\0height\0"
    "onTrainingFinished\0onDetectionFinshed\0"
    "loadImage\0loadFaceTemplate\0"
    "loadNonFaceTemplate\0loadTemplateInfoList\0"
    "QList<QTreeWidgetItem*>\0templateInfos\0"
    "PCAClassifier::TemplateType\0type\0"
    "displaySelectedTreeWidgetItem\0"
    "QTreeWidgetItem*\0selectedItem\0"
    "performPCATraining\0performFaceDetection\0"
    "busyProgressbar\0resetProgressbar\0"
    "showAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_appWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       4,    1,   92,    2, 0x08 /* Private */,
       6,    1,   95,    2, 0x08 /* Private */,
       8,    0,   98,    2, 0x08 /* Private */,
       9,    0,   99,    2, 0x08 /* Private */,
      10,    0,  100,    2, 0x08 /* Private */,
      11,    0,  101,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    2,  103,    2, 0x08 /* Private */,
      18,    1,  108,    2, 0x08 /* Private */,
      21,    0,  111,    2, 0x08 /* Private */,
      22,    0,  112,    2, 0x08 /* Private */,
      23,    0,  113,    2, 0x08 /* Private */,
      24,    0,  114,    2, 0x08 /* Private */,
      25,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void appWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        appWindow *_t = static_cast<appWindow *>(_o);
        switch (_id) {
        case 0: _t->printMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateTemplateWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateTemplateHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onTrainingFinished(); break;
        case 4: _t->onDetectionFinshed(); break;
        case 5: _t->loadImage(); break;
        case 6: _t->loadFaceTemplate(); break;
        case 7: _t->loadNonFaceTemplate(); break;
        case 8: _t->loadTemplateInfoList((*reinterpret_cast< const QList<QTreeWidgetItem*>(*)>(_a[1])),(*reinterpret_cast< PCAClassifier::TemplateType(*)>(_a[2]))); break;
        case 9: _t->displaySelectedTreeWidgetItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->performPCATraining(); break;
        case 11: _t->performFaceDetection(); break;
        case 12: _t->busyProgressbar(); break;
        case 13: _t->resetProgressbar(); break;
        case 14: _t->showAbout(); break;
        default: ;
        }
    }
}

const QMetaObject appWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_appWindow.data,
      qt_meta_data_appWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *appWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *appWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_appWindow.stringdata))
        return static_cast<void*>(const_cast< appWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int appWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
