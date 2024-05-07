#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QObject>
#include <QTranslator>
#include <connect_device.h>
#include <QMessageBox>

class link_modules:public QObject
{
    //Q_OBJECT
   public:
    link_modules();
    ~link_modules();
    MainWindow *wind;
    port_master *mstr;

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "work1_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    link_modules *link_1 = new link_modules();

    link_1->wind->show();
    return a.exec();
}


link_modules::link_modules()
{
    wind = new MainWindow();
    mstr = new port_master();

    wind->set_port_list(mstr->get_ports_names());
/**/
    connect(mstr, &port_master::ports_changed,          //
                    wind,
                    &MainWindow::set_port_list
            );

    connect(mstr,&port_master::port_open,
            wind, &MainWindow::set_con_status
            );

    connect(mstr,&port_master::text_reseive,
            wind, &MainWindow::set_res_dat
            );

    connect(wind, &MainWindow::con_butt,
            mstr, &port_master::port_connect
                );
    connect(wind, &MainWindow::port_disable,
            mstr,&port_master::port_cracked

                );
    /**/
    connect(wind, &MainWindow::lock_signal,             //Связь клавиши включения/отключения замка
            mstr, &port_master::lock_drive              //с функцией
            );


}


link_modules::~link_modules()
{
    delete wind;
    delete mstr;
}















