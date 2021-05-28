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
    ui->IrqTree->setHeaderLabels(QStringList() << "Target Function" << "Call Function" << "Number Irq" << "Level Irq");
    ui->IrqTree->header()->setStretchLastSection(false);
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

    for(auto it: splitIrq) {
        QRegExp rx2(";");
        QStringList splitParams = it.split(rx2, QString::SkipEmptyParts);
        setTreeItem(splitParams[0], splitParams[1], splitParams[2], splitParams[3]);
    }
}

void QIrqWidget::setTreeItem(QString targetFunction, QString callFunction, QString number, QString level)
{
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, targetFunction);
    itm->setText(1, callFunction);
    itm->setText(2, number);
    itm->setText(3, level);
    ui->IrqTree->addTopLevelItem(itm);
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
