QT       += core gui
QT		+= xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
msvc:QMAKE_CXXFLAGS += /utf-8
CONFIG += c++11
TARGET              = ConfigMaker
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = bin
win32:RC_FILE       = other/main.rc
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RESOURCES           += other/main.qrc
SOURCES += \
    dialogintroduction.cpp \
    globalfunc.cpp \
    main.cpp \
    modbusfrm.cpp \
    widget.cpp

HEADERS += \
    dialogintroduction.h \
    globalfunc.h \
    modbusfrm.h \
    widget.h

FORMS += \
    dialogintroduction.ui \
    modbusfrm.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
