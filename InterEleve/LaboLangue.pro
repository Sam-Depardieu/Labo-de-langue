QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attenteprof.cpp \
    interfaceaudioco.cpp \
    interfaceenregistrement.cpp \
    interfaceqcm.cpp \
    main.cpp \
    mainwindow.cpp \
    volumecontroldialog.cpp

HEADERS += \
    attenteprof.h \
    interfaceaudioco.h \
    interfaceenregistrement.h \
    interfaceqcm.h \
    mainwindow.h \
    volumecontroldialog.h

FORMS += \
    attenteprof.ui \
    interfaceaudioco.ui \
    interfaceenregistrement.ui \
    interfaceqcm.ui \
    mainwindow.ui \
    volumecontroldialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Video/loading.gif

RESOURCES += \
    Image.qrc
