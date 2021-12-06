QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contactswidget.cpp \
    custombutton.cpp \
    homewidget.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    settingswidget.cpp \
    logindialog.cpp \
    payments.cpp \
    togglebtn.cpp \
    payments.cpp

HEADERS += \
    contactswidget.h \
    custombutton.h \
    homewidget.h \
    logindialog.h \
    mainwindow.h \
    settingswidget.h \
    payments.h \
    togglebtn.h \
    payments.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Montserrat-Bold.ttf \
    style.qss

RESOURCES +=
