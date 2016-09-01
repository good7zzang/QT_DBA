#ifndef SELECTPRODUCTIONDASHBOARD_H
#define SELECTPRODUCTIONDASHBOARD_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QDateTime>
#include "query_thread.h"
#include "productionboard_setting.h"

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
    void DBinit();
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    void TimeUpdate();

public slots:
    void Menubartriggered(QAction* action);

private:
    Ui::SelectProductionDashboard *ui;
};

#endif // SELECTPRODUCTIONDASHBOARD_H
