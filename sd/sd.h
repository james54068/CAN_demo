#ifndef _SD_CARD_H_
#define _SD_CARD_H_		 
#include "stm32f4xx.h"
 						    	 
// SD類型定義
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
// SD卡指令表  	   
#define CMD0    0       //卡复位
#define CMD1    1
#define CMD8    8       //命令8 ，SEND_IF_COND
#define CMD9    9       //命令9 ，讀CSD數據
#define CMD10   10      //命令10，讀CID數據
#define CMD12   12      //命令12，停止數據傳輸
#define CMD16   16      //命令16，設置SectorSize，應該回傳0x00
#define CMD17   17      //命令17，讀Sector
#define CMD18   18      //命令18，讀Multi sector
#define CMD23   23      //命令23，設置多sector寫入前預先猜除N個Block
#define CMD24   24      //命令24，寫Sector
#define CMD25   25      //命令25，?Multi sector
#define CMD41   41      //命令41，回傳0x00
#define CMD55   55      //命令55，回傳0x01
#define CMD58   58      //命令58，讀CCR信息
#define CMD59   59      //命令59，使能/禁止CRC，應該回傳0x00
//數據寫入回傳字的意義
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD卡回傳值的意義 [bit7 bit6 ......bit2 bit1 bit0]
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF
 							   						 	 
//CS腳位定義
#define SD_CS_PORT GPIOA
#define SD_CS_CLK  RCC_AHB1Periph_GPIOA
#define SD_CS_PIN  GPIO_Pin_4
#define Set_SD_CS  GPIO_SetBits(SD_CS_PORT,SD_CS_PIN);
#define Clr_SD_CS  GPIO_ResetBits(SD_CS_PORT,SD_CS_PIN);
				    	  

extern u8  SD_Type;//SD卡的類型
//函式宣告⑹ 
u8 SD_WaitReady(void);							//等待SD卡準備
u8 SD_GetResponse(u8 Response);					//取得SD卡回應
u8 SD_Initialize(void);							//SD卡初始化
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);		//讀
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);		//寫
u32 SD_GetSectorCount(void);   					//讀取sector數量
u8 SD_GetCID(u8 *cid_data);                     //讀SD卡CID
u8 SD_GetCSD(u8 *csd_data);                     //讀SD卡CSD
 
#endif





