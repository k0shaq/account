#include "account.h"
#include <QMessageBox>

void Account::createAccount(QString sur, QString accNum, int perc, int bal){
    surname = sur;
    accNumber = accNum;
    percent = perc;
    balance = bal;
}
void Account::changeSurname(QString newSurname){
    surname = newSurname;
}
void Account::takeMoney(int money){
    balance = balance - money;
}
void Account::putMoney(int money){
    balance = balance + money;
}
void Account::deposit(int year){
    for (int i = 0; i < year; i++){
        balance = balance + ((balance*percent)/100);
   }
}
int Account::convertToUSD(){
   return balance/36;
}
int Account::convertToEUR(){
   return balance/39;
}
void Account::critical1(){
    QMessageBox::critical(nullptr,"Система безпеки банку", "Ваш рахунок заблоковано. Ваш баланс перевищує дозволений ліміт.");
}
void Account::critical2(){
     QMessageBox::critical(nullptr,"Система безпеки банку", "Ваш рахунок заблоковано. Ми не працюємо з боржниками.");
}

QString Account::getSurname(){
   return surname;
}
QString Account::getAccNumber(){
   return accNumber;
}
int Account::getPercent(){
   return percent;
}
int Account::getBalance(){
   return balance;
}

void Account::setSurname(QString sur){
   surname = sur;
}
void Account::setAccNumber(QString accNum){
   accNumber = accNum;
}
void Account::setPercent(int perc){
   percent = perc;
}
void Account::setBalance(int bal){
   balance = bal;
}
