QT -= gui
QT += network sql

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    mytcpserver.cpp \
    database.cpp \
    functions.cpp

HEADERS += \
    mytcpserver.h \
    database.h \
    functions.h