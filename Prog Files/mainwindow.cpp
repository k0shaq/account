#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileedit.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <string>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("National Bank");
    ui->listWidget->addItem("Privat Bank");
    ui->listWidget->addItem("Bank Ukraine");
    ui->listWidget->addItem("Copy");

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
   QListWidgetItem* selectedItem = ui->listWidget->currentItem();
   QString fille = selectedItem->text(), filename;
   QString currentPath = QDir::currentPath();
   if (fille == "National Bank") filename = currentPath + "/FILE_1.txt";
   else if (fille == "Privat Bank") filename = currentPath + "/FILE_2.txt";
   else if (fille == "Bank Ukraine") filename = currentPath + "/FILE_3.txt";
   else if (fille == "Copy") filename = currentPath + "/COPY.txt";
   QFile file(filename);
   bool isEmpty;
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       if (file.size() == 0) {
          isEmpty = true;
       } else {
          isEmpty = false;
       }

       if (isEmpty){
          FileEdit FilEd;
          hide();
          FilEd.startApp(filename);
       }
       else {
          FileEdit FilEd;
          hide();
          FilEd.connectApp(filename);
       }
       file.close();
   } else {
       QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл");
   }
}

void MainWindow::on_copyButton_clicked()
{
   QString currentPath = QDir::currentPath();
   QListWidgetItem* selectedItem = ui->listWidget->currentItem();
   QString fille = selectedItem->text();
     QString filename_source, filename_copy;
   if (fille == "Copy") {QMessageBox::critical(nullptr,"Помилка", "Ви не можете копіювати файл сам у себе");}
   else {

   if (fille == "National Bank") filename_source = currentPath + "/FILE_1.txt";
   else if (fille == "Privat Bank") filename_source = currentPath + "/FILE_2.txt";
   else if (fille == "Bank Ukraine") filename_source = currentPath + "/FILE_3.txt"; }
   filename_copy = currentPath + "/COPY.txt";

   QFile sourceFile(filename_source);
   QFile copyFile(filename_copy);
   QByteArray buffer;
   if (!sourceFile.exists() || !sourceFile.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr,"Помилка", "Не вдалося відкрити або знайти вихідний файл");
   }
    else if (!copyFile.open(QIODevice::WriteOnly)) {
   sourceFile.close();
   QMessageBox::critical(nullptr,"Помилка", "Не вдалося відкрити файл для запису");
   }
   while (!(buffer = sourceFile.read(4096)).isEmpty()) {
   if (copyFile.write(buffer) == -1) {
          sourceFile.close();
          copyFile.close();
    QMessageBox::critical(nullptr,"Помилка", "Помилка запису в файл");
   }
   }
if (copyFile.size()!=0)
   QMessageBox::information(nullptr, "Успішно", "Файл успішно скопійовано.");


sourceFile.close();
copyFile.close();
}


void MainWindow::on_clearFile_button_clicked()
{
QListWidgetItem* selectedItem = ui->listWidget->currentItem();
QString fille = selectedItem->text(), filename;
QString currentPath = QDir::currentPath();
if (fille == "National Bank") filename = currentPath + "/FILE_1.txt";
else if (fille == "Privat Bank") filename = currentPath + "/FILE_2.txt";
else if (fille == "Bank Ukraine") filename = currentPath + "/FILE_3.txt";
else if (fille == "Copy") filename = currentPath + "/COPY.txt";
QFile file(filename);
if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
   file.close();
}
}

