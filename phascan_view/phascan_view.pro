#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T14:44:04
#
#-------------------------------------------------

QT       += core gui opengl

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

SOURCES += main.cpp

LIBS += -L$$PWD/./ -lDopplerFocalLaw
