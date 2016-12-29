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
    ReadDXF/test_creationclass.cpp \
    ReadDXF/DrawDxf.cpp

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
    ReadDXF/test_creationclass.h \
    ReadDXF/DrawDxf.h

FORMS    += mainwindow.ui
