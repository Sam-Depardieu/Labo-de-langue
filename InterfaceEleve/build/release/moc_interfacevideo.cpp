/****************************************************************************
** Meta object code from reading C++ file 'interfacevideo.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../interfacevideo.h"
#include <QtGui/qtextcursor.h>
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
    char stringdata1[34];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[27];
    char stringdata5[28];
    char stringdata6[30];
    char stringdata7[19];
    char stringdata8[13];
    char stringdata9[4];
    char stringdata10[35];
    char stringdata11[27];
    char stringdata12[40];
    char stringdata13[6];
    char stringdata14[26];
    char stringdata15[18];
    char stringdata16[20];
    char stringdata17[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_InterfaceVideo_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_InterfaceVideo_t qt_meta_stringdata_InterfaceVideo = {
    {
        QT_MOC_LITERAL(0, 14),  // "InterfaceVideo"
        QT_MOC_LITERAL(15, 33),  // "on_pushButton_SelectVideo_cli..."
        QT_MOC_LITERAL(49, 0),  // ""
        QT_MOC_LITERAL(50, 29),  // "on_pushButton_Avant10_clicked"
        QT_MOC_LITERAL(80, 26),  // "on_pushButton_Play_clicked"
        QT_MOC_LITERAL(107, 27),  // "on_pushButton_Pause_clicked"
        QT_MOC_LITERAL(135, 29),  // "on_pushButton_Apres10_clicked"
        QT_MOC_LITERAL(165, 18),  // "animateButtonClick"
        QT_MOC_LITERAL(184, 12),  // "QPushButton*"
        QT_MOC_LITERAL(197, 3),  // "btn"
        QT_MOC_LITERAL(201, 34),  // "on_horizontalSlider_sliderRel..."
        QT_MOC_LITERAL(236, 26),  // "on_pushButtonReset_clicked"
        QT_MOC_LITERAL(263, 39),  // "on_verticalSlider_sonVideo_va..."
        QT_MOC_LITERAL(303, 5),  // "value"
        QT_MOC_LITERAL(309, 25),  // "on_pushButton_Son_clicked"
        QT_MOC_LITERAL(335, 17),  // "updateChronoLabel"
        QT_MOC_LITERAL(353, 19),  // "faireClignoterLabel"
        QT_MOC_LITERAL(373, 10)   // "receiveCmd"
    },
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
    "on_verticalSlider_sonVideo_valueChanged",
    "value",
    "on_pushButton_Son_clicked",
    "updateChronoLabel",
    "faireClignoterLabel",
    "receiveCmd"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_InterfaceVideo[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    1,   97,    2, 0x08,    6 /* Private */,
      10,    0,  100,    2, 0x08,    8 /* Private */,
      11,    0,  101,    2, 0x08,    9 /* Private */,
      12,    1,  102,    2, 0x08,   10 /* Private */,
      14,    0,  105,    2, 0x08,   12 /* Private */,
      15,    0,  106,    2, 0x08,   13 /* Private */,
      16,    0,  107,    2, 0x08,   14 /* Private */,
      17,    0,  108,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateChronoLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'faireClignoterLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveCmd'
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
        case 0: _t->on_pushButton_SelectVideo_clicked(); break;
        case 1: _t->on_pushButton_Avant10_clicked(); break;
        case 2: _t->on_pushButton_Play_clicked(); break;
        case 3: _t->on_pushButton_Pause_clicked(); break;
        case 4: _t->on_pushButton_Apres10_clicked(); break;
        case 5: _t->animateButtonClick((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_sliderReleased(); break;
        case 7: _t->on_pushButtonReset_clicked(); break;
        case 8: _t->on_verticalSlider_sonVideo_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_pushButton_Son_clicked(); break;
        case 10: _t->updateChronoLabel(); break;
        case 11: _t->faireClignoterLabel(); break;
        case 12: _t->receiveCmd(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
