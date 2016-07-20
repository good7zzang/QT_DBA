#include "cmsdba_maindlg.h"
#include <QApplication>
#include <molding_setting.h>
#include "settinglog.h"
#include "moldcondition_report.h"
#include "alarmlog.h"
#include "singlegraph.h"
#include "dbsearchact.h"
#include "moldconditionformset.h"

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

    MoldConditionFormSet moldconditionformset;
    moldconditionformset.show();

    return a.exec();
}
