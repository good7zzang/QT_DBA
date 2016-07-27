#include "cmsdba_maindlg.h"
#include <QApplication>
#include <molding_setting.h>
#include "settinglog.h"
#include "moldcondition_report.h"
#include "alarmlog.h"
#include "singlegraph.h"
#include "dbsearchact.h"
#include "moldconditionformset.h"
#include "productstatistics.h"
#include "dbsearchsetting.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMSDBA_MainDlg w;
    w.show();

//    molding_setting moldsetting;
//    MoldCondition_Report MoldCondition;
//    MoldCondition.show();
//    moldsetting.show();


//    DBsearchact dbsearchact;
//    dbsearchact.show();

//    SingleGraph singlegraph;
//    singlegraph.show();

//    AlarmLog alarmlog;
//    alarmlog.show();

//    SettingLog settinglog;
//    settinglog.show();

//    MoldConditionFormSet moldconditionformset;
//    moldconditionformset.show();

//    DBA_Setting dba_setting;
//    dba_setting.show();

//    Productstatistics productstatistics;
//    productstatistics.show();

//    AlarmLogShow alarmlogshow;
//    alarmlogshow.show();

//    SettingLogShow settinglogshow;
//    settinglogshow.show();

//    DBsearchact db;
//    db.show();

    DBsearchsetting db;
    db.show();

    return a.exec();
}
