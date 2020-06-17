#ifndef RAMKA_H
#define RAMKA_H

#include <QString>
#include <QWidget>

class Ramka {

private:
    int DirA, DirB, PwmA, PwmB, Battery;
    double AccX, AccY, GyroX, GyroY, P, I, D;

public:
    void AddData(QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString);
    QString Wypisz();
    QString getP();
    QString getI();
    QString getD();
    double getAccX();
    double getAccY();
    double getGyroX();
    double getGyroY();
    int getDirA();
    int getDirB();
    int getBattery();

};

#endif // RAMKA_H
