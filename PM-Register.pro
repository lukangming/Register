QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(common/common.pri)
include(Keygen/Keygen.pri)
include(qaesencryption/qaesencryption.pri)
include(serialSet/serialSet.pri)
include(usrMgt/usrMgt.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    navarwid.cpp


HEADERS += \
    mainwindow.h \
    navarwid.h


FORMS += \
    mainwindow.ui \
    navarwid.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    images/image.qrc

DISTFILES += \
    images/back.jpg \
    images/box_back.jpg \
    images/logo.jpg \
    images/title_back.jpg
