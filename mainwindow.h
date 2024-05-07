#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void con_butt(QString);
        void port_disable();
        void lock_signal(bool);

public slots:
     void set_port_list(QList<QString>);     //Установка списка портов
     void set_con_status(bool);              //индикатор подключения
     void set_res_dat(QString);             //Вывод текстовой строки
     //void set_lock_status(bool);
public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
             //Установка подключения порта
    QString get_current_item();             //Выдача имени выбранного порта

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lock_butt_clicked();

    void on_get_sens_butt_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
