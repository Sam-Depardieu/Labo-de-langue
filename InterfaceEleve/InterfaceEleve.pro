QT += core gui sql multimedia widgets network multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += debug_and_release
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= windows
QT += websockets

TEMPLATE = app

#INCLUDEPATH += cppzmq\include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audioCommunicator.cpp \
    avancementqcm.cpp \
    interfaceaudio.cpp \
    interfaceenregistrement.cpp \
    interfaceqcm.cpp \
    interfacevideo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    audioCommunicator.h \
    avancementqcm.h \
    interfaceaudio.h \
    interfaceenregistrement.h \
    interfaceqcm.h \
    interfacevideo.h \
    mainwindow.h

FORMS += \
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
