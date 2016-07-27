#ifndef MACHINEADD_H
#define MACHINEADD_H

#include <QWidget>

namespace Ui {
class MachineAdd;
}

class MachineAdd : public QWidget
{
    Q_OBJECT

public:
    explicit MachineAdd(QWidget *parent = 0);
    ~MachineAdd();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MachineAdd *ui;

};

#endif // MACHINEADD_H
