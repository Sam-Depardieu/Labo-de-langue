/****************************************************************************
** Meta object code from reading C++ file 'qcm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
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
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSQCMENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQCMENDCLASS = QtMocHelpers::stringData(
    "QCM",
    "fermetureQCM",
    "",
    "addQuestion",
    "QString*",
    "nomQ",
    "numQ",
    "nbRep",
    "std::array<std::array<QString,2>,4>",
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
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQCMENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    4,   81,    2, 0x08,    2 /* Private */,
       3,    3,   90,    2, 0x28,    7 /* Private | MethodCloned */,
       3,    2,   97,    2, 0x28,   11 /* Private | MethodCloned */,
       3,    1,  102,    2, 0x28,   14 /* Private | MethodCloned */,
       3,    0,  105,    2, 0x28,   16 /* Private | MethodCloned */,
      10,    0,  106,    2, 0x08,   17 /* Private */,
      11,    0,  107,    2, 0x08,   18 /* Private */,
      12,    0,  108,    2, 0x08,   19 /* Private */,
      13,    3,  109,    2, 0x08,   20 /* Private */,
      18,    0,  116,    2, 0x08,   24 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 8,    5,    6,    7,    9,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,    5,    6,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 4, 0x80000000 | 4,   15,   16,   17,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCM::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQCMENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQCMENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQCMENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCM, std::true_type>,
        // method 'fermetureQCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::array<std::array<QString,2>,4>, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveQuestions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addBoxAddQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addAnswers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QuestionWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        // method 'importQCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCM *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fermetureQCM(); break;
        case 1: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<std::array<std::array<QString,2>,4>>>(_a[4]))); break;
        case 2: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3]))); break;
        case 3: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2]))); break;
        case 4: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1]))); break;
        case 5: _t->addQuestion(); break;
        case 6: _t->removeQuestion(); break;
        case 7: _t->saveQuestions(); break;
        case 8: _t->addBoxAddQuestion(); break;
        case 9: _t->addAnswers((*reinterpret_cast< std::add_pointer_t<QuestionWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3]))); break;
        case 10: _t->importQCM(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCM::*)();
            if (_t _q_method = &QCM::fermetureQCM; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
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
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQCMENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int QCM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QCM::fermetureQCM()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
