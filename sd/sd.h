#ifndef _SD_CARD_H_
#define _SD_CARD_H_		 
#include "stm32f4xx.h"
 						    	 
// SD�����w�q
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
// SD�d���O��  	   
#define CMD0    0       //�d�`��
#define CMD1    1
#define CMD8    8       //�R�O8 �ASEND_IF_COND
#define CMD9    9       //�R�O9 �AŪCSD�ƾ�
#define CMD10   10      //�R�O10�AŪCID�ƾ�
#define CMD12   12      //�R�O12�A����ƾڶǿ�
#define CMD16   16      //�R�O16�A�]�mSectorSize�A���Ӧ^��0x00
#define CMD17   17      //�R�O17�AŪSector
#define CMD18   18      //�R�O18�AŪMulti sector
#define CMD23   23      //�R�O23�A�]�m�hsector�g�J�e�w���q��N��Block
#define CMD24   24      //�R�O24�A�gSector
#define CMD25   25      //�R�O25�A?Multi sector
#define CMD41   41      //�R�O41�A�^��0x00
#define CMD55   55      //�R�O55�A�^��0x01
#define CMD58   58      //�R�O58�AŪCCR�H��
#define CMD59   59      //�R�O59�A�ϯ�/�T��CRC�A���Ӧ^��0x00
//�ƾڼg�J�^�Ǧr���N�q
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD�d�^�ǭȪ��N�q [bit7 bit6 ......bit2 bit1 bit0]
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF
 							   						 	 
//CS�}��w�q
#define SD_CS_PORT GPIOA
#define SD_CS_CLK  RCC_AHB1Periph_GPIOA
#define SD_CS_PIN  GPIO_Pin_4
#define Set_SD_CS  GPIO_SetBits(SD_CS_PORT,SD_CS_PIN);
#define Clr_SD_CS  GPIO_ResetBits(SD_CS_PORT,SD_CS_PIN);
				    	  

extern u8  SD_Type;//SD�d������
//�禡�ŧi�� 
u8 SD_WaitReady(void);							//����SD�d�ǳ�
u8 SD_GetResponse(u8 Response);					//���oSD�d�^��
u8 SD_Initialize(void);							//SD�d��l��
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);		//Ū
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);		//�g
u32 SD_GetSectorCount(void);   					//Ū��sector�ƶq
u8 SD_GetCID(u8 *cid_data);                     //ŪSD�dCID
u8 SD_GetCSD(u8 *csd_data);                     //ŪSD�dCSD
 
#endif





