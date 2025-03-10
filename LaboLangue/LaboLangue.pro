QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql
QT += websockets
QT += multimedia

CONFIG += c++17
QT += core network
CONFIG += console
CONFIG -= app_bundle
TARGET = LaboLangue
TEMPLATE = app

INCLUDEPATH += mingw64/include
LIBS += -L mingw64/lib -l zmq


INCLUDEPATH += cppzmq\include


QT += multimedia multimediawidgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AudioCommunicator.cpp \
    customgraphicsitemgroup.cpp \
    main.cpp \
    mainwindow.cpp \
    qcm.cpp
    src/zmp.cpp

HEADERS += \
    AudioCommunicator.h \
    customgraphicsitemgroup.h \
    mainwindow.h \
    qcm.h

FORMS += \
    mainwindow.ui \
    qcm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
