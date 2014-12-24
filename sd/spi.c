#include "spi.h"

SPI_InitTypeDef  SPI_InitStruct;
void SPIx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  	/* SPI1 Clk Init ************************************************************/
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	
	/* SPI AF ******************************************************************/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	/* CSM PB12 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	/* SCK PB13 PB14 PB15*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//SPI Configuration
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //設置SPI單向或者雙向的資料模式:SPI設置為雙線雙向全雙工
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;		//設置SPI工作模式:設置為主SPI
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;		//設置SPI的數據大小:SPI發送接收8位元幀結構
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;		//選擇了串列時鐘的穩態:時鐘懸空高
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;	//資料捕獲於第二個時鐘沿
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;		//NSS信號由硬體（NSS管腳）還是軟體（使用SSI位元）管理:內部NSS信號有SSI位元控制
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定義串列傳輸速率預分頻的值:串列傳輸速率預分頻值為256
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;	//指定資料傳輸從MSB位還是LSB位開始:資料傳輸從MSB位開始
	SPI_InitStruct.SPI_CRCPolynomial = 7;	//CRC值計算的多項式
	SPI_Init(SPI1, &SPI_InitStruct);  //根據SPI_InitStruct中指定的參數初始化外設SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外設
	
	SPIx_ReadWriteByte(0xff);//啟動傳輸		 
}   
//SPI 速度設置函數
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分頻   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8分頻   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16分頻  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256分頻 (SPI 281.25K@sys 72M)
  
void SPIx_SetSpeed(u8 SpeedSet)		   //程式執行中改速度用
{
	SPI_InitStruct.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1,ENABLE);
} 


u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //檢查指定的SPI標誌位元設置與否:發送緩存空標誌位元
		{
			retry++;
			if(retry>200)return 0;
		}			  

	SPI_I2S_SendData(SPI1, TxData); //通過外設SPIx發送一個資料
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //檢查指定的SPI標誌位元設置與否:接受緩存非空標誌位元
		{
			retry++;
			if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI1); //返回通過SPIx最近接收的資料
}
