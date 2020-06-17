#ifndef CRC_H
#define CRC_H


#include <QDebug>


unsigned short crc16_ccitt(const char *buf, int len);
#endif // CRC_H
