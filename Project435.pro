#-------------------------------------------------
#
# Project created by QtCreator 2018-02-14T12:56:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project435
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        welcome.cpp \
    signup.cpp \
    main.cpp \
    signin.cpp \
    home.cpp \
    user.cpp \
    scores.cpp \
    game1.cpp \
    game2.cpp \
    game.cpp \
    gamemenu.cpp \
    history.cpp \
    description.cpp

HEADERS += \
        welcome.h \
    signup.h \
    signin.h \
    home.h \
    user.h \
    scores.h \
    game1.h \
    game2.h \
    game.h \
    gamemenu.h \
    history.h \
    description.h

FORMS += \
        welcome.ui \
    signup.ui \
    signin.ui \
    home.ui \
    game1.ui \
    game2.ui \
    gamemenu.ui \
    history.ui \
    description.ui
