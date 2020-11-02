#ifndef QREGWIDGET_H
#define QREGWIDGET_H

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <memory>
#include <AddNewPer.h>

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

private slots:
    void addNewReg();

private:
    std::unique_ptr<Ui::QRegWidget> ui;

};

#endif // QREGWIDGET_H
