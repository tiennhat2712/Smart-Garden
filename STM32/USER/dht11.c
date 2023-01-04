#include "dht11.h"
#include "Delay.h"
 u8 temp = 0;
 u8 humi = 0;
 void Delayms(uint16_t time){  

    uint16_t i,j;
    for(i=0;i<time;i++)
        for(j=0;j<10260;j++);
}

void Delayus(uint16_t time){ 
 
    uint16_t i,j;
    for(i=0;i<time;i++)
        for(j=0;j<9;j++);
}

 
u8 DHT11_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DHTCLOCK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = DHTPIN;			    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DHTPORT, &GPIO_InitStructure);			     
	
	DHT11_DQ_OUT_SET; 
	DHT11_Rst();
	
	return DHT11_Check();
}

void DHT11_Rst(void){
	
	DHT11_IO_OUT();
	DHT11_DQ_OUT_SET;
	Delayms(20);
	DHT11_DQ_OUT_CLEAR; 
	Delayus(30);
	
}

u8 DHT11_Check(void){
	u8 time=0;
	DHT11_IO_IN();
	while(DHT11_DQ_IN&&time<100)
	{
		time++;
		Delayus(1);
	}//cho xuong
	
	if(time>=100) 
		return 1;//loi
	else time=0;
	while(!DHT11_DQ_IN&&time<100)
	{
		time++;
		Delayus(1);
	}// cho len
	if(time>=100) 
		return 1;//loi
	else return 0;
	
}

u8 DHT11_Read_Bit(void){
	
	u8 time=0;
	
	while(DHT11_DQ_IN&&time<100)
	{
		time++;
		Delayus(1);
	}//cho xuong

	time=0;
	while(!DHT11_DQ_IN&&time<100)
	{
		time++;
		Delayus(1);
	}// cho len
	Delayus(40);
	if(DHT11_DQ_IN) return 1;
	else return 0;
	
	//return 0;
}

u8 DHT11_Read_Byte(void){
	u8 i=0;
	u8 data=0;
	
	for(i=0;i<8;i++){
		
		data<<=1;
		data|=DHT11_Read_Bit();
		
	}
	return data;
}

u8 DHT11_Read_Data(void){
	u8 i=0;
	u8 buf[5];	
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		
		if(buf[0]+buf[1]+buf[2]+buf[3]==buf[4])
		{
			humi=buf[0]; 
			temp=buf[2];
		}
	}
	else
	{		
		return 1;//loi
	}
	return 0;//ok
}

uint8_t DHT11_ReadHumi(void)
{
	return (uint8_t)humi;
}
uint8_t DHT11_ReadTemp(void)
{
	return (uint8_t)temp;
}

