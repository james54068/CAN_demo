#ifndef __SPI_H
#define __SPI_H
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

/*Function Prototype*/ 				  	    													  
void SPIx_Init(void);			 //��l��SPI�f
void SPIx_SetSpeed(u8 SpeedSet); //�]�mSPI�t��   
u8 	SPIx_ReadWriteByte(u8 TxData);//SPI�׬y��Ū�g�@�Ӧ줸��
		 
#endif


