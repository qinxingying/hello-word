#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T15:08:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dxf_test
TEMPLATE = app
PROJECT_DIR = $$PWD
INCLUDEPATH = $$PWD/ReadDXF

SOURCES += main.cpp\
    mainwindow.cpp \
    ReadDXF/dl_dxf.cpp \
    ReadDXF/dl_writer_ascii.cpp \
    ReadDXF/DrawDxf.cpp \
    ReadDXF/dxf_data.cpp

HEADERS  += mainwindow.h \
    ReadDXF/dl_attributes.h \
    ReadDXF/dl_codes.h \
    ReadDXF/dl_creationadapter.h \
    ReadDXF/dl_creationinterface.h \
    ReadDXF/dl_dxf.h \
    ReadDXF/dl_entities.h \
    ReadDXF/dl_exception.h \
    ReadDXF/dl_extrusion.h \
    ReadDXF/dl_global.h \
    ReadDXF/dl_writer.h \
    ReadDXF/dl_writer_ascii.h \
    ReadDXF/DrawDxf.h \
    ReadDXF/dxf_data.h

FORMS    += mainwindow.ui
