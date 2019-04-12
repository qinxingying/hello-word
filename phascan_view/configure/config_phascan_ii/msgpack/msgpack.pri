
INCLUDEPATH += $$PWD

include($$PWD/private/private.pri)
include($$PWD/stream/stream.pri)

HEADERS += \
    $$PWD/msgpack.h \
    $$PWD/msgpackcommon.h \
    $$PWD/msgpack_export.h \
    $$PWD/endianhelper.h \
    $$PWD/msgpackstream.h
