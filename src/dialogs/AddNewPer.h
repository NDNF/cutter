#ifndef ADDNEWPER_H
#define ADDNEWPER_H

#include <QDialog>

namespace Ui {
class AddNewPer;
}

class AddNewPer : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewPer(QWidget *parent = 0);
    ~AddNewPer();

private:
    Ui::AddNewPer *ui;

private slots:
    void addNewPerAddTable();

signals:
    void sendCmd(const QString cmd);
};

#endif // ADDNEWPER_H
