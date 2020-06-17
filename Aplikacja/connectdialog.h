#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include "crc.h"
#include "ramka.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();
     Ramka *ramka;
     void sendMessageToDevice(QString);
     QSerialPort *device;

private slots:
    void on_pushButtonFind_clicked();

    void on_pushButtonConnect_clicked();

    void readFromPort();

 //   void GetPIDslot();

signals:
    void dataReady(Ramka ramka);
    void NewPIDsignal(Ramka ramka);

private:
    Ui::ConnectDialog *ui;

    void AddToStatus(QString message);

};

#endif // CONNECTDIALOG_H
