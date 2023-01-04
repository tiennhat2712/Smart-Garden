#include "stm32f10x.h"   
#ifndef __DHT11_H
#define __DHT11_H 		
#define DHTPORT GPIOA
#define DHTPIN GPIO_Pin_7
#define DHTCLOCK RCC_APB2Periph_GPIOA
//////////////////////////////////////////////////////////////////////////////////	 
#define DHT11_IO_IN()  {DHTPORT->CRL&=0X0FFFFFFF;GPIOA->CRL|=8<<28;}
#define DHT11_IO_OUT() {DHTPORT->CRL&=0X0FFFFFFF;GPIOA->CRL|=3<<28;}
//IO										   
#define	DHT11_DQ_IN  (DHTPORT->IDR & DHTPIN) 
#define DHT11_DQ_OUT_SET DHTPORT->BRR = DHTPIN
#define DHT11_DQ_OUT_CLEAR DHTPORT->BSRR = DHTPIN

uint8_t DHT11_Init(void);
uint8_t DHT11_Read_Data(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_ReadHumi(void);
uint8_t DHT11_ReadTemp(void);
void DHT11_Rst(void);  

#endif
