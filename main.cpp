#include "cmsdba_maindlg.h"
#include <QApplication>
#include <molding_setting.h>
#include "dbsearchact.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMSDBA_MainDlg w;
    w.show();

    molding_setting moldsetting;
    moldsetting.show();

    DBsearchact dbsearchact;
    dbsearchact.show();


    return a.exec();
}
