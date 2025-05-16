QT       += core gui websockets core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
TARGET = LaboLangue
TEMPLATE = app

INCLUDEPATH += $$PWD/zmq/include
LIBS += -L$$PWD/zmq/ -lzmq  # MSVC

QT += multimedia multimediawidgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AudioCommunicator.cpp \
    choixsession.cpp \
    helpwindow.cpp \
    iconEleveGroup.cpp \
    main.cpp \
    mainwindow.cpp \
    qcm.cpp

HEADERS += \
    AudioCommunicator.h \
    choixsession.h \
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

DISTFILES += \
    build/img/check.png \
    build/img/clair.png \
    build/img/cross-qcm.png \
    build/img/cross.png \
    build/img/earGreen.png \
    build/img/earRed.png \
    build/img/micro.png \
    build/img/mute.png \
    build/img/person.png \
    build/img/sombre.png

RESOURCES += \
    ressources/ressource.qrc
