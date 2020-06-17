#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BatteryInit();

    ui->textEdit_accX->setReadOnly(true);
    ui->textEdit_accY->setReadOnly(true);
    ui->textEdit_gyroX->setReadOnly(true);
    ui->textEdit_gyroY->setReadOnly(true);

    connectdialog = new ConnectDialog(this);

    graphsdialog = new Graphsdialog(this);

    PidDialog = new PID(this);
    PidDialog->connectdialog_ptr = connectdialog;

    rysunekKol = new RysunekKol(this);
    rysunekKol->setGeometry(20,70,260,120);

    connect(connectdialog, SIGNAL(dataReady(Ramka)), rysunekKol, SLOT(newData(Ramka)));
    connect(connectdialog, SIGNAL(dataReady(Ramka)), graphsdialog, SLOT(NewGraphsData(Ramka)));
    connect(connectdialog, SIGNAL(dataReady(Ramka)), this, SLOT(updateValues(Ramka)));
    connect(connectdialog, SIGNAL(dataReady(Ramka)), this, SLOT(upDateBattery(Ramka)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionConnect_triggered()
{
    connectdialog->show();
}

void MainWindow::on_actionPID_triggered()
{
    PidDialog->show();
}

void MainWindow::upDateBattery(Ramka frame)
{
    QString lableText ="";
    double batteryValue = 0;

    if(frame.getBattery() < 141 && battery1_state != 0){
        battery1_state = 0;
        ui->label_battery1_icon->setPixmap(battery0);
    }

    if(frame.getBattery() >= 141 && frame.getBattery() < 179  && battery1_state != 1){
        battery1_state = 1;
        ui->label_battery1_icon->setPixmap(battery1);
    }

    if(frame.getBattery() >= 179 && frame.getBattery() < 217  && battery1_state != 2){
        battery1_state = 2;
        ui->label_battery1_icon->setPixmap(battery2);
    }

    if(frame.getBattery() >= 217 && frame.getBattery() < 256  && battery1_state != 3){
        battery1_state = 3;
        ui->label_battery1_icon->setPixmap(battery3);
    }

    batteryValue = (frame.getBattery() - 103);
    batteryValue /= 152;
    batteryValue *= 100;
    batteryValue = (int)batteryValue;
    lableText = QString::number(batteryValue);
    lableText += "%";
    ui->label_battery1_value->setText(lableText);
    this->repaint();

}

void MainWindow::updateValues(Ramka frame)
{
    this->ui->textEdit_accX->clear();
    this->ui->textEdit_gyroX->clear();
    this->ui->textEdit_accY->clear();
    this->ui->textEdit_gyroY->clear();

    this->ui->textEdit_accY->append(QString::number(frame.getAccY()));
    this->ui->textEdit_gyroY->append(QString::number(frame.getGyroY()));
    this->ui->textEdit_accX->append(QString::number(frame.getAccX()));
    this->ui->textEdit_gyroX->append(QString::number(frame.getGyroX()));

    this->ui->textEdit_accX->repaint();

}

void MainWindow::BatteryInit()
{
    battery1_state = 0;

    battery0.load(":/images/battery_0.png");
    battery1.load(":/images/battery_1.png");
    battery2.load(":/images/battery_2.png");
    battery3.load(":/images/battery_3.png");

    ui->label_battery1_icon->setScaledContents(true);
    ui->label_battery1_icon->setPixmap(battery0);
    ui->label_battery1_value->setText("0%");
}


void MainWindow::on_pushButton_forward_pressed()
{
    connectdialog->sendMessageToDevice("1");
}

void MainWindow::on_pushButton_backward_pressed()
{
    connectdialog->sendMessageToDevice("2");
}

void MainWindow::on_pushButton_right_pressed()
{
    connectdialog->sendMessageToDevice("3");
}

void MainWindow::on_pushButton_left_pressed()
{
    connectdialog->sendMessageToDevice("4");
}

void MainWindow::on_pushButton_graphs_clicked()
{
     graphsdialog->show();
}
