/****************************************************************************
** Meta object code from reading C++ file 'audioCommunicator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../audioCommunicator.h"
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
    uint offsetsAndSizes[28];
    char stringdata0[8];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[13];
    char stringdata6[11];
    char stringdata7[8];
    char stringdata8[26];
    char stringdata9[14];
    char stringdata10[9];
    char stringdata11[29];
    char stringdata12[10];
    char stringdata13[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Student_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Student_t qt_meta_stringdata_Student = {
    {
        QT_MOC_LITERAL(0, 7),  // "Student"
        QT_MOC_LITERAL(8, 19),  // "captureAndSendAudio"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 12),  // "receiveAudio"
        QT_MOC_LITERAL(42, 16),  // "changeAudioGroup"
        QT_MOC_LITERAL(59, 12),  // "QHostAddress"
        QT_MOC_LITERAL(72, 10),  // "newAddress"
        QT_MOC_LITERAL(83, 7),  // "newPort"
        QT_MOC_LITERAL(91, 25),  // "onAudioSourceStateChanged"
        QT_MOC_LITERAL(117, 13),  // "QAudio::State"
        QT_MOC_LITERAL(131, 8),  // "newState"
        QT_MOC_LITERAL(140, 28),  // "initializeAudioCommunication"
        QT_MOC_LITERAL(169, 9),  // "muteAudio"
        QT_MOC_LITERAL(179, 11)   // "unmuteAudio"
    },
    "Student",
    "captureAndSendAudio",
    "",
    "receiveAudio",
    "changeAudioGroup",
    "QHostAddress",
    "newAddress",
    "newPort",
    "onAudioSourceStateChanged",
    "QAudio::State",
    "newState",
    "initializeAudioCommunication",
    "muteAudio",
    "unmuteAudio"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Student[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x0a,    1 /* Public */,
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    2,   58,    2, 0x0a,    3 /* Public */,
       8,    1,   63,    2, 0x0a,    6 /* Public */,
      11,    0,   66,    2, 0x0a,    8 /* Public */,
      12,    0,   67,    2, 0x0a,    9 /* Public */,
      13,    0,   68,    2, 0x0a,   10 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::UShort,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
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
        // method 'captureAndSendAudio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveAudio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeAudioGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QHostAddress &, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'onAudioSourceStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAudio::State, std::false_type>,
        // method 'initializeAudioCommunication'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'muteAudio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unmuteAudio'
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
        case 0: _t->captureAndSendAudio(); break;
        case 1: _t->receiveAudio(); break;
        case 2: _t->changeAudioGroup((*reinterpret_cast< std::add_pointer_t<QHostAddress>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2]))); break;
        case 3: _t->onAudioSourceStateChanged((*reinterpret_cast< std::add_pointer_t<QAudio::State>>(_a[1]))); break;
        case 4: _t->initializeAudioCommunication(); break;
        case 5: _t->muteAudio(); break;
        case 6: _t->unmuteAudio(); break;
        default: ;
        }
    }
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
