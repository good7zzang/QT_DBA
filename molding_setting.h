#ifndef MOLDING_SETTING_H
#define MOLDING_SETTING_H

#include <QWidget>

namespace Ui {
class molding_setting;
}

class molding_setting : public QWidget
{
    Q_OBJECT

public:
    explicit molding_setting(QWidget *parent = 0);
    ~molding_setting();

private:
    Ui::molding_setting *ui;
};

#endif // MOLDING_SETTING_H
