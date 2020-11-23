#ifndef QREGWIDGET_H
#define QREGWIDGET_H

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <memory>
#include <AddNewPer.h>
#include <Peripheral.h>

class MainWindow;
class QTreeWidgetItem;
class AddNewPer;

namespace Ui {
class QRegWidget;
}

class QRegWidget : public CutterDockWidget
{
    Q_OBJECT

public:
    explicit QRegWidget(MainWindow *main);
    ~QRegWidget();

public slots:
    void getDataRequest(QTreeWidgetItem *item, const QString &path, const QString &str);
    void update();

private slots:
    void addNewReg();
    void deleteReg();
    void showPeripherals();
    void loadRegs(QTreeWidgetItem *item);

private:
    std::unique_ptr<Ui::QRegWidget> ui;
    QTreeWidgetItem* setTreeHead(QString path, QString type, QString name, QString value);
    void setTreeParent(QString path, QString type, QString name, QString value);
    void setTreeChild(QString path, QString type, QString name, QString value, QTreeWidgetItem *parent);
    void updateTreeChild(QString path, QString type, QString name, QString value, QTreeWidgetItem *item);
    QString createPath(QString path, QString name);
    void getParams(QString str, QString &name,  QString &type,  QString &value);
    bool is_update(QVector<QTreeWidgetItem *> v, QTreeWidgetItem* itm);
signals:
    void getRegs(const QString cmd, QTreeWidgetItem *item);
};

#endif // QREGWIDGET_H
