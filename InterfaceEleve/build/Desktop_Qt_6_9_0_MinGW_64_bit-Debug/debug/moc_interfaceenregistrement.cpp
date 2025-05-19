/****************************************************************************
** Meta object code from reading C++ file 'interfaceenregistrement.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../interfaceenregistrement.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaceenregistrement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN23InterfaceEnregistrementE_t {};
} // unnamed namespace

template <> constexpr inline auto InterfaceEnregistrement::qt_create_metaobjectdata<qt_meta_tag_ZN23InterfaceEnregistrementE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "InterfaceEnregistrement",
        "on_pushButtonSpeak_clicked",
        "",
        "on_pushButtonPause_clicked",
        "on_pushButtonClear_clicked",
        "on_pushButtonSon_clicked",
        "on_pushButtonRetourArriere_clicked",
        "on_pushButtonAppelProf_clicked",
        "on_pushButtonAvancer_clicked",
        "on_pushButtonEnregistrer_clicked",
        "on_pushButtonPlay_clicked",
        "animateButtonClick",
        "QPushButton*",
        "btn",
        "updateChrono",
        "rewindChrono",
        "updateChronoLabel",
        "onRecorderStateChanged",
        "QMediaRecorder::RecorderState",
        "state",
        "onRecorderErrorOccurred",
        "QMediaRecorder::Error",
        "error",
        "errorString",
        "checkPlaybackPosition",
        "position",
        "onUdpTimeout"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_pushButtonSpeak_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonPause_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonClear_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonSon_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonRetourArriere_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonAppelProf_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonAvancer_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonEnregistrer_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonPlay_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'animateButtonClick'
        QtMocHelpers::SlotData<void(QPushButton *)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'updateChrono'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'rewindChrono'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateChronoLabel'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRecorderStateChanged'
        QtMocHelpers::SlotData<void(QMediaRecorder::RecorderState)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'onRecorderErrorOccurred'
        QtMocHelpers::SlotData<void(QMediaRecorder::Error, const QString &)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 21, 22 }, { QMetaType::QString, 23 },
        }}),
        // Slot 'checkPlaybackPosition'
        QtMocHelpers::SlotData<void(qint64)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 25 },
        }}),
        // Slot 'onUdpTimeout'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InterfaceEnregistrement, qt_meta_tag_ZN23InterfaceEnregistrementE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject InterfaceEnregistrement::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23InterfaceEnregistrementE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23InterfaceEnregistrementE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN23InterfaceEnregistrementE_t>.metaTypes,
    nullptr
} };

void InterfaceEnregistrement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InterfaceEnregistrement *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_pushButtonSpeak_clicked(); break;
        case 1: _t->on_pushButtonPause_clicked(); break;
        case 2: _t->on_pushButtonClear_clicked(); break;
        case 3: _t->on_pushButtonSon_clicked(); break;
        case 4: _t->on_pushButtonRetourArriere_clicked(); break;
        case 5: _t->on_pushButtonAppelProf_clicked(); break;
        case 6: _t->on_pushButtonAvancer_clicked(); break;
        case 7: _t->on_pushButtonEnregistrer_clicked(); break;
        case 8: _t->on_pushButtonPlay_clicked(); break;
        case 9: _t->animateButtonClick((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 10: _t->updateChrono(); break;
        case 11: _t->rewindChrono(); break;
        case 12: _t->updateChronoLabel(); break;
        case 13: _t->onRecorderStateChanged((*reinterpret_cast< std::add_pointer_t<QMediaRecorder::RecorderState>>(_a[1]))); break;
        case 14: _t->onRecorderErrorOccurred((*reinterpret_cast< std::add_pointer_t<QMediaRecorder::Error>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->checkPlaybackPosition((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 16: _t->onUdpTimeout(); break;
        default: ;
        }
    }
}

const QMetaObject *InterfaceEnregistrement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceEnregistrement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23InterfaceEnregistrementE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InterfaceEnregistrement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
