#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T14:44:04
#
#-------------------------------------------------

QT       += core gui opengl printsupport

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

INCLUDEPATH += $$PWD/lib/opengl
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

#DEFINES += QT_NO_DEBUG_OUTPUT
