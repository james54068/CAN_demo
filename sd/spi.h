#ifndef __SPI_H
#define __SPI_H
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

/*Function Prototype*/ 				  	    													  
void SPIx_Init(void);			 //初始化SPI口
void SPIx_SetSpeed(u8 SpeedSet); //設置SPI速度   
u8 	SPIx_ReadWriteByte(u8 TxData);//SPI匯流排讀寫一個位元組
		 
#endif


