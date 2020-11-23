#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <QDialog>

namespace Ui {
class Peripheral;
}

class Peripheral : public QDialog
{
    Q_OBJECT

public:
    explicit Peripheral(QWidget *parent = 0);
    ~Peripheral();

private:
    Ui::Peripheral *ui;
};

#endif // PERIPHERAL_H
