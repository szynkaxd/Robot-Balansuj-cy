#include "graphsdialog.h"
#include "ui_graphsdialog.h"

Graphsdialog::Graphsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphsdialog)
{
    ui->setupUi(this);
    ui->plot_acc->addGraph();
    ui->plot_acc->graph()->setLineStyle(QCPGraph::lsLine);

    ui->plot_gyro->addGraph();
    ui->plot_gyro->graph()->setLineStyle(QCPGraph::lsLine);
}

Graphsdialog::~Graphsdialog()
{
    delete ui;
}

void Graphsdialog::addPoint(double acc_x, double acc_y, double gyro_x, double gyro_y)
{
    qvacc_x.append(acc_x);
    qvacc_y.append(acc_y);

    qvgyro_x.append(gyro_x);
    qvgyro_y.append(gyro_y);
}

void Graphsdialog::clearData()
{
    ui->plot_acc->graph()->data()->clear();
    this->qvacc_x.clear();
    this->qvacc_y.clear();
    ui->plot_acc->replot();
    ui->plot_acc->update();

    ui->plot_gyro->graph()->data()->clear();
    this->qvgyro_x.clear();
    this->qvacc_y.clear();
    ui->plot_gyro->replot();
    ui->plot_gyro->update();
}

void Graphsdialog::plot()
{
    ui->plot_acc->graph()->setData(qvacc_x, qvacc_y);
    ui->plot_gyro->graph()->setData(qvgyro_x, qvgyro_y);
    ui->plot_acc->graph()->rescaleAxes(true);
    ui->plot_gyro->graph()->rescaleAxes(true);
    ui->plot_acc->replot();
    ui->plot_acc->update();
    ui->plot_gyro->replot();
    ui->plot_gyro->update();
    this->repaint();
}

void Graphsdialog::NewGraphsData(Ramka frame)
{
    this->addPoint(frame.getAccX(), frame.getAccY(), frame.getGyroX(), frame.getGyroY());
    this->plot();
}

void Graphsdialog::on_pushButton_clicked()
{
    this->clearData();
}
