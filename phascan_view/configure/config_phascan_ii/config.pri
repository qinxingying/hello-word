
include($$PWD/msgpack/msgpack.pri)

HEADERS += \
    $$PWD/config.h \
    $$PWD/settings.h \
    $$PWD/default_settings.h

SOURCES += \
    $$PWD/config.cpp \
    $$PWD/settings.cpp

LIBQMSGPACK=qmsgpack
CONFIG(debug, debug|release) {
    LIBQMSGPACK = $$join(LIBQMSGPACK,,,"d")
}

LIBS += -L$$PWD/lib -l$$LIBQMSGPACK

include(mercury_paramters/mercury_paramters.pri)
