#include "cmsdba_maindlg.h"
#include <QApplication>
#include <molding_setting.h>

#include <moldcondition_report.h>

#include <singlegraph.h>
#include "dbsearchact.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMSDBA_MainDlg w;
    w.show();

    molding_setting moldsetting;
    MoldCondition_Report MoldCondition;
    MoldCondition.show();
    moldsetting.show();


    DBsearchact dbsearchact;
    dbsearchact.show();

    SingleGraph singlegraph;
    singlegraph.show();


    return a.exec();
}
