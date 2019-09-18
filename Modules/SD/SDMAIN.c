#include "Types.h"
#include "SD_Config.h"
#include "SD_Inf.h"


#ifdef MCAL_SD_DRIVER_SPI_CONFIG_H_

#include "spi_SD.h"

extern u8 MMCWRData[MMC_DATA_SIZE];
extern u8 MMCRDData[MMC_DATA_SIZE];
#define MAX_BLOCK_NUM 12 

void SPI1_Init( void )
{
	SPI_InitTypeDef SPI_InitStruct;
	/* Configure PIN connect block */
	SPI_StructInit(& SPI_InitStruct);
	/* Configuring the SPI Mode to be Master */
	SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
	
	/* Set PCLK 1/2 of CCLK */
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	
	/*Appling the changes , configurate and enable the SPI2*/
	SPI_Init(SPI1, &SPI_InitStruct);
	
	/*Enabling the SPI2 */
	SPI_Cmd(SPI1, ENABLE);
}
void SPI1_Receive( u8 *buf, u32 Length )
{
	u8 i;
	for ( i = 0; i < Length; i++ )
	{
		*buf = SPI_I2S_ReceiveData( SPI3);
		//buf++;
	}
	return;
}

void SPI_test(void)
{
	u8 *tx_test;
	u8 *rx_test;
	
	*tx_test = 0xff;
	//SPI2_Init();
	SPI1_Init();
	
	SPI2_Send(tx_test,1);
	
	
	SPI1_Receive(rx_test,1);
	rx_test = rx_test;
}
#endif

#ifdef MCAL_SD_DRIVER_UART_CONFIG_H_
#include "UART_SD.h"

#endif 
