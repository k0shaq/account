#include "fileedit.h"
#include "ui_fileedit.h"
#include "account.h"
#include <QMessageBox>
#include "creatacc.h"
#include "cabinet.h"
#include <QTextStream>
#include <QFile>
#include <QMap>
#include "mainwindow.h"
using namespace std;

FileEdit::FileEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileEdit)
{
    ui->setupUi(this);
}

FileEdit::~FileEdit()
{
    delete ui;
}

void FileEdit::startApp(QString fn){
   filename = fn;
   setModal(true);
   exec();
}

void FileEdit::connectApp(QString fn){
   filename = fn;
   setModal(true);
   openFile(bank,filename);
   ui->button_acc1->setText(obj1.getSurname());
   ui->button_acc2->setText(obj2.getSurname());
   ui->button_acc3->setText(obj3.getSurname());
   ui->button_acc4->setText(obj4.getSurname());
   ui->button_acc5->setText(obj5.getSurname());
   exec();
}

void FileEdit::openFile(QMap<int, Account>& bank, QString filename){
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

void FileEdit::setTextButton(){
        ui->button_acc1->setText(obj1.getSurname());
        ui->button_acc2->setText(obj2.getSurname());
        ui->button_acc3->setText(obj3.getSurname());
        ui->button_acc4->setText(obj4.getSurname());
        ui->button_acc5->setText(obj5.getSurname());
}
void FileEdit::on_button_acc1_clicked()
{
   if (ui->button_acc1->text()=="Null" || ui->button_acc1->text()=="0" || ui->button_acc1->text()==" "){
       creatAcc reg;
       reg.startReg(filename, 1);
       openFile(bank,filename);
       setTextButton();
   }
   else {
       cabinet cabWindow;
       cabWindow.startCab(filename, 1);
       openFile(bank,filename);
       setTextButton();

   }
}

void FileEdit::on_button_acc2_clicked()
{
   if (ui->button_acc2->text()=="Null" || ui->button_acc2->text()=="0" || ui->button_acc2->text()==" "){
       creatAcc reg;
       reg.startReg(filename, 2);
       openFile(bank,filename);
       setTextButton();
   }
   else {
       cabinet cabWindow;
       cabWindow.startCab(filename, 2);
       openFile(bank,filename);
       setTextButton();

   }
}

void FileEdit::on_button_acc3_clicked()
{
   if (ui->button_acc3->text()=="Null" || ui->button_acc3->text()=="0" || ui->button_acc3->text()==" "){
       creatAcc reg;
       reg.startReg(filename, 3);
       openFile(bank,filename);
       setTextButton();
   }
   else {
       cabinet cabWindow;
       cabWindow.startCab(filename, 3);
       openFile(bank,filename);
       setTextButton();

   }
}

void FileEdit::on_button_acc4_clicked()
{
   if (ui->button_acc4->text()=="Null" || ui->button_acc4->text()=="0" || ui->button_acc4->text()==" "){
       creatAcc reg;
       reg.startReg(filename, 4);
       openFile(bank,filename);
       setTextButton();
   }
   else {
       cabinet cabWindow;
       cabWindow.startCab(filename, 4);
       openFile(bank,filename);
       setTextButton();

   }
}

void FileEdit::on_button_acc5_clicked()
{
   if (ui->button_acc5->text()=="Null" || ui->button_acc5->text()=="0" || ui->button_acc5->text()==" "){
       creatAcc reg;
       reg.startReg(filename, 5);
       openFile(bank,filename);
       setTextButton();
   }
   else {
       cabinet cabWindow;
       cabWindow.startCab(filename, 5);
       openFile(bank,filename);
       setTextButton();

   }
}


void FileEdit::on_openMain_button_clicked()
{
    MainWindow* windy = new MainWindow;
    hide();
    windy->show();
}

