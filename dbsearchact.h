#ifndef DBSEARCHACT_H
#define DBSEARCHACT_H

#include <QWidget>

namespace Ui {
class DBsearchact;
}

class DBsearchact : public QWidget
{
    Q_OBJECT

public:
    explicit DBsearchact(QWidget *parent = 0);
    ~DBsearchact();

private:
    Ui::DBsearchact *ui;
};

#endif // DBSEARCHACT_H
