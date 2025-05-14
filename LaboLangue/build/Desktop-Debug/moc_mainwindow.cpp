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
    uint offsetsAndSizes[96];
    char stringdata0[11];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[26];
    char stringdata5[24];
    char stringdata6[23];
    char stringdata7[12];
    char stringdata8[16];
    char stringdata9[13];
    char stringdata10[13];
    char stringdata11[24];
    char stringdata12[21];
    char stringdata13[37];
    char stringdata14[6];
    char stringdata15[21];
    char stringdata16[24];
    char stringdata17[23];
    char stringdata18[24];
    char stringdata19[21];
    char stringdata20[23];
    char stringdata21[27];
    char stringdata22[26];
    char stringdata23[25];
    char stringdata24[34];
    char stringdata25[32];
    char stringdata26[29];
    char stringdata27[35];
    char stringdata28[36];
    char stringdata29[25];
    char stringdata30[34];
    char stringdata31[16];
    char stringdata32[6];
    char stringdata33[27];
    char stringdata34[28];
    char stringdata35[23];
    char stringdata36[13];
    char stringdata37[16];
    char stringdata38[18];
    char stringdata39[5];
    char stringdata40[15];
    char stringdata41[8];
    char stringdata42[17];
    char stringdata43[8];
    char stringdata44[11];
    char stringdata45[21];
    char stringdata46[28];
    char stringdata47[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 21),  // "on_PlanButton_clicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 24),  // "on_SessionButton_clicked"
        QT_MOC_LITERAL(59, 25),  // "on_CreationButton_clicked"
        QT_MOC_LITERAL(85, 23),  // "on_StatutButton_clicked"
        QT_MOC_LITERAL(109, 22),  // "on_loadSession_clicked"
        QT_MOC_LITERAL(132, 11),  // "loadSession"
        QT_MOC_LITERAL(144, 15),  // "saveSessionData"
        QT_MOC_LITERAL(160, 12),  // "isNewSession"
        QT_MOC_LITERAL(173, 12),  // "resetSession"
        QT_MOC_LITERAL(186, 23),  // "setupActivitiesComboBox"
        QT_MOC_LITERAL(210, 20),  // "setupClassesComboBox"
        QT_MOC_LITERAL(231, 36),  // "on_ChoixActivite_currentIndex..."
        QT_MOC_LITERAL(268, 5),  // "index"
        QT_MOC_LITERAL(274, 20),  // "on_selectAll_clicked"
        QT_MOC_LITERAL(295, 23),  // "on_selectManuel_clicked"
        QT_MOC_LITERAL(319, 22),  // "on_validButton_clicked"
        QT_MOC_LITERAL(342, 23),  // "on_SourceButton_clicked"
        QT_MOC_LITERAL(366, 20),  // "on_delButton_clicked"
        QT_MOC_LITERAL(387, 22),  // "on_echapButton_clicked"
        QT_MOC_LITERAL(410, 26),  // "on_casqueSonButton_clicked"
        QT_MOC_LITERAL(437, 25),  // "on_microSonButton_clicked"
        QT_MOC_LITERAL(463, 24),  // "on_Communication_clicked"
        QT_MOC_LITERAL(488, 33),  // "on_envoyerMessagePersonne_cli..."
        QT_MOC_LITERAL(522, 31),  // "on_envoyerMessageGroupe_clicked"
        QT_MOC_LITERAL(554, 28),  // "on_creerGroupeButton_clicked"
        QT_MOC_LITERAL(583, 34),  // "on_nomGroupeLineEdit_returnPr..."
        QT_MOC_LITERAL(618, 35),  // "on_nomEleveLineEdit_editingFi..."
        QT_MOC_LITERAL(654, 24),  // "on_annulerButton_clicked"
        QT_MOC_LITERAL(679, 33),  // "onClicked_itemBoutonAjouterGr..."
        QT_MOC_LITERAL(713, 15),  // "iconEleveGroup*"
        QT_MOC_LITERAL(729, 5),  // "eleve"
        QT_MOC_LITERAL(735, 26),  // "on_modeClairButton_clicked"
        QT_MOC_LITERAL(762, 27),  // "on_modeSombreButton_clicked"
        QT_MOC_LITERAL(790, 22),  // "on_cacheButton_clicked"
        QT_MOC_LITERAL(813, 12),  // "majStatusQCM"
        QT_MOC_LITERAL(826, 15),  // "changeNameTable"
        QT_MOC_LITERAL(842, 17),  // "QTableWidgetItem*"
        QT_MOC_LITERAL(860, 4),  // "item"
        QT_MOC_LITERAL(865, 14),  // "updateEleveNom"
        QT_MOC_LITERAL(880, 7),  // "newName"
        QT_MOC_LITERAL(888, 16),  // "updateNomDansBDD"
        QT_MOC_LITERAL(905, 7),  // "idEleve"
        QT_MOC_LITERAL(913, 10),  // "nouveauNom"
        QT_MOC_LITERAL(924, 20),  // "loadInformationTable"
        QT_MOC_LITERAL(945, 27),  // "on_redemarrerButton_clicked"
        QT_MOC_LITERAL(973, 21)   // "on_AideButton_clicked"
    },
    "MainWindow",
    "on_PlanButton_clicked",
    "",
    "on_SessionButton_clicked",
    "on_CreationButton_clicked",
    "on_StatutButton_clicked",
    "on_loadSession_clicked",
    "loadSession",
    "saveSessionData",
    "isNewSession",
    "resetSession",
    "setupActivitiesComboBox",
    "setupClassesComboBox",
    "on_ChoixActivite_currentIndexChanged",
    "index",
    "on_selectAll_clicked",
    "on_selectManuel_clicked",
    "on_validButton_clicked",
    "on_SourceButton_clicked",
    "on_delButton_clicked",
    "on_echapButton_clicked",
    "on_casqueSonButton_clicked",
    "on_microSonButton_clicked",
    "on_Communication_clicked",
    "on_envoyerMessagePersonne_clicked",
    "on_envoyerMessageGroupe_clicked",
    "on_creerGroupeButton_clicked",
    "on_nomGroupeLineEdit_returnPressed",
    "on_nomEleveLineEdit_editingFinished",
    "on_annulerButton_clicked",
    "onClicked_itemBoutonAjouterGroupe",
    "iconEleveGroup*",
    "eleve",
    "on_modeClairButton_clicked",
    "on_modeSombreButton_clicked",
    "on_cacheButton_clicked",
    "majStatusQCM",
    "changeNameTable",
    "QTableWidgetItem*",
    "item",
    "updateEleveNom",
    "newName",
    "updateNomDansBDD",
    "idEleve",
    "nouveauNom",
    "loadInformationTable",
    "on_redemarrerButton_clicked",
    "on_AideButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  236,    2, 0x08,    1 /* Private */,
       3,    0,  237,    2, 0x08,    2 /* Private */,
       4,    0,  238,    2, 0x08,    3 /* Private */,
       5,    0,  239,    2, 0x08,    4 /* Private */,
       6,    0,  240,    2, 0x08,    5 /* Private */,
       7,    0,  241,    2, 0x08,    6 /* Private */,
       8,    1,  242,    2, 0x08,    7 /* Private */,
      10,    0,  245,    2, 0x08,    9 /* Private */,
      11,    0,  246,    2, 0x08,   10 /* Private */,
      12,    0,  247,    2, 0x08,   11 /* Private */,
      13,    1,  248,    2, 0x08,   12 /* Private */,
      15,    0,  251,    2, 0x08,   14 /* Private */,
      16,    0,  252,    2, 0x08,   15 /* Private */,
      17,    0,  253,    2, 0x08,   16 /* Private */,
      18,    0,  254,    2, 0x08,   17 /* Private */,
      19,    0,  255,    2, 0x08,   18 /* Private */,
      20,    0,  256,    2, 0x08,   19 /* Private */,
      21,    0,  257,    2, 0x08,   20 /* Private */,
      22,    0,  258,    2, 0x08,   21 /* Private */,
      23,    0,  259,    2, 0x08,   22 /* Private */,
      24,    0,  260,    2, 0x08,   23 /* Private */,
      25,    0,  261,    2, 0x08,   24 /* Private */,
      26,    0,  262,    2, 0x08,   25 /* Private */,
      27,    0,  263,    2, 0x08,   26 /* Private */,
      28,    0,  264,    2, 0x08,   27 /* Private */,
      29,    0,  265,    2, 0x08,   28 /* Private */,
      30,    1,  266,    2, 0x08,   29 /* Private */,
      33,    0,  269,    2, 0x08,   31 /* Private */,
      34,    0,  270,    2, 0x08,   32 /* Private */,
      35,    0,  271,    2, 0x08,   33 /* Private */,
      36,    0,  272,    2, 0x08,   34 /* Private */,
      37,    1,  273,    2, 0x08,   35 /* Private */,
      40,    2,  276,    2, 0x08,   37 /* Private */,
      42,    2,  281,    2, 0x08,   40 /* Private */,
      45,    0,  286,    2, 0x08,   43 /* Private */,
      46,    0,  287,    2, 0x08,   44 /* Private */,
      47,    0,  288,    2, 0x08,   45 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void, 0x80000000 | 31, QMetaType::QString,   32,   41,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   43,   44,
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
        // method 'on_SessionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_CreationButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_StatutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_loadSession_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadSession'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSessionData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'resetSession'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupActivitiesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupClassesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ChoixActivite_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_selectAll_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_selectManuel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_validButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_SourceButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_delButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_echapButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_casqueSonButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_microSonButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Communication_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_envoyerMessagePersonne_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_envoyerMessageGroupe_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_creerGroupeButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_nomGroupeLineEdit_returnPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_nomEleveLineEdit_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_annulerButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClicked_itemBoutonAjouterGroupe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<iconEleveGroup *, std::false_type>,
        // method 'on_modeClairButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_modeSombreButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cacheButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'majStatusQCM'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeNameTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'updateEleveNom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<iconEleveGroup *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateNomDansBDD'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'loadInformationTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_redemarrerButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_AideButton_clicked'
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
        case 1: _t->on_SessionButton_clicked(); break;
        case 2: _t->on_CreationButton_clicked(); break;
        case 3: _t->on_StatutButton_clicked(); break;
        case 4: _t->on_loadSession_clicked(); break;
        case 5: _t->loadSession(); break;
        case 6: _t->saveSessionData((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->resetSession(); break;
        case 8: _t->setupActivitiesComboBox(); break;
        case 9: _t->setupClassesComboBox(); break;
        case 10: _t->on_ChoixActivite_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_selectAll_clicked(); break;
        case 12: _t->on_selectManuel_clicked(); break;
        case 13: _t->on_validButton_clicked(); break;
        case 14: _t->on_SourceButton_clicked(); break;
        case 15: _t->on_delButton_clicked(); break;
        case 16: _t->on_echapButton_clicked(); break;
        case 17: _t->on_casqueSonButton_clicked(); break;
        case 18: _t->on_microSonButton_clicked(); break;
        case 19: _t->on_Communication_clicked(); break;
        case 20: _t->on_envoyerMessagePersonne_clicked(); break;
        case 21: _t->on_envoyerMessageGroupe_clicked(); break;
        case 22: _t->on_creerGroupeButton_clicked(); break;
        case 23: _t->on_nomGroupeLineEdit_returnPressed(); break;
        case 24: _t->on_nomEleveLineEdit_editingFinished(); break;
        case 25: _t->on_annulerButton_clicked(); break;
        case 26: _t->onClicked_itemBoutonAjouterGroupe((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1]))); break;
        case 27: _t->on_modeClairButton_clicked(); break;
        case 28: _t->on_modeSombreButton_clicked(); break;
        case 29: _t->on_cacheButton_clicked(); break;
        case 30: _t->majStatusQCM(); break;
        case 31: _t->changeNameTable((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 32: _t->updateEleveNom((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 33: _t->updateNomDansBDD((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 34: _t->loadInformationTable(); break;
        case 35: _t->on_redemarrerButton_clicked(); break;
        case 36: _t->on_AideButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< iconEleveGroup* >(); break;
            }
            break;
        case 32:
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
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
