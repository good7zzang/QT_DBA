#ifndef SINGLEGRAPH_H
#define SINGLEGRAPH_H

#include <QWidget>

namespace Ui {
class SingleGraph;
}

class SingleGraph : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGraph(QWidget *parent = 0);
    ~SingleGraph();

private:
    Ui::SingleGraph *ui;
};

#endif // SINGLEGRAPH_H
