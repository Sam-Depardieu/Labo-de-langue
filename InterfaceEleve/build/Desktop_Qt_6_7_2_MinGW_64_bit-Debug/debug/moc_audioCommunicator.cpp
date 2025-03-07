/****************************************************************************
** Meta object code from reading C++ file 'audioCommunicator.h'
**
<<<<<<< HEAD
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
=======
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../audioCommunicator.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioCommunicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
<<<<<<< HEAD
#error "This file was generated using the moc from 6.7.2. It"
=======
#error "This file was generated using the moc from 6.8.2. It"
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
<<<<<<< HEAD

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSAudioCommunicatorENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSAudioCommunicatorENDCLASS = QtMocHelpers::stringData(
=======
struct qt_meta_tag_ZN17AudioCommunicatorE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN17AudioCommunicatorE = QtMocHelpers::stringData(
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
    "AudioCommunicator",
    "onConnected",
    "",
    "onDisconnected"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
<<<<<<< HEAD
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAudioCommunicatorENDCLASS[] = {
=======

Q_CONSTINIT static const uint qt_meta_data_ZN17AudioCommunicatorE[] = {
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x08,    1 /* Private */,
       3,    0,   27,    2, 0x08,    2 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AudioCommunicator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
<<<<<<< HEAD
    qt_meta_stringdata_CLASSAudioCommunicatorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAudioCommunicatorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAudioCommunicatorENDCLASS_t,
=======
    qt_meta_stringdata_ZN17AudioCommunicatorE.offsetsAndSizes,
    qt_meta_data_ZN17AudioCommunicatorE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN17AudioCommunicatorE_t,
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AudioCommunicator, std::true_type>,
        // method 'onConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AudioCommunicator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
<<<<<<< HEAD
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioCommunicator *>(_o);
        (void)_t;
=======
    auto *_t = static_cast<AudioCommunicator *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
        switch (_id) {
        case 0: _t->onConnected(); break;
        case 1: _t->onDisconnected(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *AudioCommunicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioCommunicator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
<<<<<<< HEAD
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAudioCommunicatorENDCLASS.stringdata0))
=======
    if (!strcmp(_clname, qt_meta_stringdata_ZN17AudioCommunicatorE.stringdata0))
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioCommunicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
<<<<<<< HEAD
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
=======
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
>>>>>>> 64b7569d2d382efdbabb604fa13e996a72e94031
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
