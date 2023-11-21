#include "cabinet.h"
#include "ui_cabinet.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <string>
#include <QPixmap>

#include <QLocale>

cabinet::cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cabinet)
{
    ui->setupUi(this);
    QPixmap pix(":/img/pic1.png");
    int w = ui->pic1->width();
    int h = ui->pic1->height();

    ui->pic1->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

cabinet::~cabinet()
{
    delete ui;
}

void cabinet::startCab(QString fn, int obj){
    filename = fn;
    currentObj = obj;
    setModal(true);
    openFile(bank,filename);
    if (obj == 1) foo(obj1);
    else if (obj == 2) foo(obj2);
    else if (obj == 3) foo(obj3);
    else if (obj == 4) foo(obj4);
    else if (obj == 5) foo(obj5);
    exec();
    if (obj == 1) upgradeDates(obj1);
    else if (obj == 2) upgradeDates(obj2);
    else if (obj == 3) upgradeDates(obj3);
    else if (obj == 4) upgradeDates(obj4);
    else if (obj == 5) upgradeDates(obj5);
    upgradeFile(bank,filename);
}
void cabinet::foo(Account obj){
    surname = obj.getSurname();
    accNumber = obj.getAccNumber();
    percent = obj.getPercent();
    balance = obj.getBalance();

    QLocale locale(QLocale::English);
    QString formBal = locale.toString(balance);
    ui->cab_surname->setText(surname);

    int length = accNumber.length();
    for (int i = length - 4; i > 0; i -= 4) {
        accNumber.insert(i, ' ');
    }

    QString percent_out = QString::number(percent) + "%";
    ui->cab_number->setText(accNumber);
    ui->cab_percent->setText(percent_out);
    formBal+=" грн";
    ui->cab_balance->setText(formBal);

}
void cabinet::upgradeDates(Account obj){
    obj.setSurname(surname);
    obj.setAccNumber(accNumber);
    obj.setPercent(percent);
    obj.setBalance(balance);
}
void cabinet::openFile(QMap<int, Account>& bank, QString filename){
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int key;
        QString surname, accNumber;
        int percent, balance;

        in >> key >> surname >> accNumber >> percent >> balance;
        obj1.setSurname(surname);
        obj1.setAccNumber(accNumber);
        obj1.setPercent(percent);
        obj1.setBalance(balance);
        bank[key] = obj1;

        in >> key >> surname >> accNumber >> percent >> balance;
        obj2.setSurname(surname);
        obj2.setAccNumber(accNumber);
        obj2.setPercent(percent);
        obj2.setBalance(balance);
        bank[key] = obj2;

        in >> key >> surname >> accNumber >> percent >> balance;
        obj3.setSurname(surname);
        obj3.setAccNumber(accNumber);
        obj3.setPercent(percent);
        obj3.setBalance(balance);
        bank[key] = obj3;

        in >> key >> surname >> accNumber >> percent >> balance;
        obj4.setSurname(surname);
        obj4.setAccNumber(accNumber);
        obj4.setPercent(percent);
        obj4.setBalance(balance);
        bank[key] = obj4;

        in >> key >> surname >> accNumber >> percent >> balance;
        obj5.setSurname(surname);
        obj5.setAccNumber(accNumber);
        obj5.setPercent(percent);
        obj5.setBalance(balance);
        bank[key] = obj5;
    }

    file.close();
}
void cabinet::upgradeFile(QMap<int, Account>& bank, QString filename){
    bank[1]= obj1;
    bank[2]= obj2;
    bank[3]= obj3;
    bank[4]= obj4;
    bank[5]= obj5;
    QFile file (filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (auto it = bank.begin(); it != bank.end(); ++it) {
            out << it.key() << " " << it.value().getSurname() << " " << it.value().getAccNumber() << " " << it.value().getPercent() << " " << it.value().getBalance() << "\n";
        }
          out.flush();
        file.close();
    }
}

void cabinet::on_button_takeMoney_clicked()
{
    int money = ui->line_money->text().toInt();
    if (money <= 0) QMessageBox::critical(nullptr, "Помилка", "Введіть корректне число (ваше число менше за нуль або перевищує допустимий ліміт).");
    else if (money > balance) QMessageBox::critical(nullptr, "Помилка", "У вас недостатньо коштів.");
    else {
    balance = balance - money;
    if (currentObj == 1) obj1.setBalance(balance);
    else if (currentObj == 2) obj2.setBalance(balance);
    else if (currentObj == 3) obj3.setBalance(balance);
    else if (currentObj == 4) obj4.setBalance(balance);
    else if (currentObj == 5) obj5.setBalance(balance);
    QLocale locale(QLocale::English);
    QString formBal = locale.toString(balance);
    formBal+=" грн";
    ui->cab_balance->setText(formBal);
}
}
void cabinet::on_button_putMoney_clicked()
{
    int money = ui->line_money->text().toInt();
    if (money <= 0) QMessageBox::critical(nullptr, "Помилка", "Введіть корректне число (ваше число менше за нуль або перевищує допустимий ліміт).");
    else if (money + balance >= 2147483647 || money+balance < 0) QMessageBox::critical(nullptr, "Помилка", "Ви порушуєте правила нашого банку. Сума на балансі не повинна перевищувати 2.147.483.646 грн.");
    else{
    balance = balance + money;
    if (currentObj == 1) obj1.setBalance(balance);
    else if (currentObj == 2) obj2.setBalance(balance);
    else if (currentObj == 3) obj3.setBalance(balance);
    else if (currentObj == 4) obj4.setBalance(balance);
    else if (currentObj == 5) obj5.setBalance(balance);
    QLocale locale(QLocale::English);
    QString formBal = locale.toString(balance);
    formBal+=" грн";
    ui->cab_balance->setText(formBal);
    }
}
void cabinet::on_button_editSurname_clicked()
{
    surname = ui->line_surname->text();

    bool containsOnlyLetters = true;

    for(int i = 0; i < surname.length(); i++) {
    if(!surname.at(i).isLetter() && surname.at(i)!='\'') {
            containsOnlyLetters = false;
            break;
    }
    }
    if(!containsOnlyLetters) {
    QMessageBox::critical(this,"Помилка", "Прізвище не може містити символів або чисел.");
    }
    else if ( surname.isEmpty()){
    QMessageBox::critical(this,"Помилка", "Поле не може залишатись порожнім.");
    }
    else{
    if (currentObj == 1) obj1.setSurname(surname);
    else if (currentObj == 2) obj2.setSurname(surname);
    else if (currentObj == 3) obj3.setSurname(surname);
    else if (currentObj == 4) obj4.setSurname(surname);
    else if (currentObj == 5) obj5.setSurname(surname);
    ui->cab_surname->setText(surname); }
}
void cabinet::on_pushButton_clicked()
{
     int year = ui->line_deposit_year->text().toInt();
    double testBal = static_cast<double>(balance);
     int maxYear = 0, count = 0;
     for (int i = 0; i<year; i++){
    if (count == 0){
            if (testBal < 2147483645 && testBal > 0) {
            testBal= testBal + (testBal*percent)/100;
    }
        else {maxYear = i; count++;}
    }
     }
     if (maxYear>0) maxYear--;
     QString error = "По закінченню депозиту сума на балансі буде перевищувати дозволену. Ви можете відкрити депозит на " + QString::number(maxYear) + " років." ;
    if (year <= 0) QMessageBox::critical(nullptr, "Помилка", "Введіть додатнє число.");
    else if (year > 50) QMessageBox::critical(nullptr, "Помилка", "Ви не можете відкрити депозит на понад 50 років.");
    else if (testBal>=2147483647  || testBal < 0) QMessageBox::critical(nullptr, "Помилка", error);
    else {
    balance = static_cast<int>(testBal);
    if (currentObj == 1) obj1.setBalance(balance);
    else if (currentObj == 2) obj2.setBalance(balance);
    else if (currentObj == 3) obj3.setBalance(balance);
    else if (currentObj == 4) obj4.setBalance(balance);
    else if (currentObj == 5) obj5.setBalance(balance);
    QLocale locale(QLocale::English);
    QString formBal = locale.toString(balance);
    formBal+=" грн";
    ui->cab_balance->setText(formBal);
    }
}
void cabinet::on_button_USD_clicked()
{
    double bal = static_cast<double>(balance);
    double res = bal / USD;
    QLocale locale(QLocale::English);
    QString result = locale.toString(res, 'f', 2) + " $";
    QMessageBox::about(nullptr, "USD: ", result);
}
void cabinet::on_button_EUR_clicked()
{
    double bal = static_cast<double>(balance);
    double res = bal / EUR;
    QLocale locale(QLocale::English);
    QString result = locale.toString(res, 'f', 2) + " €";
    QMessageBox::about(nullptr, "EUR: ", result);
}

string convertGroup(int num) {
    const string units[10] = { "", "Один", "Два", "Три", "Чотири", "П'ять", "Шість", "Сім", "Вісім", "Дев'ять" };
    const string teens[10] = { "", "Одинадцять", "Дванадцять", "Тринадцять", "Чотирнадцять", "П'ятнадцять", "Шістнадцять", "Сімнадцять", "Вісімнадцять", "Дев'ятнадцять" };
    const string tens[10] = { "", "Десять", "Двадцять", "Тридцять", "Сорок", "П'ятдесят", "Шістдесят", "Сімдесят", "Вісімдесят", "Дев'яносто" };

    string result = "";

    if (num >= 100) {
    result += units[num / 100] + " Сот. ";
    num %= 100;
    }

    if (num >= 11 && num <= 19) {
    result += teens[num - 10] + " ";
    }
    else if (num == 10 || num >= 20) {
    result += tens[num / 10] + " ";
    num %= 10;
    }

    if (num >= 1 && num <= 9) {
    result += units[num] + " ";
    }

    return result;

}
void cabinet::on_buttion_statement_clicked()
{
    int num = balance;
    if (num == 0) {
        QMessageBox::information(nullptr, "Statement", "Нуль");
    }

    string result = "";

    if (num >= 1000000000) {
        result += convertGroup(num / 1000000000) + "Млрд. ";
        num %= 1000000000;
    }

    if (num >= 1000000) {
        result += convertGroup(num / 1000000) + "Млн. ";
        num %= 1000000;
    }

    if (num >= 1000) {
        result += convertGroup(num / 1000) + "Тис. ";
        num %= 1000;
    }

    if (num >= 1) {
        result += convertGroup(num);
    }
    QString res = QString::fromStdString(result);
    QMessageBox::information(nullptr, "Statement", res);
}


