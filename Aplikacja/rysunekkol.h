#ifndef RYSUNEKKOL_H
#define RYSUNEKKOL_H

#include <QWidget>
#include <QPainter>
#include "ramka.h"
#include "connectdialog.h"
#include <QPoint>

Q_DECLARE_METATYPE(Ramka)

class RysunekKol : public QWidget
{
    Q_OBJECT
    int rotateA = 0;
    int rotateB = 0;
    QPoint startA, startB;


public:
   // explicit RysunekKol(QWidget *parent = nullptr);
    RysunekKol(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    void RysujKolo(QPainter&);
    void RysujPromien(QPainter& Rysownik);
    QPoint KatNaXY(int);
  //  void registrationReadDataSignal(ConnectDialog *conenectDialog);

public slots:
    void newData(Ramka);

signals:
};

#endif // RYSUNEKKOL_H
