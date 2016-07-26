#ifndef DBSEARCHSETTING_H
#define DBSEARCHSETTING_H

#include <QWidget>

namespace Ui {
class DBsearchsetting;
}

class DBsearchsetting : public QWidget
{
    Q_OBJECT

public:
    explicit DBsearchsetting(QWidget *parent = 0);
    ~DBsearchsetting();

private:
    Ui::DBsearchsetting *ui;
};

#endif // DBSEARCHSETTING_H
