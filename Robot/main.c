#define F_CPU 20000000UL
#define PI 3.14159
#define DT 0.01

#include <inttypes.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "mpu6050.h"
#include "mpu6050_reg.h"
#include "i2c.h"
#include "uart.h"


int main(void){


// testowanie logiki sterownika silników
	DDRD |= (1<<PD5) |(1<<PD4) |(1<<PD3) | (1<<PD2);
	DDRC |= (1<<PC0) | (1<<PC1);

//	PORTC |= (1<<PC0) | (0<<PC1);
//	PORTD |= (1<<PD5);
//PORTD |= (1<<PD3) | (1<<PD2) | (0<<PD4);

uint8_t tmp8[2];
int16_t acc_buff[3], gyro_buff[3], tmp16;

unsigned char onechar;
unsigned char buff[15] = "jestem robotem";
unsigned char buff2[15] = "chuj";
uint8_t ret, i;

double rollAcc, roll, pitchAcc, pitch;

uint8_t wartoscBezwzgledna;


USART_INITIALIZATION();
i2c_init();
mpu6050_init();

i2c_start(MPU6050_ADDRESS+I2C_WRITE);




//Obliczenie błędu żyroskopu


	while(1){
		//odczyt danych z czujników
		mpu6050_read_gyro_ALL(gyro_buff);
		mpu6050_read_accel_ALL(acc_buff);

		//Odczyt z żyroskopu przekształcony do [rad/s]
		pitch += ((double)gyro_buff[0]*(PI/180)/1000/32768);
		roll += ((double)gyro_buff[1]*(PI/180)/1000/32768);

		//Prosta metoda usuwania picków akcelerometru
		// maksymalna 16 bitowa wartość 32768 to 2g
		// ucinamy wszystkie wartości większ niż 2g i mniejsze niż 0.5g
		wartoscBezwzgledna = abs(acc_buff[0]+acc_buff[1]+acc_buff[2]);
		if (wartoscBezwzgledna > 8192 && wartoscBezwzgledna < 32768){

			//Obrót w okół OX -> wektor wzdłóż OY
			pitchAcc = atan2f((double)acc_buff[1], (double)acc_buff[2]) * 180 / PI;
			pitch = pitch*0.98 + pitchAcc*0.02;

			//Obrót w okół OY -> wektor wzdłóż OX
			rollAcc = atan2f((double)acc_buff[0], (double)acc_buff[2]) * 180 / PI;
			roll = roll*0.98 + rollAcc*0.02;


			Write_Bytes(pitch, 0x02);
		}





	}
}
