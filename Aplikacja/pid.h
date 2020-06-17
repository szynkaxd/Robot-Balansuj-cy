#ifndef PID_H
#define PID_H

#include <QDialog>
#include <QString>
#include "connectdialog.h"

namespace Ui {
class PID;
}

class PID : public QDialog
{
    Q_OBJECT

public:
    explicit PID(QWidget *parent = nullptr);
    ~PID();
    ConnectDialog *connectdialog_ptr;

private slots:
    void on_pushButton_read_clicked();

    void on_pushButton_save_clicked();

signals:

private:
    Ui::PID *ui;

};

#endif // PID_H
