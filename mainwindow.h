#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFind_clicked();
    void addToLogs(QString message);
    void on_pushButtonConnect_clicked();
    void readFromPort();
    void sendMessageToDevice(QString message);

    void on_pushButtonLedOn_clicked();

    void on_pushButtonLedOff_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *device;
};
#endif // MAINWINDOW_H
