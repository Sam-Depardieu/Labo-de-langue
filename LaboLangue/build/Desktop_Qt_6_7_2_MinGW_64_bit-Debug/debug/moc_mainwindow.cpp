/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
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
    "loadInformationTable"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  224,    2, 0x08,    1 /* Private */,
       3,    0,  225,    2, 0x08,    2 /* Private */,
       4,    0,  226,    2, 0x08,    3 /* Private */,
       5,    0,  227,    2, 0x08,    4 /* Private */,
       6,    0,  228,    2, 0x08,    5 /* Private */,
       7,    0,  229,    2, 0x08,    6 /* Private */,
       8,    1,  230,    2, 0x08,    7 /* Private */,
      10,    0,  233,    2, 0x08,    9 /* Private */,
      11,    0,  234,    2, 0x08,   10 /* Private */,
      12,    0,  235,    2, 0x08,   11 /* Private */,
      13,    1,  236,    2, 0x08,   12 /* Private */,
      15,    0,  239,    2, 0x08,   14 /* Private */,
      16,    0,  240,    2, 0x08,   15 /* Private */,
      17,    0,  241,    2, 0x08,   16 /* Private */,
      18,    0,  242,    2, 0x08,   17 /* Private */,
      19,    0,  243,    2, 0x08,   18 /* Private */,
      20,    0,  244,    2, 0x08,   19 /* Private */,
      21,    0,  245,    2, 0x08,   20 /* Private */,
      22,    0,  246,    2, 0x08,   21 /* Private */,
      23,    0,  247,    2, 0x08,   22 /* Private */,
      24,    0,  248,    2, 0x08,   23 /* Private */,
      25,    0,  249,    2, 0x08,   24 /* Private */,
      26,    0,  250,    2, 0x08,   25 /* Private */,
      27,    0,  251,    2, 0x08,   26 /* Private */,
      28,    0,  252,    2, 0x08,   27 /* Private */,
      29,    0,  253,    2, 0x08,   28 /* Private */,
      30,    1,  254,    2, 0x08,   29 /* Private */,
      33,    0,  257,    2, 0x08,   31 /* Private */,
      34,    0,  258,    2, 0x08,   32 /* Private */,
      35,    0,  259,    2, 0x08,   33 /* Private */,
      36,    0,  260,    2, 0x08,   34 /* Private */,
      37,    1,  261,    2, 0x08,   35 /* Private */,
      40,    2,  264,    2, 0x08,   37 /* Private */,
      42,    2,  269,    2, 0x08,   40 /* Private */,
      45,    0,  274,    2, 0x08,   43 /* Private */,

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

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
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
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}
QT_WARNING_POP
