#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    k = 0;
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(openClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openClicked()
{
    QFileDialog dlg;

    try{
        QFile file(dlg.getOpenFileName(this, "Open Dialog", "", "*.fb2"));
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, "error", "file is not correct");
            return;
        }

        QString xml = QString::fromUtf8(file.readAll());

        if(xml[1] == '?')
           xml = xml.mid(xml.indexOf("?>") + 2, xml.size() - xml.indexOf("?>") - 2);


        while(xml.indexOf('\r') != -1 || xml.indexOf('\n') != -1)
        {
            int i = xml.indexOf('\r');
            xml.remove(i, 1);

            i = xml.indexOf('\n');
            xml.remove(i, 1);

        }


        tree obj(xml);
        QString body = obj.body__();
        const int lim = 2500;
        while(body.indexOf("</p>") > -1)
        {
            QString str;
            int h = 0;
            while(h != 15)
            {
                int j = body.indexOf("</p>");
                if(str.size() > lim)
                    break;
                str += body.mid(0, j + 4);
                body = body.mid(j + 4, body.size() - j -4);
                h++;
            }
            vec.push_back(str);
        }

        ui->textBrowser->setHtml(vec[0]);
        QString lbl = QString::number((k+1)) + '/' + QString::number(vec.size());
        ui->label->setText(lbl);
        file.close();
    }
    catch(const std::exception & ex){
        QMessageBox::information(this, "error", QString(ex.what()));
    }
}
void MainWindow::on_pushButton_clicked()
{
   if(!vec.empty())
   {
     if(k != vec.size() - 1)
      ui->textBrowser->setHtml(vec[++k]);
     QString lbl = QString::number((k+1)) + '/' + QString::number((vec.size() + 1));
     ui->label->setText(lbl);
   }
   else
   {
     QMessageBox::information(this, "error", "book is not open");
   }
}



void MainWindow::on_pushButton_2_clicked()
{
    if(!vec.empty())
   {
     if(k != 0)
      ui->textBrowser->setHtml(vec[--k]);
     QString lbl = QString::number((k+1)) + '/' + QString::number((vec.size() + 1));
     ui->label->setText(lbl);
   }
   else
   {
      QMessageBox::information(this, "error", "book is not open");
   }
}
