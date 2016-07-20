#ifndef PRODUCTSTATISTICS_H
#define PRODUCTSTATISTICS_H

#include <QWidget>

namespace Ui {
class Productstatistics;
}

class Productstatistics : public QWidget
{
    Q_OBJECT

public:
    explicit Productstatistics(QWidget *parent = 0);
    ~Productstatistics();

private:
    Ui::Productstatistics *ui;
};

#endif // PRODUCTSTATISTICS_H
