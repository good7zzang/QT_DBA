#ifndef CMSDBA_MAINDLG_H
#define CMSDBA_MAINDLG_H

#include <QMainWindow>

namespace Ui {
class CMSDBA_MainDlg;
}

class CMSDBA_MainDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMSDBA_MainDlg(QWidget *parent = 0);
    ~CMSDBA_MainDlg();

private:
    Ui::CMSDBA_MainDlg *ui;

public:
    void init();
    void Toolbarinit();
};

#endif // CMSDBA_MAINDLG_H
