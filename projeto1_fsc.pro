TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    files.c

HEADERS += \
    files.h

LIBS += /usr/local/lib/libforms.so
/usr/local/lib/libforms.so.2
