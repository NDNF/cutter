#include "QIrqWidget.h"
#include "ui_QIrqWidget.h"
#include <QDebug>
#include <QMessageBox>

QIrqWidget::QIrqWidget(MainWindow *main) :
    CutterDockWidget(main),
    ui(new Ui::QIrqWidget)
{
    ui->setupUi(this);

    ui->IrqTree->setColumnCount(4);
    ui->IrqTree->setHeaderLabels(QStringList() << "Target" << "call Dev" << "Number Irq" << "Level Irq");
    ui->IrqTree->header()->setStretchLastSection(false);
    //ui->IrqTree->setColumnHidden(3, true);
    ui->IrqTree->header()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->IrqTree->header()->setSectionResizeMode(1, QHeaderView::Interactive);
    ui->IrqTree->header()->setSectionResizeMode(2, QHeaderView::Interactive);
    ui->IrqTree->header()->setSectionResizeMode(3, QHeaderView::Interactive);
}

QIrqWidget::~QIrqWidget()
{
    delete ui;
}

void QIrqWidget::getIrq(const QString &str)
{
    QString res;
    QRegExp rx("\n");
    QStringList splitIrq = str.split(rx, QString::SkipEmptyParts);
    //qDebug() << "ПРИНЯЛ IRQ: " << splitIrq << "\n\n";

    for(auto it: splitIrq) {
        QRegExp rx2(";");
        QStringList splitParams = it.split(rx2, QString::SkipEmptyParts);
        /*qDebug() << splitParams << "\n\n";
        qDebug() << "splitParams[0]: "<< splitParams[0] << " splitParams[1] " << splitParams[1] << " splitParams[2] << " <<
                    splitParams[2] << " splitParams[3] " << splitParams[3] << endl << endl;*/
        setTreeItem(splitParams[0], splitParams[1], splitParams[2], splitParams[3]);
    }

    //QString res;


    /*-----------use after fixed bugs in Qemu------------------*/


//    QRegExp rx(";");
//    QStringList splitParams = str.split(rx, QString::SkipEmptyParts);
//    qDebug() << splitParams;

//    setTreeItem(splitParams[0], splitParams[1], splitParams[2]);

   /*--------------use after fixed bugs in Qemu----------------*/


//    if (!splitParams[1].isEmpty()) {

//    } else {
//        QTreeWidgetItemIterator it(ui->IrqTree);
//        QTreeWidgetItem* last = NULL;
//        while (*it) {
//            last = (*it)->parent();
//            ++it;
//        }

        /*TODO add last */

//    }

}

void QIrqWidget::setTreeItem(QString parentDev, QString callDev, QString number, QString level)
{
    //qDebug() << "--------------- " << callDev << " " << parentDev << " " << number << " "<< level << endl;
    if (parentDev.isEmpty()) {
        /*Add child to last parent*/
        //ui->Tree->topLevelItemCount();
    } else {
        QTreeWidgetItem* itm = new QTreeWidgetItem();
        itm->setText(0, parentDev);
        itm->setText(1, callDev);
        itm->setText(2, number);
        itm->setText(3, level);
        ui->IrqTree->addTopLevelItem(itm);
    }
}


void QIrqWidget::on_DeleteAll_clicked()
{
    ui->IrqTree->clear();
}

void QIrqWidget::on_Delete_clicked()
{
    auto curr = ui->IrqTree->selectedItems();
    if (curr.isEmpty()) {
        QMessageBox::critical(this, "Error", "Don't selected register");
        return;
    }
    delete curr.first();
}
