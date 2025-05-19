/****************************************************************************
** Meta object code from reading C++ file 'interfaceaudio.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../interfaceaudio.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaceaudio.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_InterfaceAudio_t {
    uint offsetsAndSizes[34];
    char stringdata0[15];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[14];
    char stringdata5[34];
    char stringdata6[27];
    char stringdata7[28];
    char stringdata8[28];
    char stringdata9[28];
    char stringdata10[35];
    char stringdata11[19];
    char stringdata12[13];
    char stringdata13[4];
    char stringdata14[27];
    char stringdata15[14];
    char stringdata16[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_InterfaceAudio_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_InterfaceAudio_t qt_meta_stringdata_InterfaceAudio = {
    {
        QT_MOC_LITERAL(0, 14),  // "InterfaceAudio"
        QT_MOC_LITERAL(15, 17),  // "mettreAJourChrono"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 5),  // "temps"
        QT_MOC_LITERAL(40, 13),  // "chronoTermine"
        QT_MOC_LITERAL(54, 33),  // "on_pushButton_SelectAudio_cli..."
        QT_MOC_LITERAL(88, 26),  // "on_pushButton_Play_clicked"
        QT_MOC_LITERAL(115, 27),  // "on_pushButton_Pause_clicked"
        QT_MOC_LITERAL(143, 27),  // "on_pushButton_Avant_clicked"
        QT_MOC_LITERAL(171, 27),  // "on_pushButton_Apres_clicked"
        QT_MOC_LITERAL(199, 34),  // "on_horizontalSlider_sliderRel..."
        QT_MOC_LITERAL(234, 18),  // "animateButtonClick"
        QT_MOC_LITERAL(253, 12),  // "QPushButton*"
        QT_MOC_LITERAL(266, 3),  // "btn"
        QT_MOC_LITERAL(270, 26),  // "on_pushButtonReset_clicked"
        QT_MOC_LITERAL(297, 13),  // "receiveChrono"
        QT_MOC_LITERAL(311, 25)   // "on_pushButton_Son_clicked"
    },
    "InterfaceAudio",
    "mettreAJourChrono",
    "",
    "temps",
    "chronoTermine",
    "on_pushButton_SelectAudio_clicked",
    "on_pushButton_Play_clicked",
    "on_pushButton_Pause_clicked",
    "on_pushButton_Avant_clicked",
    "on_pushButton_Apres_clicked",
    "on_horizontalSlider_sliderReleased",
    "animateButtonClick",
    "QPushButton*",
    "btn",
    "on_pushButtonReset_clicked",
    "receiveChrono",
    "on_pushButton_Son_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_InterfaceAudio[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x0a,    1 /* Public */,
       4,    0,   89,    2, 0x0a,    3 /* Public */,
       5,    0,   90,    2, 0x08,    4 /* Private */,
       6,    0,   91,    2, 0x08,    5 /* Private */,
       7,    0,   92,    2, 0x08,    6 /* Private */,
       8,    0,   93,    2, 0x08,    7 /* Private */,
       9,    0,   94,    2, 0x08,    8 /* Private */,
      10,    0,   95,    2, 0x08,    9 /* Private */,
      11,    1,   96,    2, 0x08,   10 /* Private */,
      14,    0,   99,    2, 0x08,   12 /* Private */,
      15,    0,  100,    2, 0x08,   13 /* Private */,
      16,    0,  101,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject InterfaceAudio::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_InterfaceAudio.offsetsAndSizes,
    qt_meta_data_InterfaceAudio,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_InterfaceAudio_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InterfaceAudio, std::true_type>,
        // method 'mettreAJourChrono'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'chronoTermine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_SelectAudio_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Play_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Pause_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Avant_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Apres_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_horizontalSlider_sliderReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'animateButtonClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        // method 'on_pushButtonReset_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveChrono'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Son_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void InterfaceAudio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InterfaceAudio *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mettreAJourChrono((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->chronoTermine(); break;
        case 2: _t->on_pushButton_SelectAudio_clicked(); break;
        case 3: _t->on_pushButton_Play_clicked(); break;
        case 4: _t->on_pushButton_Pause_clicked(); break;
        case 5: _t->on_pushButton_Avant_clicked(); break;
        case 6: _t->on_pushButton_Apres_clicked(); break;
        case 7: _t->on_horizontalSlider_sliderReleased(); break;
        case 8: _t->animateButtonClick((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 9: _t->on_pushButtonReset_clicked(); break;
        case 10: _t->receiveChrono(); break;
        case 11: _t->on_pushButton_Son_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *InterfaceAudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceAudio.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InterfaceAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
