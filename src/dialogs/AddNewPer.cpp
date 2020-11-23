#include "AddNewPer.h"
#include "ui_AddNewPer.h"

#include <QDebug>
#include <QMessageBox>

AddNewPer::AddNewPer(QWidget *parent, const QString cmd) :
    QDialog(parent), text(cmd),
    ui(new Ui::AddNewPer)
{
    ui->setupUi(this);
    ui->RegName->setText(text);
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
        QString command = ui->RegName->text();
        /*send cmd to terminal*/
        emit sendCmd(command, nullptr);
        this->close();
    }
}
