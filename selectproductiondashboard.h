#ifndef SELECTPRODUCTIONDASHBOARD_H
#define SELECTPRODUCTIONDASHBOARD_H

#include <QMainWindow>

namespace Ui {
class SelectProductionDashboard;
}

class SelectProductionDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectProductionDashboard(QWidget *parent = 0);
    ~SelectProductionDashboard();
    void init();

private:
    Ui::SelectProductionDashboard *ui;
};

#endif // SELECTPRODUCTIONDASHBOARD_H
