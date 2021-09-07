INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/threads/DataRefreshThread.h \
    $$PWD/dopplerfocallaw.h \
    $$PWD/CalcMeasurement.h \
    $$PWD/Limitation.h \
    $$PWD/ParameterProcess.h \
    $$PWD/aidedanalysis.h \
    $$PWD/aexportscandatatoexcel.h

SOURCES += \
    $$PWD/threads/DataRefreshThread.cpp \
    $$PWD/CalcMeasurement.cpp \
    $$PWD/Limitation.cpp \
    $$PWD/ParameterProcess.cpp \
    $$PWD/aidedanalysis.cpp \
    $$PWD/aexportscandatatoexcel.cpp
