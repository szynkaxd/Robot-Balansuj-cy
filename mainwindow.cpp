#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crc8.h"
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonFind_clicked()
{
    this->addToLogs("szukam urządzeń");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBoxDevices->clear();
    for(int i = 0; i < devices.count(); i++) {
        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + devices.at(i).description());
        ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
}

void MainWindow::addToLogs(QString message)
{
    QString CurrentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(CurrentDateTime + "\t" + message);
    ui->textEditLogs->update();
}

void MainWindow::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0) {
        this->addToLogs("Nie wykryto rzadnych urządzeń!");
        return;
    }
    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    this->device->setPortName(portName);
    if(!device->isOpen()){
        if(device->open(QSerialPort::ReadWrite)) {
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            this->addToLogs("Otwarto port szeregowy.");

            //CONNECT:
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        }
        else {
            this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    }
    else {
        this->addToLogs("Połączenie na tym porcie jest już otwarte.");
    }
}

void MainWindow::readFromPort()
{
//   while(this->device->canReadLine()) {
//       QString line = this->device->readLine();
//       QString terminator = "@";
//       int pos = line.indexOf(terminator);
//       this->addToLogs(line.left(pos));
//   }

    QString Ramka;
    double AccX;
    QByteArray data = this->device->readAll();
    qDebug() << "Data: " << data;
    QString buffor = data;
    qDebug() << "Bufor: " << buffor;
    QStringList BuforList = buffor.split(" ");
    Ramka = "bedziedzialac";
    qDebug() << Ramka;
    qDebug() << Ramka.size();
    qDebug() << "CRC: " << crc16_ccitt(Ramka.toUtf8().constData(), Ramka.size());

    for(int i =0 ; i < BuforList.size();i++)
    {
        if(BuforList.at(i) == "X" && i+4 <= BuforList.size())
        {
//            qDebug() << "AccX = " << BuforList.at(i+1);
//            this->addToLogs("AccX = " + BuforList.at(i+1));
//            AccX = BuforList.at(i+1).toDouble();
//           AccX += 0.2;
//           qDebug() << AccX;
            for(int j=1 ; j < 3 ; ++j){

            }
        }

    }


}

void MainWindow::sendMessageToDevice(QString message)
{
    if(this->device->isOpen() && this->device->isWritable()) {
        this->addToLogs("Wysyłam do urządzenia: "+ message);
        this->device->write(message.toStdString().c_str());
    }
    else {
        this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty.");
    }
}

void MainWindow::on_pushButtonLedOn_clicked()
{
    this->sendMessageToDevice("1");
}


void MainWindow::on_pushButtonLedOff_clicked()
{
    this->sendMessageToDevice("0");
}
