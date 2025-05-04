/****************************************************************************
** Meta object code from reading C++ file 'qcm.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qcm.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcm.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3QCME_t {};
} // unnamed namespace

template <> constexpr inline auto QCM::qt_create_metaobjectdata<qt_meta_tag_ZN3QCME_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QCM",
        "addQuestion",
        "",
        "QString*",
        "nomQ",
        "numQ",
        "nbRep",
        "array<array<QString,2>,4>",
        "choices",
        "removeQuestion",
        "saveQuestions",
        "addBoxAddQuestion",
        "addAnswers",
        "QuestionWidget*",
        "question",
        "choix",
        "correct",
        "importQCM"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'addQuestion'
        QtMocHelpers::SlotData<void(QString *, QString *, QString *, array<array<QString,2>,4>)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 }, { 0x80000000 | 7, 8 },
        }}),
        // Slot 'addQuestion'
        QtMocHelpers::SlotData<void(QString *, QString *, QString *)>(1, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 },
        }}),
        // Slot 'addQuestion'
        QtMocHelpers::SlotData<void(QString *, QString *)>(1, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 },
        }}),
        // Slot 'addQuestion'
        QtMocHelpers::SlotData<void(QString *)>(1, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'addQuestion'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate | QMC::MethodCloned, QMetaType::Void),
        // Slot 'removeQuestion'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveQuestions'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'addBoxAddQuestion'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'addAnswers'
        QtMocHelpers::SlotData<void(QuestionWidget *, QString *, QString *)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 13, 14 }, { 0x80000000 | 3, 15 }, { 0x80000000 | 3, 16 },
        }}),
        // Slot 'importQCM'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QCM, qt_meta_tag_ZN3QCME_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QCM::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3QCME_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3QCME_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3QCME_t>.metaTypes,
    nullptr
} };

void QCM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QCM *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<array<array<QString,2>,4>>>(_a[4]))); break;
        case 1: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3]))); break;
        case 2: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2]))); break;
        case 3: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1]))); break;
        case 4: _t->addQuestion(); break;
        case 5: _t->removeQuestion(); break;
        case 6: _t->saveQuestions(); break;
        case 7: _t->addBoxAddQuestion(); break;
        case 8: _t->addAnswers((*reinterpret_cast< std::add_pointer_t<QuestionWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3]))); break;
        case 9: _t->importQCM(); break;
        default: ;
        }
    }
}

const QMetaObject *QCM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3QCME_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int QCM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
