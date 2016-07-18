#include "cmsdba_maindlg.h"
#include <QApplication>
#include <molding_setting.h>
#include <moldcondition_report.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMSDBA_MainDlg w;
    w.show();

    molding_setting moldsetting;
    MoldCondition_Report MoldCondition;
    MoldCondition.show();
    moldsetting.show();

    return a.exec();
}
