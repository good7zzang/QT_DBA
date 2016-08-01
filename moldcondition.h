#ifndef MOLDCONDITION_H
#define MOLDCONDITION_H

#include <QMainWindow>

namespace Ui {
class MoldCondition;
}

class MoldCondition : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoldCondition(QString machine_name,QWidget *parent = 0);
    QString machine_name;
    ~MoldCondition();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MoldCondition *ui;
};

#endif // MOLDCONDITION_H
