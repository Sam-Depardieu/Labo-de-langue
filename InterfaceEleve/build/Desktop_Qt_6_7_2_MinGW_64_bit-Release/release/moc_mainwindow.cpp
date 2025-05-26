/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[44];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[11];
    char stringdata5[18];
    char stringdata6[31];
    char stringdata7[14];
    char stringdata8[11];
    char stringdata9[6];
    char stringdata10[16];
    char stringdata11[8];
    char stringdata12[13];
    char stringdata13[12];
    char stringdata14[12];
    char stringdata15[16];
    char stringdata16[21];
    char stringdata17[13];
    char stringdata18[20];
    char stringdata19[17];
    char stringdata20[12];
    char stringdata21[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 14),  // "chronoMisAJour"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 5),  // "temps"
        QT_MOC_LITERAL(33, 10),  // "chronoFini"
        QT_MOC_LITERAL(44, 17),  // "connectToDatabase"
        QT_MOC_LITERAL(62, 30),  // "on_pushButtonConnexion_clicked"
        QT_MOC_LITERAL(93, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(107, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(118, 5),  // "event"
        QT_MOC_LITERAL(124, 15),  // "keyReleaseEvent"
        QT_MOC_LITERAL(140, 7),  // "askPATH"
        QT_MOC_LITERAL(148, 12),  // "receiveInter"
        QT_MOC_LITERAL(161, 11),  // "receivePath"
        QT_MOC_LITERAL(173, 11),  // "receiveInfo"
        QT_MOC_LITERAL(185, 15),  // "receiveConsigne"
        QT_MOC_LITERAL(201, 20),  // "handleRestartCommand"
        QT_MOC_LITERAL(222, 12),  // "updateChrono"
        QT_MOC_LITERAL(235, 19),  // "faireClignoterLabel"
        QT_MOC_LITERAL(255, 16),  // "stopClignotement"
        QT_MOC_LITERAL(272, 11),  // "startChrono"
        QT_MOC_LITERAL(284, 5)   // "duree"
    },
    "MainWindow",
    "chronoMisAJour",
    "",
    "temps",
    "chronoFini",
    "connectToDatabase",
    "on_pushButtonConnexion_clicked",
    "keyPressEvent",
    "QKeyEvent*",
    "event",
    "keyReleaseEvent",
    "askPATH",
    "receiveInter",
    "receivePath",
    "receiveInfo",
    "receiveConsigne",
    "handleRestartCommand",
    "updateChrono",
    "faireClignoterLabel",
    "stopClignotement",
    "startChrono",
    "duree"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  110,    2, 0x06,    1 /* Public */,
       4,    0,  113,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,  114,    2, 0x08,    4 /* Private */,
       6,    0,  115,    2, 0x08,    5 /* Private */,
       7,    1,  116,    2, 0x08,    6 /* Private */,
      10,    1,  119,    2, 0x08,    8 /* Private */,
      11,    0,  122,    2, 0x08,   10 /* Private */,
      12,    0,  123,    2, 0x08,   11 /* Private */,
      13,    0,  124,    2, 0x08,   12 /* Private */,
      14,    0,  125,    2, 0x08,   13 /* Private */,
      15,    0,  126,    2, 0x08,   14 /* Private */,
      16,    0,  127,    2, 0x08,   15 /* Private */,
      17,    0,  128,    2, 0x08,   16 /* Private */,
      18,    0,  129,    2, 0x08,   17 /* Private */,
      19,    0,  130,    2, 0x08,   18 /* Private */,
      20,    1,  131,    2, 0x08,   19 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QTime,   21,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'chronoMisAJour'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'chronoFini'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectToDatabase'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_pushButtonConnexion_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'keyReleaseEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'askPATH'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveInter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receivePath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveConsigne'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleRestartCommand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateChrono'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'faireClignoterLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopClignotement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startChrono'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QTime &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->chronoMisAJour((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->chronoFini(); break;
        case 2: { bool _r = _t->connectToDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->on_pushButtonConnexion_clicked(); break;
        case 4: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 5: _t->keyReleaseEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 6: _t->askPATH(); break;
        case 7: _t->receiveInter(); break;
        case 8: _t->receivePath(); break;
        case 9: _t->receiveInfo(); break;
        case 10: _t->receiveConsigne(); break;
        case 11: _t->handleRestartCommand(); break;
        case 12: _t->updateChrono(); break;
        case 13: _t->faireClignoterLabel(); break;
        case 14: _t->stopClignotement(); break;
        case 15: _t->startChrono((*reinterpret_cast< std::add_pointer_t<QTime>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (_t _q_method = &MainWindow::chronoMisAJour; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::chronoFini; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::chronoMisAJour(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::chronoFini()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
