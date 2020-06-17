#include "rysunekkol.h"
#include <QtMath>
#include "connectdialog.h"

#define PROMIEN 50
#define GRUBOSC 3
#define MARGINES 10
#define ODSTEP 50
#define ANGLE 30



RysunekKol::RysunekKol(QWidget *parent) : QWidget(parent)
{
    qRegisterMetaType<Ramka>("CustomString1");
    this->startB.setX(200);
    this->startB.setY(60);
    this->startA.setX(60);
    this->startA.setY(60);
}

/*
void RysunekKol::registrationReadDataSignal(ConnectDialog *conenectDialog){
    connect(conenectDialog, SIGNAL(dataReady(Ramka)), this, SLOT(newData(Ramka)));
}
*/

void RysunekKol::RysujKolo(QPainter& Rysownik)
{
    QPen Piorko(Rysownik.pen());

    Piorko.setWidth(GRUBOSC);
    Rysownik.setPen(Piorko);

    Rysownik.drawEllipse(MARGINES,MARGINES,PROMIEN*2,PROMIEN*2);
    Rysownik.drawEllipse(PROMIEN*2 + ODSTEP,MARGINES,PROMIEN*2,PROMIEN*2);
}

void RysunekKol::RysujPromien(QPainter& Rysownik)
{
    QPen Piorko(Rysownik.pen());

    Piorko.setWidth(GRUBOSC);
    Rysownik.setPen(Piorko);
    Rysownik.drawLine(startA,KatNaXY(1));
    Rysownik.drawLine(startB,KatNaXY(2));

}

QPoint RysunekKol::KatNaXY(int AorB){
    QPoint pkt;
    double degrees = 0;
    double radians = 0;
    if(AorB == 1){
        degrees = rotateA;
        radians = qDegreesToRadians(degrees);
        pkt.setX(qCos(radians)*PROMIEN+startA.x());
        pkt.setY(qSin(radians)*PROMIEN+startA.y());
    }
    if(AorB == 2){
        degrees = rotateB;
        radians = qDegreesToRadians(degrees);
        pkt.setX(qCos(radians)*PROMIEN+startB.x());
        pkt.setY(qSin(radians)*PROMIEN+startB.y());
    }

    return pkt;
}




void RysunekKol::newData(Ramka ramka)
{
    if (ramka.getDirA() == 1) rotateA += ANGLE;
    if (ramka.getDirA() == 2) rotateA -= ANGLE;

    if (ramka.getDirB() == 1) rotateB += ANGLE;
    if (ramka.getDirB() == 2) rotateB -= ANGLE;

    rotateA %= 360;
    rotateB %= 360;
    update();
}



void RysunekKol::paintEvent(QPaintEvent *event)
{

    QPainter Rysownik(this);

    this->RysujKolo(Rysownik);
    this->RysujPromien(Rysownik);


}

