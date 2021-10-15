#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T14:44:04
#
#-------------------------------------------------

QT       += core gui opengl printsupport axcontainer
CONFIG += C++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = phascan_view
TEMPLATE = app

PROJECT_DIR = $$PWD

RC_FILE = app.rc
RESOURCES    += mainwindow.qrc
TRANSLATIONS += translator/phascan_view_chinese.ts \
                translator/phascan_view_english.ts \
                translator/phascan_view_japanese.ts

include(ui/ui.pri)
include(configure/configure.pri)
include(process/process.pri)
include(draw_scan/draw_scan.pri)
include(doppler_view/doppler_view.pri)
include(dxflib/dxflib.pri)
include(remote_monitoring/remote_monitoring.pri)

SOURCES += main.cpp

HEADERS += stable.h\
    version.h


QMAKE_CXXFLAGS += /MP
PRECOMPILED_HEADER = stable.h

LIBS += -L$$PWD/./ -lDopplerFocalLaw

LIBS += -L$$PWD/lib/opengl/ -lglut
LIBS += -L$$PWD/lib/opengl/ -lglut32

win32:CONFIG(release, debug|release): {
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Release/ -lopencv_core2413
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Release/ -lopencv_highgui2413
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Release/ -lopencv_imgproc2413
}
else:win32:CONFIG(debug, debug|release): {
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Debug/ -lopencv_core2413d
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Debug/ -lopencv_highgui2413d
LIBS += -L$$PWD/lib/OpenCV2.4.13.6/Debug/ -lopencv_imgproc2413d
}

INCLUDEPATH += $$PWD/lib/opengl
INCLUDEPATH += $$PWD/lib/OpenCV2.4.13.6/include
DEPENDPATH += $$PWD/lib/opengl

DISTFILES += \
    translator/phascan_view_chinese.ts \
    translator/phascan_view_english.ts \
    translator/phascan_view_japanese.ts

versionBuild.target=version
win32 {
versionBuild.commands = $$PWD/update_version.sh $$PWD/
} else {
versionBuild.commands = $$PWD/update_version.sh $$PWD/
}

QMAKE_EXTRA_TARGETS += versionBuild
PRE_TARGETDEPS += version

win32:CONFIG(release, debug|release):{
DEFINES += QT_NO_DEBUG_OUTPUT

QT += concurrent
}

