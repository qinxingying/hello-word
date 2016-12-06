INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/threads/DataRefreshThread.h \
    $$PWD/dopplerfocallaw.h \
    $$PWD/CalcMeasurement.h \
    $$PWD/DopplerPart.h \
    $$PWD/Limitation.h \
    $$PWD/ParameterProcess.h

SOURCES += \
    $$PWD/threads/DataRefreshThread.cpp \
    $$PWD/CalcMeasurement.cpp \
    $$PWD/DopplerPart.cpp \
    $$PWD/Limitation.cpp \
    $$PWD/ParameterProcess.cpp
