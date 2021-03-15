INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/gHeader.h \
    $$PWD/const.h \
    $$PWD/DopplerDataFileConfigure.h \
    $$PWD/FileStruct.h \
    $$PWD/Instrument.h \
    $$PWD/Struct.h \
    $$PWD/DopplerColorIndex.h \
    $$PWD/DopplerConfigure.h \
    $$PWD/DopplerDataFileOperateor.h \
    $$PWD/DopplerXMLReader.h \
    $$PWD/dopplermergedatafileoperateor.h \
    $$PWD/defectidentify.h

SOURCES += \
    $$PWD/const.cpp \
    $$PWD/DopplerColorIndex.cpp \
    $$PWD/DopplerConfigure.cpp \
    $$PWD/DopplerDataFileOperateor.cpp \
    $$PWD/DopplerXMLReader.cpp \
	$$PWD/dopplermergedatafileoperateor.cpp \
    $$PWD/defectidentify.cpp

include(config_phascan_ii/config.pri)

