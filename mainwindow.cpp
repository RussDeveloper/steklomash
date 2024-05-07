#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_port_list(QList<QString> list)
{

    QString tmp(ui->comboBox->currentText());           //запомнить действующее значение
    bool flag = false;
    int num = ui->comboBox->count();
    if(num>0){
    for(int i=0;i<ui->comboBox->count();i++)
    {
        if(ui->comboBox->itemText(i)==tmp.constData())
        {
            flag = true;
            num = i;
        }
       }
    }

    ui->comboBox->clear();
    ui->comboBox->addItems(list);

        if(flag)
        {
            for(int i=0;i<ui->comboBox->count();i++)
                if(ui->comboBox->itemText(i)==tmp.constData())
                {
                     ui->comboBox->setCurrentIndex(i);
                }

        }
        else
        {
            //emit (link_cracked);
        }



}

void MainWindow::set_con_status(bool stat)
{
    if(stat)
        ui->progressBar->setValue(1);
    else
        ui->progressBar->setValue(0);
}

QString MainWindow::get_current_item()
{
    return (ui->comboBox->currentText());
}


void MainWindow::set_res_dat(QString dat)
{
    ui->textEdit->append(dat);
}



void MainWindow::on_pushButton_clicked()            //Подключить порт
{
    emit con_butt(ui->comboBox->currentText());
}


void MainWindow::on_pushButton_2_clicked()          //Очистить
{
    ui->textEdit->clear();
}


void MainWindow::on_pushButton_3_clicked()          //Отключить порт
{
    emit port_disable();
}


void MainWindow::on_lock_butt_clicked()
{
    if(ui->lock_status->value()>0)
    {
        ui->lock_status->setValue(0);
        emit lock_signal(false);
    }
        else
    {
        ui->lock_status->setValue(1);
        emit lock_signal(true);
    }
}



void MainWindow::on_get_sens_butt_clicked()
{

}


























