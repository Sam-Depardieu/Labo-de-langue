/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[104];
    char stringdata0[11];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[11];
    char stringdata5[6];
    char stringdata6[17];
    char stringdata7[18];
    char stringdata8[26];
    char stringdata9[24];
    char stringdata10[21];
    char stringdata11[25];
    char stringdata12[37];
    char stringdata13[6];
    char stringdata14[24];
    char stringdata15[17];
    char stringdata16[13];
    char stringdata17[7];
    char stringdata18[7];
    char stringdata19[20];
    char stringdata20[13];
    char stringdata21[7];
    char stringdata22[9];
    char stringdata23[8];
    char stringdata24[8];
    char stringdata25[8];
    char stringdata26[13];
    char stringdata27[8];
    char stringdata28[8];
    char stringdata29[8];
    char stringdata30[21];
    char stringdata31[23];
    char stringdata32[21];
    char stringdata33[16];
    char stringdata34[6];
    char stringdata35[24];
    char stringdata36[21];
    char stringdata37[16];
    char stringdata38[13];
    char stringdata39[23];
    char stringdata40[13];
    char stringdata41[23];
    char stringdata42[26];
    char stringdata43[16];
    char stringdata44[18];
    char stringdata45[5];
    char stringdata46[22];
    char stringdata47[24];
    char stringdata48[31];
    char stringdata49[28];
    char stringdata50[29];
    char stringdata51[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 21),  // "on_PlanButton_clicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(48, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(59, 5),  // "event"
        QT_MOC_LITERAL(65, 16),  // "loadImagesFromDB"
        QT_MOC_LITERAL(82, 17),  // "connectToDatabase"
        QT_MOC_LITERAL(100, 25),  // "onImageGroupDoubleClicked"
        QT_MOC_LITERAL(126, 23),  // "setupActivitiesComboBox"
        QT_MOC_LITERAL(150, 20),  // "setupClassesComboBox"
        QT_MOC_LITERAL(171, 24),  // "on_SessionButton_clicked"
        QT_MOC_LITERAL(196, 36),  // "on_ChoixActivite_currentIndex..."
        QT_MOC_LITERAL(233, 5),  // "index"
        QT_MOC_LITERAL(239, 23),  // "on_selectManuel_clicked"
        QT_MOC_LITERAL(263, 16),  // "editStatusButton"
        QT_MOC_LITERAL(280, 12),  // "QPushButton*"
        QT_MOC_LITERAL(293, 6),  // "button"
        QT_MOC_LITERAL(300, 6),  // "status"
        QT_MOC_LITERAL(307, 19),  // "addHorizontalLayout"
        QT_MOC_LITERAL(327, 12),  // "QVBoxLayout*"
        QT_MOC_LITERAL(340, 6),  // "layout"
        QT_MOC_LITERAL(347, 8),  // "QWidget*"
        QT_MOC_LITERAL(356, 7),  // "widget1"
        QT_MOC_LITERAL(364, 7),  // "widget2"
        QT_MOC_LITERAL(372, 7),  // "widget3"
        QT_MOC_LITERAL(380, 12),  // "addButtonRow"
        QT_MOC_LITERAL(393, 7),  // "button1"
        QT_MOC_LITERAL(401, 7),  // "button2"
        QT_MOC_LITERAL(409, 7),  // "button3"
        QT_MOC_LITERAL(417, 20),  // "on_selectAll_clicked"
        QT_MOC_LITERAL(438, 22),  // "on_validButton_clicked"
        QT_MOC_LITERAL(461, 20),  // "showCheckIconOnGroup"
        QT_MOC_LITERAL(482, 15),  // "iconEleveGroup*"
        QT_MOC_LITERAL(498, 5),  // "group"
        QT_MOC_LITERAL(504, 23),  // "on_SourceButton_clicked"
        QT_MOC_LITERAL(528, 20),  // "on_delButton_clicked"
        QT_MOC_LITERAL(549, 15),  // "saveSessionData"
        QT_MOC_LITERAL(565, 12),  // "isNewSession"
        QT_MOC_LITERAL(578, 22),  // "on_echapButton_clicked"
        QT_MOC_LITERAL(601, 12),  // "resetSession"
        QT_MOC_LITERAL(614, 22),  // "on_loadSession_clicked"
        QT_MOC_LITERAL(637, 25),  // "on_CreationButton_clicked"
        QT_MOC_LITERAL(663, 15),  // "changeNameTable"
        QT_MOC_LITERAL(679, 17),  // "QTableWidgetItem*"
        QT_MOC_LITERAL(697, 4),  // "item"
        QT_MOC_LITERAL(702, 21),  // "on_muteButton_clicked"
        QT_MOC_LITERAL(724, 23),  // "on_demuteButton_clicked"
        QT_MOC_LITERAL(748, 30),  // "on_desactiverSonButton_clicked"
        QT_MOC_LITERAL(779, 27),  // "on_activerSonButton_clicked"
        QT_MOC_LITERAL(807, 28),  // "on_creerGroupeButton_clicked"
        QT_MOC_LITERAL(836, 24)   // "on_annulerButton_clicked"
    },
    "MainWindow",
    "on_PlanButton_clicked",
    "",
    "keyPressEvent",
    "QKeyEvent*",
    "event",
    "loadImagesFromDB",
    "connectToDatabase",
    "onImageGroupDoubleClicked",
    "setupActivitiesComboBox",
    "setupClassesComboBox",
    "on_SessionButton_clicked",
    "on_ChoixActivite_currentIndexChanged",
    "index",
    "on_selectManuel_clicked",
    "editStatusButton",
    "QPushButton*",
    "button",
    "status",
    "addHorizontalLayout",
    "QVBoxLayout*",
    "layout",
    "QWidget*",
    "widget1",
    "widget2",
    "widget3",
    "addButtonRow",
    "button1",
    "button2",
    "button3",
    "on_selectAll_clicked",
    "on_validButton_clicked",
    "showCheckIconOnGroup",
    "iconEleveGroup*",
    "group",
    "on_SourceButton_clicked",
    "on_delButton_clicked",
    "saveSessionData",
    "isNewSession",
    "on_echapButton_clicked",
    "resetSession",
    "on_loadSession_clicked",
    "on_CreationButton_clicked",
    "changeNameTable",
    "QTableWidgetItem*",
    "item",
    "on_muteButton_clicked",
    "on_demuteButton_clicked",
    "on_desactiverSonButton_clicked",
    "on_activerSonButton_clicked",
    "on_creerGroupeButton_clicked",
    "on_annulerButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  200,    2, 0x08,    1 /* Private */,
       3,    1,  201,    2, 0x08,    2 /* Private */,
       6,    0,  204,    2, 0x08,    4 /* Private */,
       7,    0,  205,    2, 0x08,    5 /* Private */,
       8,    0,  206,    2, 0x08,    6 /* Private */,
       9,    0,  207,    2, 0x08,    7 /* Private */,
      10,    0,  208,    2, 0x08,    8 /* Private */,
      11,    0,  209,    2, 0x08,    9 /* Private */,
      12,    1,  210,    2, 0x08,   10 /* Private */,
      14,    0,  213,    2, 0x08,   12 /* Private */,
      15,    2,  214,    2, 0x08,   13 /* Private */,
      19,    3,  219,    2, 0x08,   16 /* Private */,
      19,    4,  226,    2, 0x08,   20 /* Private */,
      26,    4,  235,    2, 0x08,   25 /* Private */,
      30,    0,  244,    2, 0x08,   30 /* Private */,
      31,    0,  245,    2, 0x08,   31 /* Private */,
      32,    1,  246,    2, 0x08,   32 /* Private */,
      35,    0,  249,    2, 0x08,   34 /* Private */,
      36,    0,  250,    2, 0x08,   35 /* Private */,
      37,    1,  251,    2, 0x08,   36 /* Private */,
      39,    0,  254,    2, 0x08,   38 /* Private */,
      40,    0,  255,    2, 0x08,   39 /* Private */,
      41,    0,  256,    2, 0x08,   40 /* Private */,
      42,    0,  257,    2, 0x08,   41 /* Private */,
      43,    1,  258,    2, 0x08,   42 /* Private */,
      46,    0,  261,    2, 0x08,   44 /* Private */,
      47,    0,  262,    2, 0x08,   45 /* Private */,
      48,    0,  263,    2, 0x08,   46 /* Private */,
      49,    0,  264,    2, 0x08,   47 /* Private */,
      50,    0,  265,    2, 0x08,   48 /* Private */,
      51,    0,  266,    2, 0x08,   49 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Bool,   17,   18,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 22,   21,   23,   24,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 22, 0x80000000 | 22,   21,   23,   24,   25,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 22, 0x80000000 | 22,   21,   27,   28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 44,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_PlanButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'loadImagesFromDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectToDatabase'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onImageGroupDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupActivitiesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupClassesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_SessionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ChoixActivite_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_selectManuel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editStatusButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'addHorizontalLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'addHorizontalLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'addButtonRow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'on_selectAll_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_validButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCheckIconOnGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<iconEleveGroup *, std::false_type>,
        // method 'on_SourceButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_delButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSessionData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_echapButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetSession'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_loadSession_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_CreationButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeNameTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'on_muteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_demuteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_desactiverSonButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_activerSonButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_creerGroupeButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_annulerButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_PlanButton_clicked(); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 2: _t->loadImagesFromDB(); break;
        case 3: { bool _r = _t->connectToDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->onImageGroupDoubleClicked(); break;
        case 5: _t->setupActivitiesComboBox(); break;
        case 6: _t->setupClassesComboBox(); break;
        case 7: _t->on_SessionButton_clicked(); break;
        case 8: _t->on_ChoixActivite_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_selectManuel_clicked(); break;
        case 10: _t->editStatusButton((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 11: _t->addHorizontalLayout((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[3]))); break;
        case 12: _t->addHorizontalLayout((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[4]))); break;
        case 13: _t->addButtonRow((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[4]))); break;
        case 14: _t->on_selectAll_clicked(); break;
        case 15: _t->on_validButton_clicked(); break;
        case 16: _t->showCheckIconOnGroup((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1]))); break;
        case 17: _t->on_SourceButton_clicked(); break;
        case 18: _t->on_delButton_clicked(); break;
        case 19: _t->saveSessionData((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 20: _t->on_echapButton_clicked(); break;
        case 21: _t->resetSession(); break;
        case 22: _t->on_loadSession_clicked(); break;
        case 23: _t->on_CreationButton_clicked(); break;
        case 24: _t->changeNameTable((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 25: _t->on_muteButton_clicked(); break;
        case 26: _t->on_demuteButton_clicked(); break;
        case 27: _t->on_desactiverSonButton_clicked(); break;
        case 28: _t->on_activerSonButton_clicked(); break;
        case 29: _t->on_creerGroupeButton_clicked(); break;
        case 30: _t->on_annulerButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            case 3:
            case 2:
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< iconEleveGroup* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
