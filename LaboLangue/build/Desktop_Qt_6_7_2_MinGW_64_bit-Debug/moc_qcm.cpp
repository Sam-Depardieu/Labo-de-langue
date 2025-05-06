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
    uint offsetsAndSizes[36];
    char stringdata0[4];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[6];
    char stringdata7[26];
    char stringdata8[8];
    char stringdata9[15];
    char stringdata10[14];
    char stringdata11[18];
    char stringdata12[11];
    char stringdata13[16];
    char stringdata14[9];
    char stringdata15[6];
    char stringdata16[8];
    char stringdata17[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCM_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCM_t qt_meta_stringdata_QCM = {
    {
        QT_MOC_LITERAL(0, 3),  // "QCM"
        QT_MOC_LITERAL(4, 11),  // "addQuestion"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 8),  // "QString*"
        QT_MOC_LITERAL(26, 4),  // "nomQ"
        QT_MOC_LITERAL(31, 4),  // "numQ"
        QT_MOC_LITERAL(36, 5),  // "nbRep"
        QT_MOC_LITERAL(42, 25),  // "array<array<QString,2>,4>"
        QT_MOC_LITERAL(68, 7),  // "choices"
        QT_MOC_LITERAL(76, 14),  // "removeQuestion"
        QT_MOC_LITERAL(91, 13),  // "saveQuestions"
        QT_MOC_LITERAL(105, 17),  // "addBoxAddQuestion"
        QT_MOC_LITERAL(123, 10),  // "addAnswers"
        QT_MOC_LITERAL(134, 15),  // "QuestionWidget*"
        QT_MOC_LITERAL(150, 8),  // "question"
        QT_MOC_LITERAL(159, 5),  // "choix"
        QT_MOC_LITERAL(165, 7),  // "correct"
        QT_MOC_LITERAL(173, 9)   // "importQCM"
    },
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
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCM[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   74,    2, 0x08,    1 /* Private */,
       1,    3,   83,    2, 0x28,    6 /* Private | MethodCloned */,
       1,    2,   90,    2, 0x28,   10 /* Private | MethodCloned */,
       1,    1,   95,    2, 0x28,   13 /* Private | MethodCloned */,
       1,    0,   98,    2, 0x28,   15 /* Private | MethodCloned */,
       9,    0,   99,    2, 0x08,   16 /* Private */,
      10,    0,  100,    2, 0x08,   17 /* Private */,
      11,    0,  101,    2, 0x08,   18 /* Private */,
      12,    3,  102,    2, 0x08,   19 /* Private */,
      17,    0,  109,    2, 0x08,   23 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 7,    4,    5,    6,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 3, 0x80000000 | 3,   14,   15,   16,
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
