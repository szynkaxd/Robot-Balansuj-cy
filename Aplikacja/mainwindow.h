#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectdialog.h"
#include "ramka.h"
#include "rysunekkol.h"
#include "pid.h"
#include "graphsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    //ActionThread *actionThread;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();

    void upDateBattery(Ramka);

    void updateValues(Ramka);

    void on_pushButton_forward_pressed();

    void on_pushButton_backward_pressed();

    void on_pushButton_right_pressed();

    void on_pushButton_left_pressed();

    void on_actionPID_triggered();

    void on_pushButton_graphs_clicked();

private:
    int battery1_state,battery2_state;
    QPixmap battery0, battery1, battery2, battery3;
    Ui::MainWindow *ui;
    ConnectDialog *connectdialog;
    PID *PidDialog;
    RysunekKol * rysunekKol;
    Graphsdialog *graphsdialog;
    void BatteryInit();
    void ValuesInit();
};
#endif // MAINWINDOW_H
