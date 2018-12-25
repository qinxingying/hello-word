
include($$PWD/msgpack/msgpack.pri)

HEADERS += \
    $$PWD/config.h

SOURCES += \
    $$PWD/config.cpp

LIBQMSGPACK=qmsgpack
CONFIG(debug, debug|release) {
    LIBQMSGPACK = $$join(LIBQMSGPACK,,,"d")
}

LIBS += -L$$PWD/lib -l$$LIBQMSGPACK
