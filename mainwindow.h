#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.h"
#include "dialog.h"
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<QString> vec;
    int k;

private slots:
   void openClicked();
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
