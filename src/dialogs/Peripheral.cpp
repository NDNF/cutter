#include "Peripheral.h"
#include "ui_Peripheral.h"

Peripheral::Peripheral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peripheral)
{
    ui->setupUi(this);
}

Peripheral::~Peripheral()
{
    delete ui;
}
