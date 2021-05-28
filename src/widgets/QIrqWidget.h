#ifndef QIRQWIDGET_H
#define QIRQWIDGET_H

#include "CutterDockWidget.h"
#include <QTreeWidgetItem>

namespace Ui {
class QIrqWidget;
}

class QIrqWidget : public CutterDockWidget
{
    Q_OBJECT

public:
    explicit QIrqWidget(MainWindow *main);
    ~QIrqWidget();

public slots:
    void getIrq(const QString &str);

private slots:
    void on_DeleteAll_clicked();

    void on_Delete_clicked();

private:
    Ui::QIrqWidget *ui;
    void setTreeItem(QString targetFunction, QString callFunction, QString number, QString level);
};

#endif // QIRQWIDGET_H
