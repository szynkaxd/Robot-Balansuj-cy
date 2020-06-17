#include "pid.h"
#include "ui_pid.h"

PID::PID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PID)
{
    ui->setupUi(this);
}

PID::~PID()
{
    delete ui;
}

void PID::on_pushButton_read_clicked()
{
    ui->textEdit_P->clear();
    ui->textEdit_I->clear();
    ui->textEdit_D->clear();

    ui->textEdit_P->insertPlainText(connectdialog_ptr->ramka->getP());
    ui->textEdit_I->insertPlainText(connectdialog_ptr->ramka->getI());
    ui->textEdit_D->insertPlainText(connectdialog_ptr->ramka->getD());

    ui->textEdit_P->repaint();
    ui->textEdit_I->repaint();
    ui->textEdit_D->repaint();
}

void PID::on_pushButton_save_clicked()
{
    QString tmp_P, tmp_I, tmp_D, command;
    tmp_P = ui->textEdit_P->toPlainText();
    tmp_I = ui->textEdit_I->toPlainText();
    tmp_D = ui->textEdit_D->toPlainText();

command = "5";
command += tmp_P;
command += tmp_I;
command += tmp_D;

connectdialog_ptr->sendMessageToDevice(command);

}
