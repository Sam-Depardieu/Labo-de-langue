/****************************************************************************
** Meta object code from reading C++ file 'interfacevideo.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../interfacevideo.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfacevideo.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_InterfaceVideo_t {
    uint offsetsAndSizes[36];
    char stringdata0[15];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[14];
    char stringdata5[34];
    char stringdata6[30];
    char stringdata7[27];
    char stringdata8[28];
    char stringdata9[30];
    char stringdata10[19];
    char stringdata11[13];
    char stringdata12[4];
    char stringdata13[35];
    char stringdata14[27];
    char stringdata15[40];
    char stringdata16[6];
    char stringdata17[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_InterfaceVideo_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_InterfaceVideo_t qt_meta_stringdata_InterfaceVideo = {
    {
        QT_MOC_LITERAL(0, 14),  // "InterfaceVideo"
        QT_MOC_LITERAL(15, 17),  // "mettreAJourChrono"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 5),  // "temps"
        QT_MOC_LITERAL(40, 13),  // "chronoTermine"
        QT_MOC_LITERAL(54, 33),  // "on_pushButton_SelectVideo_cli..."
        QT_MOC_LITERAL(88, 29),  // "on_pushButton_Avant10_clicked"
        QT_MOC_LITERAL(118, 26),  // "on_pushButton_Play_clicked"
        QT_MOC_LITERAL(145, 27),  // "on_pushButton_Pause_clicked"
        QT_MOC_LITERAL(173, 29),  // "on_pushButton_Apres10_clicked"
        QT_MOC_LITERAL(203, 18),  // "animateButtonClick"
        QT_MOC_LITERAL(222, 12),  // "QPushButton*"
        QT_MOC_LITERAL(235, 3),  // "btn"
        QT_MOC_LITERAL(239, 34),  // "on_horizontalSlider_sliderRel..."
        QT_MOC_LITERAL(274, 26),  // "on_pushButtonReset_clicked"
        QT_MOC_LITERAL(301, 39),  // "on_verticalSlider_sonVideo_va..."
        QT_MOC_LITERAL(341, 5),  // "value"
        QT_MOC_LITERAL(347, 25)   // "on_pushButton_Son_clicked"
    },
    "InterfaceVideo",
    "mettreAJourChrono",
    "",
    "temps",
    "chronoTermine",
    "on_pushButton_SelectVideo_clicked",
    "on_pushButton_Avant10_clicked",
    "on_pushButton_Play_clicked",
    "on_pushButton_Pause_clicked",
    "on_pushButton_Apres10_clicked",
    "animateButtonClick",
    "QPushButton*",
    "btn",
    "on_horizontalSlider_sliderReleased",
    "on_pushButtonReset_clicked",
    "on_verticalSlider_sonVideo_valueChanged",
    "value",
    "on_pushButton_Son_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_InterfaceVideo[] = {

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
      10,    1,   95,    2, 0x08,    9 /* Private */,
      13,    0,   98,    2, 0x08,   11 /* Private */,
      14,    0,   99,    2, 0x08,   12 /* Private */,
      15,    1,  100,    2, 0x08,   13 /* Private */,
      17,    0,  103,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject InterfaceVideo::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_InterfaceVideo.offsetsAndSizes,
    qt_meta_data_InterfaceVideo,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_InterfaceVideo_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InterfaceVideo, std::true_type>,
        // method 'mettreAJourChrono'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'chronoTermine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_SelectVideo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Avant10_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Play_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Pause_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_Apres10_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'animateButtonClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        // method 'on_horizontalSlider_sliderReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonReset_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_verticalSlider_sonVideo_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_Son_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void InterfaceVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InterfaceVideo *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mettreAJourChrono((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->chronoTermine(); break;
        case 2: _t->on_pushButton_SelectVideo_clicked(); break;
        case 3: _t->on_pushButton_Avant10_clicked(); break;
        case 4: _t->on_pushButton_Play_clicked(); break;
        case 5: _t->on_pushButton_Pause_clicked(); break;
        case 6: _t->on_pushButton_Apres10_clicked(); break;
        case 7: _t->animateButtonClick((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 8: _t->on_horizontalSlider_sliderReleased(); break;
        case 9: _t->on_pushButtonReset_clicked(); break;
        case 10: _t->on_verticalSlider_sonVideo_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_pushButton_Son_clicked(); break;
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
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceVideo.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InterfaceVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
