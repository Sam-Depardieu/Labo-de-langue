/****************************************************************************
** Meta object code from reading C++ file 'qcm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qcm.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcm.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_QCM_t {
    uint offsetsAndSizes[38];
    char stringdata0[4];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[9];
    char stringdata5[5];
    char stringdata6[5];
    char stringdata7[6];
    char stringdata8[26];
    char stringdata9[8];
    char stringdata10[15];
    char stringdata11[14];
    char stringdata12[18];
    char stringdata13[11];
    char stringdata14[16];
    char stringdata15[9];
    char stringdata16[6];
    char stringdata17[8];
    char stringdata18[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCM_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCM_t qt_meta_stringdata_QCM = {
    {
        QT_MOC_LITERAL(0, 3),  // "QCM"
        QT_MOC_LITERAL(4, 12),  // "fermetureQCM"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 11),  // "addQuestion"
        QT_MOC_LITERAL(30, 8),  // "QString*"
        QT_MOC_LITERAL(39, 4),  // "nomQ"
        QT_MOC_LITERAL(44, 4),  // "numQ"
        QT_MOC_LITERAL(49, 5),  // "nbRep"
        QT_MOC_LITERAL(55, 25),  // "array<array<QString,2>,4>"
        QT_MOC_LITERAL(81, 7),  // "choices"
        QT_MOC_LITERAL(89, 14),  // "removeQuestion"
        QT_MOC_LITERAL(104, 13),  // "saveQuestions"
        QT_MOC_LITERAL(118, 17),  // "addBoxAddQuestion"
        QT_MOC_LITERAL(136, 10),  // "addAnswers"
        QT_MOC_LITERAL(147, 15),  // "QuestionWidget*"
        QT_MOC_LITERAL(163, 8),  // "question"
        QT_MOC_LITERAL(172, 5),  // "choix"
        QT_MOC_LITERAL(178, 7),  // "correct"
        QT_MOC_LITERAL(186, 9)   // "importQCM"
    },
    "QCM",
    "fermetureQCM",
    "",
    "addQuestion",
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
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCM[] = {

 // content:
      10,       // revision
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
    qt_meta_stringdata_QCM.offsetsAndSizes,
    qt_meta_data_QCM,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCM_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCM, std::true_type>,
        // method 'fermetureQCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addQuestion'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString *, std::false_type>,
        QtPrivate::TypeAndForceComplete<array<array<QString,2>,4>, std::false_type>,
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
        case 1: _t->addQuestion((*reinterpret_cast< std::add_pointer_t<QString*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<array<array<QString,2>,4>>>(_a[4]))); break;
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
    if (!strcmp(_clname, qt_meta_stringdata_QCM.stringdata0))
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
QT_END_MOC_NAMESPACE
