#ifndef CABINET_H
#define CABINET_H

#include <QDialog>
#include "account.h"
#include <QTimer>

namespace Ui {
class cabinet;
}

class cabinet : public QDialog
{
    Q_OBJECT

public:
    explicit cabinet(QWidget *parent = nullptr);
    ~cabinet();
    QMap<int, Account> bank;
    Account obj1;
    Account obj2;
    Account obj3;
    Account obj4;
    Account obj5;
    QString filename;
    QString surname;
    QString accNumber;
    int percent;
    int balance;
    int currentObj;
    double USD = 36.47, EUR = 38.56;

    void foo(Account obj);
    void startCab(QString fn, int obj);
    void openFile(QMap<int, Account>& bank, QString filename);
    void upgradeFile(QMap<int, Account>& bank, QString filename);
    void upgradeDates(Account obj);

private slots:
    void on_button_takeMoney_clicked();
    void on_button_putMoney_clicked();
    void on_button_editSurname_clicked();
    void on_pushButton_clicked();

    void on_button_USD_clicked();

    void on_button_EUR_clicked();

    void on_buttion_statement_clicked();

private:
    Ui::cabinet *ui;
};

#endif // CABINET_H
