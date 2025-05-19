/****************************************************************************
** Meta object code from reading C++ file 'audioCommunicator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../audioCommunicator.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioCommunicator.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_Student_t {
    uint offsetsAndSizes[14];
    char stringdata0[8];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[13];
    char stringdata5[16];
    char stringdata6[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Student_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Student_t qt_meta_stringdata_Student = {
    {
        QT_MOC_LITERAL(0, 7),  // "Student"
        QT_MOC_LITERAL(8, 13),  // "sendAudioData"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 16),  // "receiveAudioData"
        QT_MOC_LITERAL(40, 12),  // "playFeedback"
        QT_MOC_LITERAL(53, 15),  // "receiveResponse"
        QT_MOC_LITERAL(69, 17)   // "checkForDatagrams"
    },
    "Student",
    "sendAudioData",
    "",
    "receiveAudioData",
    "playFeedback",
    "receiveResponse",
    "checkForDatagrams"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Student[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Student::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Student.offsetsAndSizes,
    qt_meta_data_Student,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Student_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Student, std::true_type>,
        // method 'sendAudioData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveAudioData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playFeedback'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveResponse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkForDatagrams'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Student::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Student *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendAudioData(); break;
        case 1: _t->receiveAudioData(); break;
        case 2: _t->playFeedback(); break;
        case 3: _t->receiveResponse(); break;
        case 4: _t->checkForDatagrams(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Student::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Student::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Student.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Student::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
