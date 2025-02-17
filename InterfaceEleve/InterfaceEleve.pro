QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql
CONFIG += c++17
QT += core network
CONFIG += console
CONFIG -= app_bundle
CONFIG += console
CONFIG -= windows
TEMPLATE = app



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attenteprof.cpp \
    interfaceaudio.cpp \
    interfaceenregistrement.cpp \
    interfaceqcm.cpp \
    interfacevideo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    attenteprof.h \
    interfaceaudio.h \
    interfaceenregistrement.h \
    interfaceqcm.h \
    interfacevideo.h \
    mainwindow.h

FORMS += \
    attenteprof.ui \
    interfaceaudio.ui \
    interfaceenregistrement.ui \
    interfaceqcm.ui \
    interfacevideo.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    videos.qrc
