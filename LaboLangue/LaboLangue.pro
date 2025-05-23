QT       += core gui websockets core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
TARGET = LaboLangue
TEMPLATE = app

QT += multimedia multimediawidgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AudioCommunicator.cpp \
    choixsession.cpp \
    gestionSession.cpp \
    helpwindow.cpp \
    iconEleveGroup.cpp \
    main.cpp \
    mainwindow.cpp \
    qcm.cpp

HEADERS += \
    AudioCommunicator.h \
    choixsession.h \
    gestionSession.h \
    helpwindow.h \
    iconEleveGroup.h \
    mainwindow.h \
    qcm.h

FORMS += \
    choixsession.ui \
    helpwindow.ui \
    mainwindow.ui \
    qcm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/ressource.qrc
