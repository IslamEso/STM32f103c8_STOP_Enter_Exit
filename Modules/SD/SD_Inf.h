/**
 * @file 	SD_Inf.h
 * @author 	Ahmed Hashesh
 * @date 	
 * @brief File contain the unified interface to be used with the SD card in case of UART or SPI.
 *	this is the only file allowed to be included when using SD Card  
 */

#include "Types.h"


#ifndef MODULES_SD_INF_H_
#define MODULES_SD_INF_H_

#define SD_ENABLE  STD_ON


//#if (SD_ENABLE == STD_ON)

#define SD_INIT() SD_store_String("General.txt","Initialized !!!")
#define SD_Write_Byte(byte) SD_store_String("General.txt",byte)
#define SD_Write_String(p_u8Byte,SizeBytes)  SD_store_String("General.txt",p_u8Byte)

extern  void SD_store_String(char * filename,char * p_char);

//#endif


#endif /* MODULES_SD_INF_H_ */
