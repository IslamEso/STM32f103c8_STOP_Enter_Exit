
#include <stdint.h>
#include "Types.h"
#include "spi_SD.h"

//#include "GPIO_interface.h"


uint8_t MMCWRData[MMC_DATA_SIZE];
uint8_t MMCRDData[MMC_DATA_SIZE];
uint8_t MMCCmd[MMC_CMD_SIZE];
uint8_t MMCStatus = 0;
int mmc_response( uint16_t response);
int mmc_wait_for_write_finish( void );
/*
* SPI and MMC commands related modules.
*
*/
void SPI2_Init( void )
{
	SPI_InitTypeDef SPI_InitStruct;
	/* Configure PIN connect block */
	SPI_StructInit(& SPI_InitStruct);
	/* Configuring the SPI Mode to be Master */
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	
	/* Set PCLK 1/2 of CCLK */
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	GPIO_voidSetPinValue(GPIOB_PIN12,GPIO_u8LOW);
	GPIO_voidSetPinValue(GPIOB_PIN12,GPIO_u8HIGH);
	/*Appling the changes , configurate and enable the SPI2*/
	SPI_Init(SPI2, &SPI_InitStruct);
	/*Configuring the SPI NSS to be Hardware Managed and NSS output is enabled*/
	SPI_SSOutputCmd(SPI2, ENABLE );
	/*Enabling the SPI2 */
	//SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_RXNE,ENABLE);
	SPI_Cmd(SPI2, ENABLE);
}
/**
  * @brief  SPI Send a block of data based on the length.
* @param  buf: pointer to the buffer to be sent.
* @param  Length: Length of the data to be sent in Bytes. 
*   @retval None
	*/
void SPI2_Send( u8 *buf, u32 Length )
{
	u8 Dummy;
	if ( Length == 0 )
	return;
	while ( Length > 0 )
	{
			/* as long as TNF bit is set, TxFIFO is not full, I can write */
		while ( !(SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_TXE)) );
		SPI_I2S_SendData(SPI2, *buf );
		/* Wait until the Busy bit is cleared */
		while ( (SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY)) );
		/* Flush the RxFIFO */
		Dummy =  SPI_I2S_ReceiveData( SPI2); 
		Length--;
		buf++;
	}
	Dummy = Dummy;
}

void SPI2_IRQHandler(void)
{
    //unsigned char rx;
    static unsigned short int  i = 0 ;
		static volatile u8 Slave_rev_buff[10];

    if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
    {
        Slave_rev_buff[i] = SPI2->DR ;
        i++ ;
    }

}
/**
  * @brief  SPI receives a block of data based on the length.
* @param  buf: pointer to the buffer to be recieved in.
* @param  Length: Length of the data to be recieved in Bytes. 
*   @retval None
	*/
void SPI2_Receive( u8 *buf, u32 Length )
{
	u8 i;
	for ( i = 0; i < Length; i++ )
	{
		*buf = SPI_I2S_ReceiveData( SPI2);
		buf++;
	}
	return;
}

/**
  * @brief  SPI Receive Byte, receive one byte only, return Data byte
* 					used a lot to check the status.
* @param  buf: pointer to the buffer to be recieved in.
* @param  Length: Length of the data to be recieved in Bytes. 
*   @retval None
	*/
u8 SPI2_ReceiveByte( void )
{
	return ( SPI_I2S_ReceiveData( SPI2) );
}
/************************** MMC Init *********************************/
/*
* Initialises the MMC into SPI mode and sets block size(512), returns
* 0 on success
*
*/
int mmc_init()
{
	u32 i;
	/* Generate a data pattern for write block */
	for(i=0;i<MMC_DATA_SIZE;i++)
	{
		MMCWRData[i] = i;
	}
	MMCStatus = 0;
	/* initialise the MMC card into SPI mode by sending 80 clks on */
	/* Use MMCRDData as a temporary buffer for SPI_Send() */
	for(i=0; i<10; i++)
	{
		MMCRDData[i] = 0xFF;
	}
	SPI2_Send( MMCRDData, 10 );
	//IOCLR0 = SPI_SEL; /* clear SPI SSEL */
	GPIO_voidSetPinValue(GPIOB_PIN12,GPIO_u8LOW);
	/* send CMD0(RESET or GO_IDLE_STATE) command, all the arguments
	are 0x00 for the reset command, precalculated checksum */
	MMCCmd[0] = 0x40;
	MMCCmd[1] = 0x00;
	MMCCmd[2] = 0x00;
	MMCCmd[3] = 0x00;
	MMCCmd[4] = 0x00;
	MMCCmd[5] = 0x95;
	SPI2_Send( MMCCmd, MMC_CMD_SIZE );
	/* if = 1 then there was a timeout waiting for 0x01 from the MMC */
	if( mmc_response(0x01) == 1 )
	{
		MMCStatus = IDLE_STATE_TIMEOUT;
		//IOSET0 = SPI_SEL; /* set SPI SSEL */
		return MMCStatus;
	}
	/* Send some dummy clocks after GO_IDLE_STATE */
	//IOSET0 = SPI_SEL; /* set SPI SSEL */
	SPI2_ReceiveByte();
	//IOCLR0 = SPI_SEL; /* clear SPI SSEL */
	/* must keep sending command until zero response ia back. */
	i = MAX_TIMEOUT;
	do
	{
		/* send mmc CMD1(SEND_OP_COND) to bring out of idle state */
		/* all the arguments are 0x00 for command one */
		MMCCmd[0] = 0x41;
		MMCCmd[1] = 0x00;
		MMCCmd[2] = 0x00;
		MMCCmd[3] = 0x00;
		MMCCmd[4] = 0x00;
		/* checksum is no longer required but we always send 0xFF */
		MMCCmd[5] = 0xFF;
		SPI2_Send( MMCCmd, MMC_CMD_SIZE );
		i--;
	} while ( (mmc_response(0x00) != 0) && (i>0) );
	/* timeout waiting for 0x00 from the MMC */
	if ( i == 0 )
	{
		MMCStatus = OP_COND_TIMEOUT;
		//IOSET0 = SPI_SEL; /* set SPI SSEL */
		return MMCStatus;
	}
	/* Send some dummy clocks after SEND_OP_COND */
	//IOSET0 = SPI_SEL; /* set SPI SSEL */
	SPI2_ReceiveByte();
	//IOCLR0 = SPI_SEL; /* clear SPI SSEL */
	/* send MMC CMD16(SET_BLOCKLEN) to set the block length */
	MMCCmd[0] = 0x50;
	MMCCmd[1] = 0x00; /* 4 bytes from here is the block length */
	/* LSB is first */
	/* 00 00 00 10 set to 16 bytes */
	/* 00 00 02 00 set to 512 bytes */
	MMCCmd[2] = 0x00;
	/* high block length bits - 512 bytes */
	MMCCmd[3] = 0x02;
	/* low block length bits */
	MMCCmd[4] = 0x00;
	/* checksum is no longer required but we always send 0xFF */
	MMCCmd[5] = 0xFF;
	SPI2_Send( MMCCmd, MMC_CMD_SIZE );
	if( (mmc_response(0x00))==1 )
	{
		MMCStatus = SET_BLOCKLEN_TIMEOUT;
		//IOSET0 = SPI_SEL; /* set SPI SSEL */
		return MMCStatus;
	}
	//IOSET0 = SPI_SEL; /* set SPI SSEL */
	SPI2_ReceiveByte();
	return 0;
}

/************************** MMC Write Block ***************************/
/* write a block of data based on the length that has been set
* in the SET_BLOCKLEN command.
* Send the WRITE_SINGLE_BLOCK command out first, check the
* R1 response, then send the data start token(bit 0 to 0) followed by
* the block of data. The test program sets the block length to 512
* bytes. When the data write finishs, the response should come back
* as 0xX5 bit 3 to 0 as 0101B, then another non-zero value indicating
* that MMC card is in idle state again.
*
*/
int mmc_write_block(u16 block_number)
{
u16 varl, varh;
u8 Status;
//IOCLR0 = SPI_SEL; /* clear SPI SSEL */
/* block size has been set in mmc_init() */
varl=((block_number&0x003F)<<9);
varh=((block_number&0xFFC0)>>7);
/* send mmc CMD24(WRITE_SINGLE_BLOCK) to write the data to MMC card */
MMCCmd[0] = 0x58;
/* high block address bits, varh HIGH and LOW */
MMCCmd[1] = varh >> 0x08;
MMCCmd[2] = varh & 0xFF;
/* low block address bits, varl HIGH and LOW */
MMCCmd[3] = varl >> 0x08;
MMCCmd[4] = varl & 0xFF;
/* checksum is no longer required but we always send 0xFF */
MMCCmd[5] = 0xFF;
SPI2_Send(MMCCmd, MMC_CMD_SIZE );
/* if mmc_response returns 1 then we failed to get a 0x00 response */
if((mmc_response(0x00))==1)
{
MMCStatus = WRITE_BLOCK_TIMEOUT;
//IOSET0 = SPI_SEL; /* set SPI SSEL */
return MMCStatus;
}
/* Set bit 0 to 0 which indicates the beginning of the data block */
MMCCmd[0] = 0xFE;
SPI2_Send( MMCCmd, 1 );
/* send data, pattern as 0x00,0x01,0x02,0x03,0x04,0x05 ...*/
SPI2_Send( MMCWRData, MMC_DATA_SIZE );
/* Send dummy checksum */
/* when the last check sum is sent, the response should come back
immediately. So, check the SPI FIFO MISO and make sure the status
return 0xX5, the bit 3 through 0 should be 0x05 */
MMCCmd[0] = 0xFF;
MMCCmd[1] = 0xFF;
SPI2_Send( MMCCmd, 2 );
Status = SPI2_ReceiveByte();
if ( (Status & 0x0F) != 0x05 )
{
MMCStatus = WRITE_BLOCK_FAIL;
//IOSET0 = SPI_SEL; /* set SPI SSEL */
return MMCStatus;
}
/* if the status is already zero, the write hasn't finished
yet and card is busy */
if(mmc_wait_for_write_finish()==1)
{
MMCStatus = WRITE_BLOCK_FAIL;
//IOSET0 = SPI_SEL; /* set SPI SSEL */
return MMCStatus;
}
//IOSET0 = SPI_SEL; /* set SPI SSEL */
SPI2_ReceiveByte();
return 0;
}
/************************** MMC Read Block ****************************/
/*
* Reads a 512 Byte block from the MMC
* Send READ_SINGLE_BLOCK command first, wait for response come back
* 0x00 followed by 0xFE. The call SPI_Receive() to read the data
* block back followed by the checksum.
*
*/
int mmc_read_block(u16 block_number)
{
	u16 Checksum;
	u16 varh,varl;
	//IOCLR0 = SPI_SEL; /* clear SPI SSEL */
	varl=((block_number&0x003F)<<9);
	varh=((block_number&0xFFC0)>>7);
	/* send MMC CMD17(READ_SINGLE_BLOCK) to read the data from MMC card */
	MMCCmd[0] = 0x51;
	/* high block address bits, varh HIGH and LOW */
	MMCCmd[1] = varh >> 0x08;
	MMCCmd[2] = varh & 0xFF;
	/* low block address bits, varl HIGH and LOW */
	MMCCmd[3] = varl >> 0x08;
	MMCCmd[4] = varl & 0xFF;
	/* checksum is no longer required but we always send 0xFF */
	MMCCmd[5] = 0xFF;
	SPI2_Send(MMCCmd, MMC_CMD_SIZE );
	/* if mmc_response returns 1 then we failed to get a 0x00 response */
	if((mmc_response(0x00))==1)
	{
		MMCStatus = READ_BLOCK_TIMEOUT;
		return MMCStatus;
	}
	/* wait for data token */
	if((mmc_response(0xFE))==1)
	{
		MMCStatus = READ_BLOCK_DATA_TOKEN_MISSING;
		return MMCStatus;
	}
	/* Get the block of data based on the length */
	SPI2_Receive( MMCRDData, MMC_DATA_SIZE );
	/* CRC bytes that are not needed */
	Checksum = SPI2_ReceiveByte();
	Checksum = Checksum << 0x08 | SPI2_ReceiveByte();
	SPI2_ReceiveByte();
	return 0;
}
/***************** MMC get response *******************/
/*
* Repeatedly reads the MMC until we get the
* response we want or timeout
*/
int mmc_response( u16 response)
{
	u32 count = 0xFFF;
	u8 result;
	while( count > 0 )
	{
		result = SPI2_ReceiveByte();
		while(result != response)
		{
			SPI_I2S_SendData(SPI2, response );
			/* Wait until the Busy bit is cleared */
			while ( (SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY)) );
			result = SPI2_ReceiveByte();
		}
		if ( result == response )
		{
			break;
		}
		count--;
	}
	if ( count == 0 )
		return 1; /* Failure, loop was exited due to timeout */
	else
		return 0; /* Normal, loop was exited before timeout */
}
/***************** MMC wait for write finish *******************/
/*
* Repeatedly reads the MMC until we get a non-zero value (after
* a zero value) indicating the write has finished and card is no
* longer busy.
*
*/
int mmc_wait_for_write_finish( void )
{
	u32 count = 0xFFFF; /* The delay is set to maximum considering
	the longest data block length to handle */
	u8 result = 0;
	while( (result == 0) && count )
	{
		result = SPI2_ReceiveByte();
		count--;
	}
	if ( count == 0 )
		return 1; /* Failure, loop was exited due to timeout */
	else
		return 0; /* Normal, loop was exited before timeout */
}

