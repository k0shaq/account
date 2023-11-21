#include "creatacc.h"
#include "ui_creatacc.h"
#include <QMessageBox>

creatAcc::creatAcc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatAcc)
{
    ui->setupUi(this);
     setWindowFlag(Qt::WindowCloseButtonHint, false);
}

creatAcc::~creatAcc()
{
    delete ui;
}

void creatAcc::on_register_butt_clicked()
{
    int count = 0;
    bool isNumbers;
    double numbers = ui->numberCard->text().toDouble(&isNumbers);
    bool containsOnlyLetters = true;
// прізвище

    for(int i = 0; i < ui->Surname->text().length(); i++) {
        if(!ui->Surname->text().at(i).isLetter() && ui->Surname->text().at(i)!='\'') {
            containsOnlyLetters = false;
            break;
        }
    }
    if(!containsOnlyLetters) {
         QMessageBox::critical(this,"Помилка", "Прізвище не може містити символів або чисел.");
    }
    else if ( ui->Surname->text().isEmpty()){
         QMessageBox::critical(this,"Помилка", "Поле не може залишатись порожнім.");
    }
    else {tempSurname = ui->Surname->text(); count++;}

// номер карти
    if (!isNumbers){
        QMessageBox::critical(this,"Помилка", "Номер карти не може містити букв чи інших символів, лише числа.");
    }
   else if (ui->numberCard->text().length()!=16){
        QMessageBox::critical(this,"Помилка", "Номер карти складається з 16-ти чисел.");
    }
    else if (ui->numberCard->text() == obj1.getAccNumber() ||  ui->numberCard->text() == obj2.getAccNumber() || ui->numberCard->text() == obj3.getAccNumber() || ui->numberCard->text() == obj4.getAccNumber() || ui->numberCard->text() == obj5.getAccNumber() ){
        QMessageBox::critical(this,"Помилка", "Номер карти вже зайнятий.");
    }
    else {tempNumb = ui->numberCard->text(); count++;}

// баланс
    numbers = ui->startBalance->text().toDouble(&isNumbers);
    if ( ui->startBalance->text().isEmpty()){
        QMessageBox::critical(this,"Помилка", "Поле не може залишатись порожнім.");
    }
    else if (!isNumbers){
        QMessageBox::critical(this,"Помилка", "Баланс повинен складатись лише з чисел, без символів та валюти.");
    }
    else if (numbers>=2147483647){
      QMessageBox::critical(this,"Помилка", "Ви порушуєте правила нашого банку. Сума на балансі не повинна перевищувати 2.147.483.646 грн.");
    }
    else if (numbers<0){
      QMessageBox::critical(this,"Помилка", "Початковий внесок не може бути від'ємним.");
    }
    else {startBal = ui->startBalance->text().toInt(); count++; }

// проценти
    if (!(ui->perc_3->isChecked()) && !(ui->perc_5->isChecked()) && !(ui->perc_10->isChecked())){
      QMessageBox::critical(this,"Помилка", "Виберіть депозитний план (3%, 5% або 10%).");
    }
    if (ui->perc_3->isChecked()){tempPerc = 3; }
      if (ui->perc_5->isChecked()){tempPerc = 5;}
      if (ui->perc_10->isChecked()){tempPerc = 10;}

      if (count == 3) {
      QMessageBox::StandardButton a = QMessageBox::information(this, "Реєстрація", "Ви успішно зареєструвались!", QMessageBox::Ok);
      if (a) {hide();}
      }

}


void creatAcc::upgradeFile(QMap<int, Account>& bank, QString filename){
      if (obj1.getSurname()=="") obj1 = nullDates();
      if (obj2.getSurname()=="") obj2 = nullDates();
      if (obj3.getSurname()=="") obj3 = nullDates();
      if (obj4.getSurname()=="") obj4 = nullDates();
      if (obj5.getSurname()=="") obj5 = nullDates();
      bank[1]= obj1;
      bank[2]= obj2;
      bank[3]= obj3;
      bank[4]= obj4;
      bank[5]= obj5;
      QFile file (filename);
      if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      for (auto it = bank.begin(); it != bank.end(); ++it) {
            if (it.key()!=0)
            out << it.key() << " " << it.value().getSurname() << " " << it.value().getAccNumber() << " " << it.value().getPercent() << " " << it.value().getBalance() << "\n";
      }
      file.close();
      }
}



void creatAcc::startReg(QString fn, int obj){
      filename = fn;
      currentObj = obj;
      setModal(true);
      openFile(bank,filename);
      exec();
      if (obj == 1) obj1 = upgradeDates();
      else if (obj == 2) obj2 = upgradeDates();
      else if (obj == 3) obj3 = upgradeDates();
      else if (obj == 4) obj4 = upgradeDates();
      else if (obj == 5) obj5 = upgradeDates();
      upgradeFile(bank,filename);
}

Account creatAcc::upgradeDates(){
      Account obj;
      obj.setSurname(tempSurname);
      obj.setAccNumber(tempNumb);
      obj.setPercent(tempPerc);
      obj.setBalance(startBal);
      return obj;
}


Account creatAcc::nullDates(){
      Account obj;
      obj.setSurname("Null");
      obj.setAccNumber("0000000000000000");
      obj.setPercent(0);
      obj.setBalance(0);
      return obj;
}
void creatAcc::openFile(QMap<int, Account>& bank, QString filename){
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
