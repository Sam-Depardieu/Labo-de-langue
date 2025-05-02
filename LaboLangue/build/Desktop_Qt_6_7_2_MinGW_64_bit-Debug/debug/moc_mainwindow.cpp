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
    "loadImagesFromDB",
    "connectToDatabase",
    "onImageGroupDoubleClicked",
    "editStatusButton",
    "QPushButton*",
    "button",
    "status",
    "addHorizontalLayout",
    "QVBoxLayout*",
    "layout",
    "std::initializer_list<QWidget*>",
    "widgets",
    "showCheckIconOnGroup",
    "iconEleveGroup*",
    "group",
    "on_SessionButton_clicked",
    "on_ChoixActivite_currentIndexChanged",
    "index",
    "on_loadSession_clicked",
    "on_CreationButton_clicked",
    "on_selectAll_clicked",
    "on_selectManuel_clicked",
    "on_validButton_clicked",
    "on_SourceButton_clicked",
    "on_delButton_clicked",
    "on_echapButton_clicked",
    "resetSession",
    "setupActivitiesComboBox",
    "setupClassesComboBox",
    "saveSessionData",
    "isNewSession",
    "on_muteButton_clicked",
    "on_demuteButton_clicked",
    "on_desactiverSonButton_clicked",
    "on_activerSonButton_clicked",
    "on_creerGroupeButton_clicked",
    "on_annulerButton_clicked",
    "on_Communication_clicked",
    "on_nomEleveLineEdit_editingFinished",
    "changeNameTable",
    "QTableWidgetItem*",
    "item",
    "changeNameGroup",
    "newName",
    "loadInformationTable",
    "on_envoyerMessagePersonne_clicked",
    "on_envoyerMessageGroupe_clicked"
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
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  218,    2, 0x08,    1 /* Private */,
       3,    0,  219,    2, 0x08,    2 /* Private */,
       4,    0,  220,    2, 0x08,    3 /* Private */,
       5,    0,  221,    2, 0x08,    4 /* Private */,
       6,    2,  222,    2, 0x08,    5 /* Private */,
      10,    2,  227,    2, 0x08,    8 /* Private */,
      15,    1,  232,    2, 0x08,   11 /* Private */,
      18,    0,  235,    2, 0x08,   13 /* Private */,
      19,    1,  236,    2, 0x08,   14 /* Private */,
      21,    0,  239,    2, 0x08,   16 /* Private */,
      22,    0,  240,    2, 0x08,   17 /* Private */,
      23,    0,  241,    2, 0x08,   18 /* Private */,
      24,    0,  242,    2, 0x08,   19 /* Private */,
      25,    0,  243,    2, 0x08,   20 /* Private */,
      26,    0,  244,    2, 0x08,   21 /* Private */,
      27,    0,  245,    2, 0x08,   22 /* Private */,
      28,    0,  246,    2, 0x08,   23 /* Private */,
      29,    0,  247,    2, 0x08,   24 /* Private */,
      30,    0,  248,    2, 0x08,   25 /* Private */,
      31,    0,  249,    2, 0x08,   26 /* Private */,
      32,    1,  250,    2, 0x08,   27 /* Private */,
      34,    0,  253,    2, 0x08,   29 /* Private */,
      35,    0,  254,    2, 0x08,   30 /* Private */,
      36,    0,  255,    2, 0x08,   31 /* Private */,
      37,    0,  256,    2, 0x08,   32 /* Private */,
      38,    0,  257,    2, 0x08,   33 /* Private */,
      39,    0,  258,    2, 0x08,   34 /* Private */,
      40,    0,  259,    2, 0x08,   35 /* Private */,
      41,    0,  260,    2, 0x08,   36 /* Private */,
      42,    1,  261,    2, 0x08,   37 /* Private */,
      45,    2,  264,    2, 0x08,   39 /* Private */,
      47,    0,  269,    2, 0x08,   42 /* Private */,
      48,    0,  270,    2, 0x08,   43 /* Private */,
      49,    0,  271,    2, 0x08,   44 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    8,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
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
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, 0x80000000 | 16, QMetaType::QString,   17,   46,
    QMetaType::Void,
    QMetaType::Void,
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
        // method 'loadImagesFromDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectToDatabase'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onImageGroupDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editStatusButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'addHorizontalLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVBoxLayout *, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::initializer_list<QWidget*>, std::false_type>,
        // method 'showCheckIconOnGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<iconEleveGroup *, std::false_type>,
        // method 'on_SessionButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ChoixActivite_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_loadSession_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_CreationButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        // method 'resetSession'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupActivitiesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupClassesComboBox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSessionData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
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
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Communication_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_nomEleveLineEdit_editingFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeNameTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTableWidgetItem *, std::false_type>,
        // method 'changeNameGroup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<iconEleveGroup *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'loadInformationTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_envoyerMessagePersonne_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_envoyerMessageGroupe_clicked'
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
        case 1: _t->loadImagesFromDB(); break;
        case 2: { bool _r = _t->connectToDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->onImageGroupDoubleClicked(); break;
        case 4: _t->editStatusButton((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 5: _t->addHorizontalLayout((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::initializer_list<QWidget*>>>(_a[2]))); break;
        case 6: _t->showCheckIconOnGroup((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1]))); break;
        case 7: _t->on_SessionButton_clicked(); break;
        case 8: _t->on_ChoixActivite_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_loadSession_clicked(); break;
        case 10: _t->on_CreationButton_clicked(); break;
        case 11: _t->on_selectAll_clicked(); break;
        case 12: _t->on_selectManuel_clicked(); break;
        case 13: _t->on_validButton_clicked(); break;
        case 14: _t->on_SourceButton_clicked(); break;
        case 15: _t->on_delButton_clicked(); break;
        case 16: _t->on_echapButton_clicked(); break;
        case 17: _t->resetSession(); break;
        case 18: _t->setupActivitiesComboBox(); break;
        case 19: _t->setupClassesComboBox(); break;
        case 20: _t->saveSessionData((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->on_muteButton_clicked(); break;
        case 22: _t->on_demuteButton_clicked(); break;
        case 23: _t->on_desactiverSonButton_clicked(); break;
        case 24: _t->on_activerSonButton_clicked(); break;
        case 25: _t->on_creerGroupeButton_clicked(); break;
        case 26: _t->on_annulerButton_clicked(); break;
        case 27: _t->on_Communication_clicked(); break;
        case 28: _t->on_nomEleveLineEdit_editingFinished(); break;
        case 29: _t->changeNameTable((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 30: _t->changeNameGroup((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 31: _t->loadInformationTable(); break;
        case 32: _t->on_envoyerMessagePersonne_clicked(); break;
        case 33: _t->on_envoyerMessageGroupe_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QPushButton* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVBoxLayout* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< iconEleveGroup* >(); break;
            }
            break;
        case 30:
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
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}
QT_WARNING_POP
