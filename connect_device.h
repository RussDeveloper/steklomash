#ifndef CONNECT_DEVICE_H
#define CONNECT_DEVICE_H
/**/
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QObject>

//Преамбулы посылок для передачи компьютеру

#define change_sensors		0x30		//оповещение об изменении сигналов на сенсорах
#define sensors_condition	0x31		//Передача сигналов с сенсоров
#define RFID_event			0x40		//передача данных считанной карты
#define empty_event			0x20		//Пустая посылка для проверки наличия подключения

//Преамбулы для приема команд от компьютера

#define handshake			0x25		//Сигнал о том, что предыдущая посылка принята удачно
#define get_sensors			0x60		//Команда запроса состояний сенсоров
#define lock_open			0x70		//Команда "Открыть замок"
#define lock_close			0x71		//Команда "Закрыть замок"

class port_master: public QObject
{
    Q_OBJECT
private:
    QList<QSerialPortInfo> port_list;
    QTimer *scan_period;
    QSerialPort *port;

    void port_write(char*, int);

public slots:
    void port_connect(QString);
    void port_cracked();
    void lock_drive(bool);
    void sens_req();
private slots:
    void ports_search();
    void ports_search1();
    void reseive_handler();

signals:
    void ports_changed(QList<QString>);
    void port_open(bool);
    void text_reseive(QString);
    void conn_broken();



public:
    QList<QString> get_ports_names();
    port_master();
    ~port_master();
    bool con_ok;                //флаг наличия соединения
};

#endif // CONNECT_DEVICE_H
