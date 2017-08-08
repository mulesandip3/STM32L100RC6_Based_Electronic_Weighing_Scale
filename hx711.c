#include "main.h"
#include "hx711.h"
#include <stdio.h>

#define DOUT GPIO_Pin_13
#define PD_SCK GPIO_Pin_14


int  GAIN;		// amplification factor
long OFFSET = 0;	// used for tare weight
float SCALE = 1;	// used to return weight in grams, kg, ounces, whatever



GPIO_InitTypeDef GPIO_InitStructure;

void hx711_init(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = DOUT;           // DOUT as a Input Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = PD_SCK;           // PD_SCK as a Output Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

char isready(void)
{
	if (GPIO_ReadInputDataBit(GPIOC,DOUT) == 0)
		return 0;
	else
		return 1;
}


void set_gain(int gain)
{
	switch (gain)
	{
		case 128:
			GAIN = 1;
		  break;	
		case 64:
			GAIN = 3;
		  break;	
		case 32:
			GAIN = 2;
			break;	
  }
	GPIO_WriteBit(GPIOC,PD_SCK,0);
	read();
}

unsigned long read(void)
{
	unsigned long Count;
	unsigned char i;
	Count=0;
	while(isready()==1);
	for (i=0;i<24;i++)
	{
		GPIO_SetBits(GPIOC,PD_SCK);
		Count=Count<<1;
		GPIO_ResetBits(GPIOC,PD_SCK);
		if(isready()==1) Count++;
	}
	GPIO_SetBits(GPIOC,PD_SCK);
	Count=Count^0x800000;
	GPIO_ResetBits(GPIOC,PD_SCK);
return(Count);
}




/*
unsigned long read(void)
{
	unsigned long count,dout;
	uint8_t i;	
	count = 0;
	dout = 0;
	
	if(isready() == 1)
	{
		GPIO_ResetBits(GPIOC,PD_SCK);
	}
	else
	{
		for(i=0;i<24;i++)
		{
			GPIO_SetBits(GPIOC,PD_SCK);
			delay(1);
			GPIO_ResetBits(GPIOC,PD_SCK);
			dout = GPIO_ReadInputDataBit(GPIOC,DOUT);
			count = (count | dout) << 1;
      delay(1);			
		}
   }
	GPIO_SetBits(GPIOC,PD_SCK);
	GPIO_ResetBits(GPIOC,PD_SCK);
	count = count >> 1;
	return count;
}

*/

