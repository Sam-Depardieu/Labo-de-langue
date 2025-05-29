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
        "on_SessionButton_clicked",
        "",
        "on_CreationButton_clicked",
        "on_StatutButton_clicked",
        "on_loadSession_clicked",
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
        "on_pauseButton_clicked",
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
        "loadInformationTable",
        "on_redemarrerButton_clicked",
        "on_AideButton_clicked",
        "on_cadenaCloseButton_clicked",
        "on_cadenaOpenButton_clicked",
        "errorBdd",
        "QSqlQuery&",
        "query",
        "listeCouleursDisponibles",
        "QList<QColor>",
        "couleurDisponible",
        "on_reloadButton_clicked",
        "on_LectureStatutButton_clicked",
        "on_PauseStatutButton_clicked",
        "on_lectureButton_clicked",
        "on_ajouterTemps_clicked",
        "on_enleveTemps_clicked",
        "on_AppelerButton_clicked",
        "on_AppelButton_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_SessionButton_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_CreationButton_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_StatutButton_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_loadSession_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveSessionData'
        QtMocHelpers::SlotData<void(bool)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'resetSession'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setupActivitiesComboBox'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setupClassesComboBox'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ChoixActivite_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'on_selectAll_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_selectManuel_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_validButton_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_SourceButton_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_delButton_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_echapButton_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_casqueSonButton_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_microSonButton_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Communication_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_envoyerMessagePersonne_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_envoyerMessageGroupe_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_creerGroupeButton_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_nomGroupeLineEdit_returnPressed'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_nomEleveLineEdit_editingFinished'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pauseButton_clicked'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onClicked_itemBoutonAjouterGroupe'
        QtMocHelpers::SlotData<void(iconEleveGroup *)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 29, 30 },
        }}),
        // Slot 'on_modeClairButton_clicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_modeSombreButton_clicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_cacheButton_clicked'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'majStatusQCM'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'changeNameTable'
        QtMocHelpers::SlotData<void(QTableWidgetItem *)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 36, 37 },
        }}),
        // Slot 'loadInformationTable'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_redemarrerButton_clicked'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_AideButton_clicked'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_cadenaCloseButton_clicked'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_cadenaOpenButton_clicked'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'errorBdd'
        QtMocHelpers::SlotData<bool(QSqlQuery &)>(43, 2, QMC::AccessPrivate, QMetaType::Bool, {{
            { 0x80000000 | 44, 45 },
        }}),
        // Slot 'listeCouleursDisponibles'
        QtMocHelpers::SlotData<QList<QColor>()>(46, 2, QMC::AccessPrivate, 0x80000000 | 47),
        // Slot 'couleurDisponible'
        QtMocHelpers::SlotData<QColor()>(48, 2, QMC::AccessPrivate, QMetaType::QColor),
        // Slot 'on_reloadButton_clicked'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_LectureStatutButton_clicked'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PauseStatutButton_clicked'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_lectureButton_clicked'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_ajouterTemps_clicked'
        QtMocHelpers::SlotData<void()>(53, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_enleveTemps_clicked'
        QtMocHelpers::SlotData<void()>(54, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_AppelerButton_clicked'
        QtMocHelpers::SlotData<void()>(55, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_AppelButton_clicked'
        QtMocHelpers::SlotData<void()>(56, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 0: _t->on_SessionButton_clicked(); break;
        case 1: _t->on_CreationButton_clicked(); break;
        case 2: _t->on_StatutButton_clicked(); break;
        case 3: _t->on_loadSession_clicked(); break;
        case 4: _t->saveSessionData((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->resetSession(); break;
        case 6: _t->setupActivitiesComboBox(); break;
        case 7: _t->setupClassesComboBox(); break;
        case 8: _t->on_ChoixActivite_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_selectAll_clicked(); break;
        case 10: _t->on_selectManuel_clicked(); break;
        case 11: _t->on_validButton_clicked(); break;
        case 12: _t->on_SourceButton_clicked(); break;
        case 13: _t->on_delButton_clicked(); break;
        case 14: _t->on_echapButton_clicked(); break;
        case 15: _t->on_casqueSonButton_clicked(); break;
        case 16: _t->on_microSonButton_clicked(); break;
        case 17: _t->on_Communication_clicked(); break;
        case 18: _t->on_envoyerMessagePersonne_clicked(); break;
        case 19: _t->on_envoyerMessageGroupe_clicked(); break;
        case 20: _t->on_creerGroupeButton_clicked(); break;
        case 21: _t->on_nomGroupeLineEdit_returnPressed(); break;
        case 22: _t->on_nomEleveLineEdit_editingFinished(); break;
        case 23: _t->on_pauseButton_clicked(); break;
        case 24: _t->onClicked_itemBoutonAjouterGroupe((*reinterpret_cast< std::add_pointer_t<iconEleveGroup*>>(_a[1]))); break;
        case 25: _t->on_modeClairButton_clicked(); break;
        case 26: _t->on_modeSombreButton_clicked(); break;
        case 27: _t->on_cacheButton_clicked(); break;
        case 28: _t->majStatusQCM(); break;
        case 29: _t->changeNameTable((*reinterpret_cast< std::add_pointer_t<QTableWidgetItem*>>(_a[1]))); break;
        case 30: _t->loadInformationTable(); break;
        case 31: _t->on_redemarrerButton_clicked(); break;
        case 32: _t->on_AideButton_clicked(); break;
        case 33: _t->on_cadenaCloseButton_clicked(); break;
        case 34: _t->on_cadenaOpenButton_clicked(); break;
        case 35: { bool _r = _t->errorBdd((*reinterpret_cast< std::add_pointer_t<QSqlQuery&>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { QList<QColor> _r = _t->listeCouleursDisponibles();
            if (_a[0]) *reinterpret_cast< QList<QColor>*>(_a[0]) = std::move(_r); }  break;
        case 37: { QColor _r = _t->couleurDisponible();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->on_reloadButton_clicked(); break;
        case 39: _t->on_LectureStatutButton_clicked(); break;
        case 40: _t->on_PauseStatutButton_clicked(); break;
        case 41: _t->on_lectureButton_clicked(); break;
        case 42: _t->on_ajouterTemps_clicked(); break;
        case 43: _t->on_enleveTemps_clicked(); break;
        case 44: _t->on_AppelerButton_clicked(); break;
        case 45: _t->on_AppelButton_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 24:
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
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    }
    return _id;
}
QT_WARNING_POP
