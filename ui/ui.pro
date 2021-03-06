QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontactdialog.cpp \
    balancewidget.cpp \
    contactswidget.cpp \
    custombutton.cpp \
    homewidget.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    paycontactdialog.cpp \
    switch.cpp \
    settingswidget.cpp

HEADERS += \
    addcontactdialog.h \
    balancewidget.h \
    contactswidget.h \
    custombutton.h \
    homewidget.h \
    logindialog.h \
    mainwindow.h \
    paycontactdialog.h \
    switch.h \
    settingswidget.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    style.qss \
    styleLight.qss

RESOURCES +=
