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

    ui->Tree->setColumnCount(4);
    ui->Tree->setHeaderLabels(QStringList() << "Name" << "Type" << "Value");
    ui->Tree->header()->setStretchLastSection(false);
    ui->Tree->setColumnHidden(3, true);
    ui->Tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->Tree->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->Tree->header()->setSectionResizeMode(2, QHeaderView::Stretch);
    connect(ui->Add, &QPushButton::clicked, this, &QRegWidget::addNewReg);
    connect(ui->Delete, &QPushButton::clicked, this, &QRegWidget::deleteReg);
    connect(ui->Per, &QPushButton::clicked, this, &QRegWidget::showPeripherals);
    connect(ui->Tree, &QTreeWidget::itemExpanded, this, &QRegWidget::loadRegs);
    connect(this, &QRegWidget::getRegs, Core(), &CutterCore::requestPerReg);
    connect(Core(), &CutterCore::needUpdateQPerReg, this, &QRegWidget::update);
}
QRegWidget::~QRegWidget() {}

void QRegWidget::addNewReg()
{
    AddNewPer *RegWindow = new AddNewPer(this);
    connect(RegWindow, &AddNewPer::sendCmd, Core(), &CutterCore::requestPerReg);

    RegWindow->show();
}

void QRegWidget::deleteReg()
{
    auto curr = ui->Tree->selectedItems();
    if (curr.isEmpty()) {
        QMessageBox::critical(this, "Error", "Don't selected register");
        return;
    }
    if (curr.first()->parent()) {
        QMessageBox::critical(this, "Error", "You can delete only top level register");
        return;
    }
    delete curr.first();
}

void QRegWidget::showPeripherals()
{
    Peripheral *PerWindow = new Peripheral(this);
    connect(PerWindow, &Peripheral::loadList, Core(), &CutterCore::requestListPeripherals);
    connect(Core(), &CutterCore::requestDataListPeripherals, PerWindow, &Peripheral::getListPeripherals);
    PerWindow->loadList();
    PerWindow->show();
}

void QRegWidget::loadRegs(QTreeWidgetItem *item)
{
    emit getRegs(item->text(3), item);
}

void QRegWidget::setTreeChild(QString path, QString type, QString name, QString value, QTreeWidgetItem *parent)
{
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(1, type);
    itm->setText(0, name);
    itm->setText(2, value);

    path = createPath(path, name);
    itm->setText(3, path);

    if(value.isEmpty()) {
        /*module for displaying the deployment icon*/
        QTreeWidgetItem* t = new QTreeWidgetItem(itm);
        t->setText(1, "");
        t->setText(0, "");
        t->setText(2, "");
        t->setText(3, "");
    }
}

void QRegWidget::updateTreeChild(QString path, QString type, QString name, QString value, QTreeWidgetItem *item)
{
    item->setText(1, type);
    item->setText(0, name);
    item->setText(2, value);

    path = createPath(path, name);
    item->setText(3, path);

    if (item->childCount() == 0 && value.isEmpty()) {
        /*module for displaying the deployment icon*/
        QTreeWidgetItem* t = new QTreeWidgetItem(item);
        t->setText(1, "");
        t->setText(0, "");
        t->setText(2, "");
        t->setText(3, "");
    }

}

QString QRegWidget::createPath(QString path, QString name)
{
    QString res;
    QRegExp rx("/");
    QStringList splitPath = path.split(rx, QString::SkipEmptyParts);

    /*situation when tmp and tmp[i] */

    int ind = name.indexOf("[");

    auto end = splitPath.end();

    if(splitPath.last().length() == ind) {
        end -= 1;
    }

    for(auto it = splitPath.begin(); it != end; it++) {
        res += *it + "/";
    }
    res += name;
    return res;
}

void QRegWidget::getParams(QString str, QString &name, QString &type, QString &value)
{
    for (auto itType = str.begin()+3; itType != str.end(); itType++) {
        if (*itType != '>') {
            type += *itType;
        } else {
            for (auto itName = itType + 2; itName != str.end(); itName++) {
                if (*itName != ' ') {
                    name += *itName;
                } else {
                    for (auto itValue = itName + 1; itValue != str.end(); itValue++) {
                        value += *itValue;
                    }
                    return;
                }
            }
            return;
        }
    }
    return;
}

bool QRegWidget::is_update(QVector<QTreeWidgetItem *> v, QTreeWidgetItem *itm)
{
    for(auto it: v) {
        if (it == itm) {
            return true;
        }
    }
    return false;
}

QTreeWidgetItem* QRegWidget::setTreeHead(QString path, QString type, QString name, QString value)
{
    auto count = ui->Tree->topLevelItemCount();
    for(int i = 0; i < count; i++) {
        if (ui->Tree->topLevelItem(i)->text(0) == name) {
            return nullptr;
        }
    }
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(1, type);
    itm->setText(0, name);
    itm->setText(2, value);
    itm->setText(3, path);
    ui->Tree->addTopLevelItem(itm);
    return itm;
}

void QRegWidget::getDataRequest(QTreeWidgetItem *item, const QString &path, const QString &str)
{
    QRegExp rx("\r\n");
    QStringList rows = str.split(rx, QString::SkipEmptyParts);

    if (!item && rows[0].indexOf("<ERROR>") != -1) {
        QMessageBox::critical(this, "Error", "Request to a non-existent register was received");
        return;
    }

    QRegExp rx1("/");
    QStringList headArgs = path.split(rx1, QString::SkipEmptyParts);
    QString headName = headArgs.last();

    if (!item) {
        item = setTreeHead(path, "", headName, "");
        if (!item) {
            return;
        }
    }

    int ind = 0;
    for(auto it = rows.begin(); it != rows.end()-1; it++, ind++) {
        QString name, type, value = "";
        getParams(*it,name,type,value);
        if (item->child(ind)) {
            updateTreeChild(path, type, name, value, item->child(ind));
        } else {
            setTreeChild(path, type, name, value, item);
        }
    }
    return;
}

void QRegWidget::update()
{
    QVector<QTreeWidgetItem *> used;
    QTreeWidgetItemIterator it(ui->Tree);
    while (*it) {
        auto item = (*it);
        auto parent = item->parent();
        if (parent && !is_update(used, parent) && parent->isExpanded()) {
            emit getRegs(parent->text(3), parent);
            used.push_back(parent);
        }
        ++it;
    }
}
