#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T09:51:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_DBA
TEMPLATE = app


SOURCES += main.cpp\
        cmsdba_maindlg.cpp \
    molding_setting.cpp \
    moldcondition_report.cpp

HEADERS  += cmsdba_maindlg.h \
    molding_setting.h \
    moldcondition_report.h

FORMS    += cmsdba_maindlg.ui \
    molding_setting.ui \
    moldcondition_report.ui

RESOURCES += \
    res.qrc
