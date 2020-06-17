#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "ramka.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    this->device = new QSerialPort(this);

    ui->lineEditStatus->setReadOnly(true);

    ramka = new Ramka;
}

ConnectDialog::~ConnectDialog()
{
    delete ramka;
    delete ui;
}

void ConnectDialog::on_pushButtonFind_clicked()
{
    this->AddToStatus("Zaktualizowano listę dostępnych urządzeń");

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBoxDevices->clear();
    for(int i = 0; i < devices.count(); i++) {
        ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
}

void ConnectDialog::AddToStatus(QString message)
{
    ui->lineEditStatus->clear();
    ui->lineEditStatus->insert(message);
    this->repaint();
}

void ConnectDialog::sendMessageToDevice(QString message)
{
    if(this->device->isOpen() && this->device->isWritable()) {
        this->device->write(message.toStdString().c_str());
        qDebug() << "Wysłałem: "<< message;
      } else {
        qDebug() << "Nie mogę wysłać wiadomości. Port nie jest otwarty!";
      }
}

void ConnectDialog::readFromPort()
{
    QString tmp = "";
    QByteArray data = this->device->readAll();  
    QString bufor = data;
    QStringList BuforList = bufor.split(" ");


    for(int i = 0 ; i < BuforList.size() ; i++)
    {
        if(BuforList.at(i) == ""){
            BuforList.removeAt(i);
        }
    }



    for(int i = 0 ; i < BuforList.size() ; i++)
    {
        if(BuforList.at(i) == ""){
            BuforList.removeAt(i);
        }

        if(BuforList.at(i) == "X" && i+13 <= BuforList.size()-1)
        {

        //    if(BuforList.at(i+14) == "@"){

                for(int j=1; j<13;j++){
                    tmp += BuforList.at(i+j);
                }
                if (crc16_ccitt(tmp.toUtf8().constData(), tmp.size()) == BuforList.at(i+13).toShort() || BuforList.at(i+13) == "0"){

                    ramka->AddData(BuforList.at(i+1),BuforList.at(i+2),BuforList.at(i+3),BuforList.at(i+4),BuforList.at(i+5),
                                  BuforList.at(i+6),BuforList.at(i+7),BuforList.at(i+8),BuforList.at(i+9),BuforList.at(i+10),BuforList.at(i+11),BuforList.at(i+12));
                    tmp="";
                    emit dataReady(*ramka);

                }
                else{
              //      qDebug() << "Błąd CRC";
                }
            //}
            //else {
            //    qDebug() << "Brak znaku końca ramki";
           // }
         }
        else {
          //  qDebug() << "Niepoprawna ramka";
        }
    }
}

void ConnectDialog::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0) {
        this->AddToStatus("Najpierwsz wyszukaj dostęne urządzenia!");
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

            this->AddToStatus("Otwarto port szeregowy.");

            //CONNECT:
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        }
        else {
            this->AddToStatus("Otwarcie portu szeregowego się nie powiodło!");
        }
    }
    else {
        this->AddToStatus("Połączenie na tym porcie jest już otwarte.");
    }
}
