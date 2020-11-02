#include "QRegWidget.h"
#include "ui_QRegWidget.h"

#include <QDebug>


QRegWidget::QRegWidget(MainWindow *main) :
    CutterDockWidget(main),
    ui(new Ui::QRegWidget)
{
    ui->setupUi(this);
    //ui->tableWidget->setColumnCount(3);
    //ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Type" << "Name" << "Value");
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->Tree->setColumnCount(3);
    ui->Tree->setHeaderLabels(QStringList() << "Type" << "Name" << "Value");
    ui->Tree->header()->setStretchLastSection(false);
    ui->Tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->Tree->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->Tree->header()->setSectionResizeMode(2, QHeaderView::Stretch);
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, "Hello");
    itm->setText(1, "World");
    itm->setText(2, "Gays");
    ui->Tree->addTopLevelItem(itm);
    connect(ui->Add, &QPushButton::clicked, this, &QRegWidget::addNewReg);

}
QRegWidget::~QRegWidget() {}

void QRegWidget::addNewReg()
{
    AddNewPer *RegWindow = new AddNewPer(this);
    connect(RegWindow, &AddNewPer::sendCmd, Core(), &CutterCore::requestPerReg);

    RegWindow->show();
    /*всплывающее окно с добавлением правила*/
    qDebug() << "I'm here";
}
