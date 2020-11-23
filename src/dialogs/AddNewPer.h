#ifndef ADDNEWPER_H
#define ADDNEWPER_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class AddNewPer;
}

class AddNewPer : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewPer(QWidget *parent = 0, const QString cmd = "");
    ~AddNewPer();

private:
    Ui::AddNewPer *ui;
    QString text;

private slots:
    void addNewPerAddTable();

signals:
    void sendCmd(const QString str, QTreeWidgetItem *item);
};

#endif // ADDNEWPER_H
