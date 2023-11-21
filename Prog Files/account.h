#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string>
#include <QString>
using namespace std;

class Account
{
private:
    QString surname;
    QString accNumber;
    int percent;
    int balance;
public:
    void createAccount(QString sur, QString accNum, int perc, int bal);
    void changeSurname(QString newSurname);
    void takeMoney(int money);
    void putMoney(int money);
    void deposit(int year);
    int convertToUSD();
    int convertToEUR();
    QString statement(int num);
    void critical1();
    void critical2();
    QString getSurname();
    QString getAccNumber();
    int getPercent();
    int getBalance();
    void setSurname(QString sur);
    void setAccNumber(QString accNum);
    void setPercent(int perc);
    void setBalance(int bal);

    Account(QString sur, QString accNum, int perc, int bal){
        surname = sur;
        accNumber = accNum;

        percent = perc;
        balance = bal;
    }
    Account(){
        surname = "Null";
        accNumber = "0000000000000000";
        percent = 0;
        balance = 0;
    }
};

#endif // ACCOUNT_H
