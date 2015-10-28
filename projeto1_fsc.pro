TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += projeto1_main.c

HEADERS += projeto1.h

LIBS += /usr/local/lib/libforms.so \
/usr/local/lib/libforms.so.2
