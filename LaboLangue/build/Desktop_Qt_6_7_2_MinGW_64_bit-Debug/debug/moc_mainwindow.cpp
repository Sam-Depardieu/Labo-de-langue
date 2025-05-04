/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
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
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
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
        "majStatusQCM",
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
        "on_envoyerMessageGroupe_clicked",
        "on_modeClairButton_clicked",
        "on_modeSombreButton_clicked",
        "on_StatutButton_clicked",
        "on_cacheButton_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_PlanButton_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadImagesFromDB'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'connectToDatabase'
        QtMocHelpers::SlotData<bool()>(4, 2, QMC::AccessPrivate, QMetaType::Bool),
        // Slot 'onImageGroupDoubleClicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'editStatusButton'
        QtMocHelpers::SlotData<void(QPushButton *, bool)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::Bool, 9 },
        }}),
        // Slot 'addHorizontalLayout'
        QtMocHelpers::SlotData<void(QVBoxLayout *, std::initializer_list<QWidget*>)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 13, 14 },
        }}),
        // Slot 'showCheckIconOnGroup'
        QtMocHelpers::SlotData<void(iconEleveGroup *)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'majStatusQCM'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_SessionButton_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ChoixActivite_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 21 },
        }}),
        // Slot 'on_loadSession_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_CreationButton_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_selectAll_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_selectManuel_clicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_validButton_clicked'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_SourceButton_clicked'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_delButton_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_echapButton_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'resetSession'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setupActivitiesComboBox'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setupClassesComboBox'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveSessionData'
        QtMocHelpers::SlotData<void(bool)>(33, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'on_muteButton_clicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_demuteButton_clicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_desactiverSonButton_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_activerSonButton_clicked'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_creerGroupeButton_clicked'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_annulerButton_clicked'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Communication_clicked'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_nomEleveLineEdit_editingFinished'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'changeNameTable'
        QtMocHelpers::SlotData<void(QTableWidgetItem *)>(43, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 44, 45 },
        }}),
        // Slot 'changeNameGroup'
        QtMocHelpers::SlotData<void(iconEleveGroup *, QString)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 16, 17 }, { QMetaType::QString, 47 },
        }}),
        // Slot 'loadInformationTable'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_envoyerMessagePersonne_clicked'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_envoyerMessageGroupe_clicked'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_modeClairButton_clicked'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_modeSombreButton_clicked'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_StatutButton_clicked'
        QtMocHelpers::SlotData<void()>(53, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_cacheButton_clicked'
        QtMocHelpers::SlotData<void()>(54, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_PlanButton_clicked(); break;
        case 1: _t->loadImagesFromDB(); break;
        case 2: { bool _r = _t->connectToDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->onImageGroupDoubleClicked(); break;
        case 4: _t->editStatusButton((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 5: _t->addHorizontalLayout((*reinterpret_cast< std::add_pointer_t<QVBoxLayout*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::initializer_list<QWidget*>>>(_a[2]))); break;
        case 6: _t->showCheckIconOnGroup((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1]))); break;
        case 7: _t->majStatusQCM(); break;
        case 8: _t->on_SessionButton_clicked(); break;
        case 9: _t->on_ChoixActivite_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_loadSession_clicked(); break;
        case 11: _t->on_CreationButton_clicked(); break;
        case 12: _t->on_selectAll_clicked(); break;
        case 13: _t->on_selectManuel_clicked(); break;
        case 14: _t->on_validButton_clicked(); break;
        case 15: _t->on_SourceButton_clicked(); break;
        case 16: _t->on_delButton_clicked(); break;
        case 17: _t->on_echapButton_clicked(); break;
        case 18: _t->resetSession(); break;
        case 19: _t->setupActivitiesComboBox(); break;
        case 20: _t->setupClassesComboBox(); break;
        case 21: _t->saveSessionData((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->on_muteButton_clicked(); break;
        case 23: _t->on_demuteButton_clicked(); break;
        case 24: _t->on_desactiverSonButton_clicked(); break;
        case 25: _t->on_activerSonButton_clicked(); break;
        case 26: _t->on_creerGroupeButton_clicked(); break;
        case 27: _t->on_annulerButton_clicked(); break;
        case 28: _t->on_Communication_clicked(); break;
        case 29: _t->on_nomEleveLineEdit_editingFinished(); break;
        case 30: _t->changeNameTable((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 31: _t->changeNameGroup((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 32: _t->loadInformationTable(); break;
        case 33: _t->on_envoyerMessagePersonne_clicked(); break;
        case 34: _t->on_envoyerMessageGroupe_clicked(); break;
        case 35: _t->on_modeClairButton_clicked(); break;
        case 36: _t->on_modeSombreButton_clicked(); break;
        case 37: _t->on_StatutButton_clicked(); break;
        case 38: _t->on_cacheButton_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
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
        case 31:
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
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}
QT_WARNING_POP
