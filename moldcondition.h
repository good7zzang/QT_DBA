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
    explicit MoldCondition(QWidget *parent = 0);
    ~MoldCondition();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MoldCondition *ui;
};

#endif // MOLDCONDITION_H
