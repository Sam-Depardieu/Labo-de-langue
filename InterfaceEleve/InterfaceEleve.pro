QT       += core gui multimedia multimediawidgets
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
CONFIG -= windows
QT += core


TEMPLATE = app

# Sources
SOURCES += \
    attenteprof.cpp \
    interfaceaudio.cpp \
    interfaceenregistrement.cpp \
    interfaceqcm.cpp \
    interfacevideo.cpp \
    main.cpp \
    mainwindow.cpp

# Headers
HEADERS += \
    attenteprof.h \
    interfaceaudio.h \
    interfaceenregistrement.h \
    interfaceqcm.h \
    interfacevideo.h \
    mainwindow.h

# Forms
FORMS += \
    attenteprof.ui \
    interfaceaudio.ui \
    interfaceenregistrement.ui \
    interfaceqcm.ui \
    interfacevideo.ui \
    mainwindow.ui

# Resources
RESOURCES += \
    images.qrc \
    videos.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
