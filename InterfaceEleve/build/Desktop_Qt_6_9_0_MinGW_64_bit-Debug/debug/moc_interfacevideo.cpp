/****************************************************************************
** Meta object code from reading C++ file 'interfacevideo.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../interfacevideo.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfacevideo.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14InterfaceVideoE_t {};
} // unnamed namespace

template <> constexpr inline auto InterfaceVideo::qt_create_metaobjectdata<qt_meta_tag_ZN14InterfaceVideoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "InterfaceVideo",
        "on_pushButton_SelectVideo_clicked",
        "",
        "on_pushButton_Avant10_clicked",
        "on_pushButton_Play_clicked",
        "on_pushButton_Pause_clicked",
        "on_pushButton_Apres10_clicked",
        "animateButtonClick",
        "QPushButton*",
        "btn",
        "on_horizontalSlider_sliderReleased",
        "on_pushButtonReset_clicked",
        "onUdpTimeout",
        "on_verticalSlider_sonVideo_valueChanged",
        "value",
        "on_pushButton_Son_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_pushButton_SelectVideo_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Avant10_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Play_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Pause_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Apres10_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'animateButtonClick'
        QtMocHelpers::SlotData<void(QPushButton *)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'on_horizontalSlider_sliderReleased'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButtonReset_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUdpTimeout'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_verticalSlider_sonVideo_valueChanged'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Slot 'on_pushButton_Son_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InterfaceVideo, qt_meta_tag_ZN14InterfaceVideoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject InterfaceVideo::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14InterfaceVideoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14InterfaceVideoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14InterfaceVideoE_t>.metaTypes,
    nullptr
} };

void InterfaceVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InterfaceVideo *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_pushButton_SelectVideo_clicked(); break;
        case 1: _t->on_pushButton_Avant10_clicked(); break;
        case 2: _t->on_pushButton_Play_clicked(); break;
        case 3: _t->on_pushButton_Pause_clicked(); break;
        case 4: _t->on_pushButton_Apres10_clicked(); break;
        case 5: _t->animateButtonClick((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_sliderReleased(); break;
        case 7: _t->on_pushButtonReset_clicked(); break;
        case 8: _t->onUdpTimeout(); break;
        case 9: _t->on_verticalSlider_sonVideo_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_pushButton_Son_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *InterfaceVideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceVideo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14InterfaceVideoE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InterfaceVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
