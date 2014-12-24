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
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //�]�mSPI��V�Ϊ����V����ƼҦ�:SPI�]�m�����u���V�����u
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;		//�]�mSPI�u�@�Ҧ�:�]�m���DSPI
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;		//�]�mSPI���ƾڤj�p:SPI�o�e����8�줸�V���c
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;		//��ܤF��C������í�A:�����a�Ű�
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;	//��Ʈ����ĤG�Ӯ����u
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;		//NSS�H���ѵw��]NSS�޸}�^�٬O�n��]�ϥ�SSI�줸�^�޲z:����NSS�H����SSI�줸����
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//�w�q��C�ǿ�t�v�w���W����:��C�ǿ�t�v�w���W�Ȭ�256
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;	//���w��ƶǿ�qMSB���٬OLSB��}�l:��ƶǿ�qMSB��}�l
	SPI_InitStruct.SPI_CRCPolynomial = 7;	//CRC�ȭp�⪺�h����
	SPI_Init(SPI1, &SPI_InitStruct);  //�ھ�SPI_InitStruct�����w���Ѽƪ�l�ƥ~�]SPIx�H�s��
 
	SPI_Cmd(SPI1, ENABLE); //�ϯ�SPI�~�]
	
	SPIx_ReadWriteByte(0xff);//�Ұʶǿ�		 
}   
//SPI �t�׳]�m���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2���W   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8���W   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16���W  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256���W (SPI 281.25K@sys 72M)
  
void SPIx_SetSpeed(u8 SpeedSet)		   //�{�����椤��t�ץ�
{
	SPI_InitStruct.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1,ENABLE);
} 


u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //�ˬd���w��SPI�лx�줸�]�m�P�_:�o�e�w�s�żлx�줸
		{
			retry++;
			if(retry>200)return 0;
		}			  

	SPI_I2S_SendData(SPI1, TxData); //�q�L�~�]SPIx�o�e�@�Ӹ��
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //�ˬd���w��SPI�лx�줸�]�m�P�_:�����w�s�D�żлx�줸
		{
			retry++;
			if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI1); //��^�q�LSPIx�̪񱵦������
}
