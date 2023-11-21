#ifndef FILEEDIT_H
#define FILEEDIT_H
#include "account.h"
#include <QDialog>

namespace Ui {
class FileEdit;
}

class FileEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FileEdit(QWidget *parent = nullptr);
    ~FileEdit();
    QMap<int, Account> bank;
    Account obj1;
    Account obj2;
    Account obj3;
    Account obj4;
    Account obj5;
    QString filename;
    void startApp(QString fn);
    void connectApp(QString fn);
    void openFile(QMap<int, Account>& bank, QString filename);
    void setTextButton();

private:
    Ui::FileEdit *ui;

private slots:
    void on_button_acc1_clicked();
    void on_button_acc2_clicked();
    void on_button_acc3_clicked();
    void on_button_acc4_clicked();
    void on_button_acc5_clicked();
    void on_openMain_button_clicked();
};

#endif // FILEEDIT_H
