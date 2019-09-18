#include "Types.h"
#include "SD_Inf.h"
#include "fatfs.h"

FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t total, free;
char buffer[100];

#define _Error_Handler(__FILE__, __LINE__) return /*Error_Handler()*/

void SD_store_String(char * filename, char * p_u8Byte)
{
    
/* Mount SD Card */
  if(f_mount(&fs, "", 0) != FR_OK)
    _Error_Handler(__FILE__, __LINE__);
  
  /* Open file to write */
  if(f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE) != FR_OK)
    _Error_Handler(__FILE__, __LINE__);
  
  f_lseek(&fil,f_size(&fil));

  /* Check free space */
 // if(f_getfree("", &fre_clust, &pfs) != FR_OK)
  //  _Error_Handler(__FILE__, __LINE__);
  
 // total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
 // free = (uint32_t)(fre_clust * pfs->csize * 0.5);   
    
  /* Free space is less than 1kb */
 // if(free < 1)
 //   _Error_Handler(__FILE__, __LINE__);  

	f_puts(p_u8Byte, &fil);  
	//f_puts("data saved successfully !!!", &fil);
	
  /* Close file */
  if(f_close(&fil) != FR_OK)
    _Error_Handler(__FILE__, __LINE__);  
  
  /* Unmount SDCARD */
  if(f_mount(NULL, "", 1) != FR_OK)
    _Error_Handler(__FILE__, __LINE__);     
}
