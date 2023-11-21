#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_copyButton_clicked();

    void on_clearFile_button_clicked();


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
