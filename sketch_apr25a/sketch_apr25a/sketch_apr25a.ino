#include <FastCRC_cpu.h>
#include <FastCRC.h>
#include <FastCRC_tables.h>
#include <util/crc16.h>
#define POLY 0x8408


const uint8_t ledPin = LED_BUILTIN;
uint32_t interval = 1000;
uint32_t previousMillis = 0;

double AcX = 1.1;
double AcY = 2.2;
unsigned short crc;

unsigned short crc16(char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8; 
                 i++, data >>= 1)
            {
                  if ((crc & 0xFFFF) ^ (data & 0x906E))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

char buf[] = "123";

  Serial.println(crc16(buf, sizeof(buf)),HEX);

  
}
 
void loop() {
  String ramka = "X ";
  ramka += AcX;
  ramka += " ";
  ramka += AcY;
  ramka += " ";
  ramka += crc;
  ramka += " @ ";
//    Serial.print(ramka);
    AcX += 1;
    AcY += 1;
  delay(1000);
}
 
void serialEvent() {
  while (Serial.available()) {
    char state = (char)Serial.read();
    if(state == '0') {
      digitalWrite(ledPin, 0);
    } else if(state == '1') {
      digitalWrite(ledPin, 1);
    }
 
    Serial.println("Potwierdzam odbior. Status diody = " + String(state));
  }
}
