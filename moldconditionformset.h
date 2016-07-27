#ifndef MOLDCONDITIONFORMSET_H
#define MOLDCONDITIONFORMSET_H

#include <QWidget>

namespace Ui {
class MoldConditionFormSet;
}

class MoldConditionFormSet : public QWidget
{
    Q_OBJECT

public:
    explicit MoldConditionFormSet(QWidget *parent = 0);
    ~MoldConditionFormSet();

private:
    Ui::MoldConditionFormSet *ui;
};

#endif // MOLDCONDITIONFORMSET_H
