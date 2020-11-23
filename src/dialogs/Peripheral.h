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
public slots:
    void getListPeripherals(const QString &str);
signals:
    void loadList();

private:
    Ui::Peripheral *ui;
    void showAddPerReg();
};

#endif // PERIPHERAL_H
