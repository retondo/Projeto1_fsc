TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    nucleo.c \
    lista.c \
    interface.c \
    main.c

HEADERS += \
    nucleo.h \
    bcp.h \
    lista.h \
    interface.h

LIBS += /usr/local/lib/libforms.so \
/usr/local/lib/libforms.so.2 \
/usr/local/lib/libforms.so.2.1.3 \
/lib/x86_64-linux-gnu/libpthread.so.0 \
/usr/lib/x86_64-linux-gnu/libX11.so
