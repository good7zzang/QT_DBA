#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T09:51:51
#
#-------------------------------------------------

QT       += core gui network sql xlsx charts

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
    settinglogshow.cpp \
    dbsearchsetting.cpp \
    m_table_item.cpp \
    simplecrypt.cpp \
    db_serversetting.cpp \
    zoomchart.cpp \
    zoomchartview.cpp \
    callout.cpp \
    data_graph_m_widget.cpp \
    heatername_setting.cpp \
    exelcell_setting.cpp \
    temp_moniter_style1.cpp \
    fpfrom.cpp \
    selectproductiondashboard.cpp \
    query_thread.cpp \
    productionboard_setting.cpp \
    dbsearchalarmlog.cpp


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
    settinglogshow.h \
    dbsearchsetting.h \
    m_table_item.h \
    simplecrypt.h \
    db_serversetting.h \
    zoomchart.h \
    zoomchartview.h \
    callout.h \
    data_graph_m_widget.h \
    heatername_setting.h \
    exelcell_setting.h \
    temp_moniter_style1.h \
    fpfrom.h \
    selectproductiondashboard.h \
    query_thread.h \
    productionboard_setting.h \
    dbsearchalarmlog.h


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
    settinglogshow.ui \
    dbsearchsetting.ui \
    db_serversetting.ui \
    data_graph_m_widget.ui \
    heatername_setting.ui \
    exelcell_setting.ui \
    temp_moniter_style1.ui \
    fpfrom.ui \
    selectproductiondashboard.ui \
    productionboard_setting.ui \
    dbsearchalarmlog.ui




HEADERS  += cmsdba_maindlg.h \
    molding_setting.h \
    dbsearchact.h

FORMS    += cmsdba_maindlg.ui \
    molding_setting.ui \
    dbsearchact.ui

TRANSLATIONS += Lang_ko_KR.ts Lang_en_EN.ts\

RESOURCES += \
    res.qrc
