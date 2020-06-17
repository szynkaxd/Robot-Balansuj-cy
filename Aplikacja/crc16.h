#ifndef CRC16_H
#define CRC16_H

#include <QObject>

class Crc16 : public QObject
{
    Q_OBJECT
    unsigned short crc16;
public:
    explicit Crc16(QObject *parent = 0);
    void getCrc16();

signals:

public slots:
};

#endif // CRC16_H
