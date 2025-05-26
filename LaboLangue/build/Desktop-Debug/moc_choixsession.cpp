/****************************************************************************
** Meta object code from reading C++ file 'choixsession.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../choixsession.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'choixsession.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_choixSession_t {
    uint offsetsAndSizes[22];
    char stringdata0[13];
    char stringdata1[34];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[5];
    char stringdata5[28];
    char stringdata6[5];
    char stringdata7[24];
    char stringdata8[24];
    char stringdata9[29];
    char stringdata10[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_choixSession_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_choixSession_t qt_meta_stringdata_choixSession = {
    {
        QT_MOC_LITERAL(0, 12),  // "choixSession"
        QT_MOC_LITERAL(13, 33),  // "on_listeSession_itemDoubleCli..."
        QT_MOC_LITERAL(47, 0),  // ""
        QT_MOC_LITERAL(48, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(65, 4),  // "item"
        QT_MOC_LITERAL(70, 27),  // "on_findLineEdit_textChanged"
        QT_MOC_LITERAL(98, 4),  // "arg1"
        QT_MOC_LITERAL(103, 23),  // "on_sortAZButton_clicked"
        QT_MOC_LITERAL(127, 23),  // "on_sortZAButton_clicked"
        QT_MOC_LITERAL(151, 28),  // "on_takeSessionButton_clicked"
        QT_MOC_LITERAL(180, 27)   // "on_delSessionButton_clicked"
    },
    "choixSession",
    "on_listeSession_itemDoubleClicked",
    "",
    "QListWidgetItem*",
    "item",
    "on_findLineEdit_textChanged",
    "arg1",
    "on_sortAZButton_clicked",
    "on_sortZAButton_clicked",
    "on_takeSessionButton_clicked",
    "on_delSessionButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_choixSession[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x08,    1 /* Private */,
       5,    1,   53,    2, 0x08,    3 /* Private */,
       7,    0,   56,    2, 0x08,    5 /* Private */,
       8,    0,   57,    2, 0x08,    6 /* Private */,
       9,    0,   58,    2, 0x08,    7 /* Private */,
      10,    0,   59,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject choixSession::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_choixSession.offsetsAndSizes,
    qt_meta_data_choixSession,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_choixSession_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<choixSession, std::true_type>,
        // method 'on_listeSession_itemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_findLineEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_sortAZButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sortZAButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_takeSessionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_delSessionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void choixSession::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<choixSession *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_listeSession_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 1: _t->on_findLineEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->on_sortAZButton_clicked(); break;
        case 3: _t->on_sortZAButton_clicked(); break;
        case 4: _t->on_takeSessionButton_clicked(); break;
        case 5: _t->on_delSessionButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *choixSession::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *choixSession::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_choixSession.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int choixSession::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
