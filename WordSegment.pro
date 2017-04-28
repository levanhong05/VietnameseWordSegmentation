#-------------------------------------------------
#
# Project created by QtCreator 2017-04-27T13:32:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:TARGET = ../bin/WordSegment
win32:TARGET = ../dist/bin/WordSegment

TEMPLATE = app


SOURCES +=      main.cpp\
                mainwindow.cpp \
                wordsegmentation.cpp \
    machine.cpp

HEADERS  +=     mainwindow.h \
                wordsegmentation.h \
    machine.h \
    configure.h

FORMS    +=     mainwindow.ui

win32 {
    SOURCEPATH = $$PWD/data
    DESTPATH = $$OUT_PWD/dist/bin
    copydata.commands = "$(COPY_DIR) $$replace(SOURCEPATH,/,\\) $$replace(DESTPATH,/,\\)"
}

unix {
    copydata.commands = "$(COPY_DIR) $$PWD/data $$OUT_PWD/../bin/"
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata
