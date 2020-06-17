#ifndef GRAPHSDIALOG_H
#define GRAPHSDIALOG_H

#include <QDialog>
#include "ramka.h"


namespace Ui {
class Graphsdialog;
}

class Graphsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Graphsdialog(QWidget *parent = nullptr);
    ~Graphsdialog();
    void addPoint(double, double, double, double);
    void clearData();
    void plot();

private:
    Ui::Graphsdialog *ui;
    QVector<double> qvacc_x, qvacc_y, qvgyro_x, qvgyro_y;

private slots:
    void NewGraphsData(Ramka);
    void on_pushButton_clicked();
};

#endif // GRAPHSDIALOG_H
