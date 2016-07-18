#ifndef MOLDCONDITION_REPORT_H
#define MOLDCONDITION_REPORT_H

#include <QMainWindow>

namespace Ui {
class MoldCondition_Report;
}

class MoldCondition_Report : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoldCondition_Report(QWidget *parent = 0);
    ~MoldCondition_Report();

private:
    Ui::MoldCondition_Report *ui;
};

#endif // MOLDCONDITION_REPORT_H
