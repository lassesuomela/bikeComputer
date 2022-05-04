QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    images/locationArrow.png \
    images/satellite.png

RESOURCES += \
    Resources.qrc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../serialPortReader/release/ -lserialMonitor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../serialPortReader/debug/ -lserialMonitor
else:unix:!macx: LIBS += -L$$PWD/../serialPortReader/ -lserialMonitor

INCLUDEPATH += $$PWD/../serialPortReader
DEPENDPATH += $$PWD/../serialPortReader
