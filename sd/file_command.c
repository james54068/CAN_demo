#include "file_command.h"
#include "ff.h"
#include "main.h"
#include <string.h>

uint8_t ls(uint8_t *Directory)
{
	/* Directory object structure (DIR) */
	DIR       dir;
 	/*File status structure (FILINFO) */
	FILINFO   fileInfo;
	/* File function return code (FRESULT) */
	FRESULT   res;

  	if(f_opendir(&dir,Directory)==FR_OK)
  	{
    	while(f_readdir(&dir,&fileInfo)==FR_OK)
    	{
      		if(!fileInfo.fname[0]) break;
      		/*AM_ARC:read/write able file*/      
      		if(fileInfo.fattrib==AM_ARC)  printf("%s\r\n",fileInfo.fname);
      		/*AM_DIR:Directory*/
      		if(fileInfo.fattrib==AM_DIR)  printf("%s\r\n",fileInfo.fname);
    	}
    	f_readdir(&dir,NULL);
    	return 0;
  	}
  return 1;
}

uint8_t ls_all(uint8_t *Directory)
{
	uint8_t next_folder[]="";
	uint8_t current_folder[]="";
	DIR     dir_scan;
 	/*File status structure (FILINFO) */
	FILINFO fileInfo_scan;
	/* File function return code (FRESULT) */
	// static uint8_t folder[]="";

	//printf("%s\r\n",folder);
	uint8_t res;
	res = f_opendir(&dir_scan,Directory);
	printf("%d\r\n",res);
  	if(res==FR_OK)
  	{
		strcpy(current_folder,Directory);
		
    	while(f_readdir(&dir_scan,&fileInfo_scan)==FR_OK)
    	{
      		if(!fileInfo_scan.fname[0]) break;
      		if(fileInfo_scan.fname[0]=='.') continue;
      		/*AM_ARC:read/write able file*/      
      		if(fileInfo_scan.fattrib==AM_ARC)  
      		{
      			//strcat(current_folder,"/");
      			printf("%s/",current_folder);
      			printf("%s\r\n",fileInfo_scan.fname);
      			//strcat(current_folder,fileInfo_scan.fname);
      			//printf("%s\r\n",current_folder);
      		}
      		/*AM_DIR:Directory*/
      		if(fileInfo_scan.fattrib==AM_DIR)
      		{
      			//printf("%s\r\n",fileInfo_scan.fname);
      			strcat(Directory,fileInfo_scan.fname);
      			strcpy(next_folder,Directory);
      			//printf("%s\r\n",next_folder);
      			ls_all(&next_folder);
      		}      			
    	}
    	f_readdir(&dir_scan,NULL);
    	return 0;
  	}
  return 1;
}


uint8_t read_file(uint8_t *Directory)
{
	/* File object structure (FIL) */
	FIL       fsrc;
	/* Directory object structure (DIR) */
	DIR       dir;
 	/*File status structure (FILINFO) */
	FILINFO   fileInfo;
	/* File function return code (FRESULT) */
	FRESULT   res;
	/* File read/write count*/
	UINT      br;

	/*Max file number in root is 50(no long name <= 8 byte)*/
	uint8_t Block_Buffer[512];

	res = f_opendir(&dir,Directory);
  	printf("%d\r\n",res);
  	if(res==FR_OK)
  	{ 
    	res = f_open(&fsrc, "123", FA_READ);
    	printf("%d\r\n",res);
    if(!res)
    {
      printf("open news.txt : %d\r\n",res);
      br=1;
      printf("File Content:\r\n");
      for (;;)
      {
        int a=0;
        for(a=0; a<512; a++) Block_Buffer[a]=0;
        res = f_read(&fsrc, Block_Buffer, sizeof(Block_Buffer), &br);
        printf("%s\r\n",Block_Buffer);
        /**/
        if (res || br < sizeof(Block_Buffer)) break; 
      }
    }
    f_close(&fsrc);     
  }
}