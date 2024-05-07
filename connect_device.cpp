#include "connect_device.h"
#include <QSerialPort>
#include <QMessageBox>

port_master::port_master()
{
    port_list = QSerialPortInfo::availablePorts();
    scan_period = new QTimer();
    scan_period->start(100);
     port = nullptr;
    connect(scan_period, SIGNAL(timeout()),         //Сигнал таймера
            this, SLOT(ports_search()));
    /**/
    connect(this,
            &port_master::conn_broken,
            this,
            &port_master::port_cracked
            );
}

port_master::~port_master()
{
    delete port;
    scan_period->stop();
    delete scan_period;
}

/**/
QList<QString> port_master::get_ports_names()
{
    QList<QString> tmp;
    for(QSerialPortInfo item : port_list)
    {
        tmp.append(item.portName());
    }
    return tmp;
}

void port_master::ports_search()
{
    QStringList str;
    QList<QSerialPortInfo> temp = QSerialPortInfo::availablePorts();
    bool flag = false;

    for(QSerialPortInfo item : temp)
    {
        str<<item.portName();
    }

    for(QSerialPortInfo item : port_list)
    {
        if(!(str.contains(item.portName())))    //Если в новом списке не обнаружится хотя бы один порт из старого
        {
            flag=true;                       //установить флаг
        }
    }
    if((flag)                               //Если не совпадают имена нового списка портов и старого
       ||(temp.count()!=port_list.count())) //или количество портов - обновить лист и подать сигнал
    {
        port_list.clear();
        port_list.append(temp);
        emit ports_changed(str);
    }

    if(port!=nullptr)
    {
        QString tmp(port->portName());
        bool st = str.contains(port->portName());
        if(!(str.contains(port->portName())))   //Если в новом списке текущего порта нет - разрываем соединение
        {
            emit conn_broken();
        }
    }

}

void port_master::ports_search1()
{
    QStringList str;
    QList<QSerialPortInfo> temp = QSerialPortInfo::availablePorts();
    bool flag = true;
    for(QSerialPortInfo item : temp)
    {
        str.join(item.portName());
    }
    str.sort();

    if(temp.count()!=port_list.count())                                 //В случае изменения наличия протов
       {
        port_list.clear();
        port_list.append(temp);

        for(QSerialPortInfo item : temp)
        {
            str.append(item.portName());

            if(port!=nullptr)
            {
                if(item.portName()==port->portName())                   //Если в новом списке текущего порта нет - разрываем соединение
                {
                    flag = false;
                }
            }
        }
        if(flag)
            emit conn_broken();
        emit ports_changed(str);
        }
}

void port_master::port_connect(QString str)
{
    if(port!=nullptr)                             //Удаление старых данных из указателя
    {
        if(port->isOpen())
            port->close();
        delete port;
    }

    port = new QSerialPort(str);

    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    if(port->open(QIODevice::ReadWrite))
    {
        connect(port,                                   //Сигнал с порта
                &QSerialPort::readyRead,
                this,
                &port_master::reseive_handler
                );
        emit port_open(true);

    }
    else
         emit port_open(false);


}

void port_master::reseive_handler()
{
    /**/
      char mass[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    QByteArray bytes(port->readAll());
    QString tmp;
    /**/
    for(int i=0; i<bytes.count();i++)
    {
        tmp.append("0x");
        tmp.append(mass[(bytes.at(i))>>4]);
        tmp.append(mass[(bytes.at(i))&0x0f]);
        tmp.append(' ');
    }
    emit text_reseive(tmp);//(QString(bytes));    //Преобразование байто в строку и вывод в textedit

}

void port_master::port_cracked()
{
        port->close();
        delete port;
        port = nullptr;
        emit port_open(false);
}

void port_master::lock_drive(bool val)
{

    char tmp;
    /*
    QMessageBox msg;
    msg.setWindowTitle(" ");
    msg.setText("Порт не открыт");

    if(port!=nullptr)
    {
        if(port->isOpen())
        {
            if(val)
            {tmp=lock_open;}
             else
            {tmp=lock_close;}

                if(port->write(&tmp,1)<0)
                {
                    msg.setText("Произошла ошибка передачи");
                    msg.exec();
                }
        }
        else
            msg.exec();
    }else
        msg.exec();
*/
    if(val)
    {tmp = lock_open;}
     else
    {tmp=lock_close;}

    port_write(&tmp,1);
}

void port_master::sens_req()
{
    char tmp = get_sensors;
        port_write(&tmp,1);
}


void port_master::port_write(char* dat, int len)
{
    char tmp;
    QMessageBox msg;
    msg.setWindowTitle(" ");
    msg.setText("Порт не открыт");

    if(port!=nullptr)
    {
        if(port->isOpen())
        {
            if(port->write(dat,len)<0)
            {
                msg.setText("Произошла ошибка передачи");
                msg.exec();
            }
        }
        else
            msg.exec();
    }else
        msg.exec();
}













