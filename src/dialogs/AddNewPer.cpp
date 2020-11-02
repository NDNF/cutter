#include "AddNewPer.h"
#include "ui_AddNewPer.h"

#include <QDebug>
#include <QMessageBox>

AddNewPer::AddNewPer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewPer)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddNewPer::addNewPerAddTable);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddNewPer::close);

}

AddNewPer::~AddNewPer()
{
    delete ui;
}

void AddNewPer::addNewPerAddTable()
{
    if (ui->RegName->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Entered name of register");
    } else {
        QString command = "=!monitor per_reg " + ui->RegName->text();
        /*Выполнить команду, отправив ее через консоль послав сигнал???*/
        qDebug() << command;
        emit sendCmd(command);
        this->close();
    }
}
