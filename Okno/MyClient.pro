QT += core widgets network

CONFIG += c++17
CONFIG -= app_bundle

TARGET   = MyClient
TEMPLATE = app

SOURCES += \
    main.cpp \
    singletonclient.cpp \
    windowmanager.cpp \
    authwidget.cpp \
    registerwidget.cpp \
    mainmenuwidget.cpp \
    taskwidget.cpp \
    statswidget.cpp

HEADERS += \
    singletonclient.h \
    windowmanager.h \
    authwidget.h \
    registerwidget.h \
    mainmenuwidget.h \
    taskwidget.h \
    statswidget.h

FORMS += \
    authwidget.ui \
    registerwidget.ui \
    mainmenuwidget.ui \
    taskwidget.ui \
    statswidget.ui
