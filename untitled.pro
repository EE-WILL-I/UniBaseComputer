QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
 RC_FILE = resources.rc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arithmeticalmodule.cpp \
    controller.cpp \
    convertationmodule.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
    arithmeticalmodule.h \
    controller.h \
    convertationmodule.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    release/Qt5Core.dll \
    release/Qt5Gui.dll \
    release/Qt5Widgets.dll \
    release/UniBase Computer.exe \
    release/UniBaseComputer_linux \
    release/UniBaseComputer_v3.exe \
    release/libgcc_s_seh-1.dll \
    release/libstdc++-6.dll \
    release/libwinpthread-1.dll \
    release/plugins/platforms/libEGL.dll \
    release/plugins/platforms/qdirect2d.dll \
    release/plugins/platforms/qminimal.dll \
    release/plugins/platforms/qoffscreen.dll \
    release/plugins/platforms/qwindows.dll \
    release/qoffscreen.dll \
    release/qt.conf \
    resources.rc
