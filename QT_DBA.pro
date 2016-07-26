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
    moldcondition_report.cpp\
    dbsearchact.cpp \
    singlegraph.cpp \
    alarmlog.cpp \
    settinglog.cpp \
    moldconditionformset.cpp \
    dba_setting.cpp \
    productstatistics.cpp \
    machineadd.cpp \
    moldcondition.cpp \
    alarmlogshow.cpp \
    settinglogshow.cpp

HEADERS  += cmsdba_maindlg.h \
    molding_setting.h \
    moldcondition_report.h \
    singlegraph.h \
    alarmlog.h \
    settinglog.h \
    moldconditionformset.h \
    dba_setting.h \
    productstatistics.h \
    machineadd.h \
    moldcondition.h \
    alarmlogshow.h \
    settinglogshow.h

FORMS    += cmsdba_maindlg.ui \
    molding_setting.ui \
    moldcondition_report.ui \
    singlegraph.ui \
    alarmlog.ui \
    settinglog.ui \
    moldconditionformset.ui \
    dba_setting.ui \
    productstatistics.ui \
    machineadd.ui \
    moldcondition.ui \
    alarmlogshow.ui \
    settinglogshow.ui



HEADERS  += cmsdba_maindlg.h \
    molding_setting.h \
    dbsearchact.h

FORMS    += cmsdba_maindlg.ui \
    molding_setting.ui \
    dbsearchact.ui


RESOURCES += \
    res.qrc
