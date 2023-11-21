#ifndef CREATACC_H
#define CREATACC_H
#include <QTextStream>
#include <QFile>
#include <QDialog>
#include <QMap>
#include "account.h"

namespace Ui {
class creatAcc;
}

class creatAcc : public QDialog
{
    Q_OBJECT

public:
    QString tempSurname;
    QString tempNumb;
    int tempPerc;
    int startBal;
    QString filename;
    Account obj1;
    Account obj2;
    Account obj3;
    Account obj4;
    Account obj5;
    QString surname;
    QString accNumber;
    int percent;
    int balance;
    int currentObj;
    QMap<int, Account> bank;
    explicit creatAcc(QWidget *parent = nullptr);
    ~creatAcc();


    void startReg(QString fn, int obj);
    void openFile(QMap<int, Account>& bank, QString filename);
    void upgradeFile(QMap<int, Account>& bank, QString filename);
    Account upgradeDates();
    Account nullDates();


private slots:
    void on_register_butt_clicked();

private:
    Ui::creatAcc *ui;
};

#endif // CREATACC_H
