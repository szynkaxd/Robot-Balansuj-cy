#include "uart.h"

void USART_INITIALIZATION(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE>>8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

void SEND_BYTE(uint8_t b8_data)
{
    while(d_SEND_DATA_COMPLETE) { ; }
    UDR0 = b8_data;
}

uint8_t USART0ReceiveByte()
{
    while(d_RECEIVE_DATA_COMPLETE){ ; }
    return UDR0;
}

void Write_Buff(unsigned char *buff, uint8_t lenght)
{
  uint8_t i = 0;
  for(i=0;i<lenght;i++)
  {
    SEND_BYTE(buff[i]);
  }
}
