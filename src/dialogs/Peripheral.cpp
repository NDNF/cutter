#include "Peripheral.h"
#include "ui_Peripheral.h"
#include "AddNewPer.h"
#include "core/Cutter.h"
#include <QDebug>
#include <QMessageBox>

Peripheral::Peripheral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Peripheral)
{
    ui->setupUi(this);

    connect(ui->Close, &QPushButton::clicked, this, &Peripheral::close);
    connect(ui->Select, &QPushButton::clicked, this, &Peripheral::showAddPerReg);
}

Peripheral::~Peripheral()
{
    delete ui;
}

void Peripheral::getListPeripherals(const QString &str)
{
    if (str.isEmpty()) {
        QMessageBox::critical(this, "Error", "Information not received");
        return;
    }
    QRegExp rx("\r\n");
    QStringList rows = str.split(rx, QString::SkipEmptyParts);
    for (auto it = rows.begin()+1; it != rows.end(); it++) {
        QString s = (*it).mid(2, (*it).length()-2);
        ui->List->addItem(s);
    }
}

void Peripheral::showAddPerReg()
{
    AddNewPer *RegWindow = new AddNewPer(this, ui->List->currentItem()->text());
    connect(RegWindow, &AddNewPer::sendCmd, Core(), &CutterCore::requestPerReg);
    RegWindow->show();
    close();
}
