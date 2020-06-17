#include <avr/io.h>
#define BAUDRATE 9600
#define UBRR_VALUE 129
#define d_SEND_DATA_COMPLETE !(UCSR0A&(1<<UDRE0))
#define d_RECEIVE_DATA_COMPLETE !(UCSR0A&(1<<RXC0))

void USART_INITIALIZATION(void);
void SEND_BYTE(uint8_t b8_data);
uint8_t USART0ReceiveByte();
void Write_Buff(unsigned char *buff, uint8_t lenght);
