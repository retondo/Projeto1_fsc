TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    nucleo.c \
    projeto_main.c \
    lista.c \
    interface.c

HEADERS += \
    nucleo.h \
    bcp.h \
    lista.h \
    interface.h

LIBS += /usr/local/lib/libforms.so \
/usr/local/lib/libforms.so.2
