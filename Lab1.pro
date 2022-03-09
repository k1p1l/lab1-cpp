QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddataapp.cpp \
    dispetcher.cpp \
    findfile.cpp \
    getapp.cpp \
    main.cpp \
    mainwindow.cpp \
    models.cpp \
    updateapp.cpp

HEADERS += \
    adddataapp.h \
    dispetcher.h \
    findfile.h \
    getapp.h \
    mainwindow.h \
    models.h \
    updateapp.h

FORMS += \
    adddataapp.ui \
    dispetcher.ui \
    findfile.ui \
    getapp.ui \
    mainwindow.ui \
    updateapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
