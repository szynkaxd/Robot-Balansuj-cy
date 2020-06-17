#include "ramka.h"
#include <QDebug>



void Ramka::AddData(QString DirA,QString DirB,QString PwmA,QString PwmB,
 QString AccX,QString AccY,QString GyroX,QString GyroY,QString Battery,QString P,QString I,QString D){

    this->DirA = DirA.toInt();
    this->DirB = DirB.toInt();
    this->Battery = Battery.toInt();
    this->PwmA = PwmA.toInt();
    this->PwmB = PwmB.toInt();

    this->AccX = AccX.toDouble();
    this->AccY = AccY.toDouble();
    this->GyroX = GyroX.toDouble();
    this->GyroY = GyroY.toDouble();
    this->P = P.toDouble();
    this->I = I.toDouble();
    this->D = D.toDouble();
}

QString Ramka::Wypisz(){

    QString ramka = "";
    QString spacja = " ";
    ramka += "DirA= ";
    ramka += QString::number(this->DirA);
      ramka += spacja;
      ramka += "DirB= ";
     ramka += QString::number(this->DirB);
      ramka += spacja;
      ramka += "PwmA= ";
     ramka += QString::number(this->PwmA);
      ramka += spacja;
      ramka += "PwmB= ";
     ramka += QString::number(this->PwmB);
      ramka += spacja;
      ramka += "AccX= ";
     ramka += QString::number(this->AccX);
      ramka += spacja;
      ramka += "AccY= ";
     ramka += QString::number(this->AccY);
      ramka += spacja;
      ramka += "GyroX= ";
     ramka += QString::number(this->GyroX);
      ramka += spacja;
      ramka += "GyroY= ";
     ramka += QString::number(this->GyroY);
      ramka += spacja;
      ramka += "Battery= ";
     ramka += QString::number(this->Battery);
     ramka += spacja;
     ramka += "P= ";
    ramka += QString::number(this->P);
    ramka += spacja;
    ramka += "I= ";
   ramka += QString::number(this->I);
   ramka += spacja;
   ramka += "D= ";
  ramka += QString::number(this->D);

    return ramka;

}

QString Ramka::getP()
{

    return QString::number(this->P);
}

QString Ramka::getI()
{
    return QString::number(this->I);
}

QString Ramka::getD()
{
    return QString::number(this->D);
}

double Ramka::getAccX()
{
    return this->AccX;
}

double Ramka::getAccY()
{
    return this->AccY;
}

double Ramka::getGyroX()
{
    return this->GyroX;
}

double Ramka::getGyroY()
{
    return this->GyroY;
}

int Ramka::getDirA()
{
    return this->DirA;
}

int Ramka::getDirB()
{
    return this->DirB;
}

int Ramka::getBattery()
{
    return this->Battery;
}
