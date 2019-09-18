/*
 * Uart_Abs.c
 *
 *  Created on: Jul 28, 2018
 *      Author: Maged
 */
#include "Types.h"
#include "stm32f1xx_hal.h"
#include "Uart_Abs.h"
#include <string.h>


#if(UART1_ENABLE==STD_ON)
extern UART_HandleTypeDef huart1;
static uint8_t  Uart1_RX_buffer[UART1_BUFFER_LENGTH]={0};
static uint16_t Uart1_RX_buffer_counter = 0;
static uint8_t  Uart1_Receive_buf[2]={0};
static uint8_t  Uart1_u8Flags=0;
//static uint16_t Uart1_u16LastReadIndex=0;
#endif

#if(UART2_ENABLE==STD_ON)
extern UART_HandleTypeDef huart2;
static uint8_t  Uart2_RX_buffer[UART2_BUFFER_LENGTH]={0};
static uint16_t Uart2_RX_buffer_counter = 0;
static uint8_t  Uart2_Receive_buf[2]={0};
static uint8_t  Uart2_u8Flags=0;
//static uint16_t Uart2_u16LastReadIndex=0;
#endif

#if(UART3_ENABLE==STD_ON)
extern UART_HandleTypeDef huart3;
static uint8_t  Uart3_RX_buffer[UART3_BUFFER_LENGTH]={0};
static uint16_t Uart3_RX_buffer_counter = 0;
static uint8_t  Uart3_Receive_buf[2]={0};
static uint8_t  Uart3_u8Flags=0;
//static uint16_t Uart3_u16LastReadIndex=0;
#endif


#if(TEST_UART == STD_ON)
uint8_t uart_test_msg1[]={0xFF,0xFF,0x17,'T','e','s','t'};
uint8_t uart_test_msg2[]="AT\r";
uint8_t uart_test_msg2RX[50];
volatile uint16_t uart_test_RX_len=0;
volatile HAL_StatusTypeDef sendStatus;
volatile std_returnType sendStatus2;
void UART_test_task(void)
{
	//    do{
	//    sendStatus==HAL_UART_GetState(&huart1);
	//    }while(sendStatus!=HAL_OK);
	uart_test_RX_len=UART_u16ReadRxBuffer(UART_CH3,uart_test_msg2RX);
	sendStatus2=UART_udtFlushRxBuffer(UART_CH3);
	sendStatus2=UART_udtSendString(UART_CH3,uart_test_msg2);
	//sendStatus=HAL_UART_Transmit(&huart2,uart_test_msg,sizeof(uart_test_msg),1000);
	//sendStatus=HAL_UART_Transmit(&huart3,uart_test_msg,sizeof(uart_test_msg),1000);
	//	do{
	//    sendStatus==HAL_UART_GetState(&huart1);
	//    }while(sendStatus!=HAL_OK);
	//	sendStatus=HAL_UART_Receive(&huart1,&Uart1_RX_buffer[Uart1_RX_buffer_counter++],1,1000);
}


#endif


void UART_voidInit(void)
{
#if(UART1_ENABLE==STD_ON)
	HAL_UART_Receive_IT(&huart1,&Uart1_Receive_buf[0],1);
	#endif

#if(UART2_ENABLE==STD_ON)
	HAL_UART_Receive_IT(&huart2,&Uart2_Receive_buf[0],1);
#endif

#if(UART3_ENABLE==STD_ON)
	HAL_UART_Receive_IT(&huart3,&Uart3_Receive_buf[0],1);
#endif
}

void UART_voidDeinit(void)
{
#if(UART1_ENABLE==STD_ON)
	HAL_UART_AbortReceive_IT(&huart1);
	#endif

#if(UART2_ENABLE==STD_ON)
	HAL_UART_AbortReceive_IT(&huart2);
#endif

#if(UART3_ENABLE==STD_ON)
	HAL_UART_AbortReceive_IT(&huart3);
#endif
}

#if(UART1_ENABLE==STD_ON)
void UART1_voidInit(void)
{
	HAL_UART_Receive_IT(&huart1,&Uart1_Receive_buf[0],1);
}
#endif


#if(UART1_ENABLE==STD_ON)
void UART1_voidDeinit(void)
{
	HAL_UART_AbortReceive_IT(&huart1);
}
#endif


#if(UART2_ENABLE==STD_ON)
void UART2_voidInit(void)
{
	HAL_UART_Receive_IT(&huart2,&Uart2_Receive_buf[0],1);
}
#endif

#if(UART2_ENABLE==STD_ON)
void UART2_voidDeinit(void)
{
	HAL_UART_AbortReceive_IT(&huart2);
}
#endif

#if(UART3_ENABLE==STD_ON)
void UART3_voidInit(void)
{
	HAL_UART_Receive_IT(&huart3,&Uart3_Receive_buf[0],1);
}
#endif

#if(UART3_ENABLE==STD_ON)
void UART3_voidDeinit(void)
{
	HAL_UART_AbortReceive_IT(&huart3);
}
#endif


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if(UART1_ENABLE==STD_ON)
	if(huart->Instance == huart1.Instance)
	{
		Uart1_RX_buffer[Uart1_RX_buffer_counter]=Uart1_Receive_buf[0];
		Uart1_RX_buffer_counter++;
		SET_FLAG(Uart1_u8Flags,UART_RX_INDICATION_FLAG);
		if(Uart1_RX_buffer_counter>=UART1_BUFFER_LENGTH)
		{
			Uart1_RX_buffer_counter=0;
			SET_FLAG(Uart1_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		}
		HAL_UART_Receive_IT(&huart1,&Uart1_Receive_buf[0],1);
	}
#endif

#if(UART2_ENABLE==STD_ON)
	if(huart->Instance == huart2.Instance)
	{
		Uart2_RX_buffer[Uart2_RX_buffer_counter]=Uart2_Receive_buf[0];
		Uart2_RX_buffer_counter++;
		SET_FLAG(Uart2_u8Flags,UART_RX_INDICATION_FLAG);
		if(Uart2_RX_buffer_counter>=UART2_BUFFER_LENGTH)
		{
			Uart2_RX_buffer_counter=0;
			SET_FLAG(Uart2_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		}
		HAL_UART_Receive_IT(&huart2,&Uart2_Receive_buf[0],1);
	}
#endif

#if(UART3_ENABLE==STD_ON)
	if(huart->Instance == huart3.Instance)
	{
		Uart3_RX_buffer[Uart3_RX_buffer_counter]=Uart3_Receive_buf[0];
		Uart3_RX_buffer_counter++;
		SET_FLAG(Uart3_u8Flags,UART_RX_INDICATION_FLAG);
		if(Uart3_RX_buffer_counter>=UART3_BUFFER_LENGTH)
		{
			Uart3_RX_buffer_counter=0;
			SET_FLAG(Uart3_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		}
		HAL_UART_Receive_IT(&huart3,&Uart3_Receive_buf[0],1);
	}
#endif
}  // end of void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)


/******************************************************************/
/********************** Flush RX buffers **************************/
/******************************************************************/

#if(UART1_ENABLE==STD_ON)
void UART1_voidFlushRxBuffer(void)
{
	memset(Uart1_RX_buffer,0,UART1_BUFFER_LENGTH);
	Uart1_RX_buffer_counter = 0;
	CLEAR_FLAG(Uart1_u8Flags,UART_RX_INDICATION_FLAG);
	CLEAR_FLAG(Uart1_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
	//Uart1_u16LastReadIndex=0;
}
#endif

#if(UART2_ENABLE==STD_ON)
void UART2_voidFlushRxBuffer(void)
{
	memset(Uart2_RX_buffer,0,UART2_BUFFER_LENGTH);
	Uart2_RX_buffer_counter = 0;
	CLEAR_FLAG(Uart2_u8Flags,UART_RX_INDICATION_FLAG);
	CLEAR_FLAG(Uart2_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
	//Uart2_u16LastReadIndex=0;
}
#endif

#if(UART3_ENABLE==STD_ON)
void UART3_voidFlushRxBuffer(void)
{
	memset(Uart3_RX_buffer,0,UART3_BUFFER_LENGTH);
	Uart3_RX_buffer_counter = 0;
	CLEAR_FLAG(Uart3_u8Flags,UART_RX_INDICATION_FLAG);
	CLEAR_FLAG(Uart3_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
	//Uart3_u16LastReadIndex=0;
}
#endif

std_returnType UART_udtFlushRxBuffer(Uart_udtChannelType Channel)
{
	std_returnType LocalReturn = E_NOK;
	switch (Channel)
	{
#if(UART1_ENABLE==STD_ON)
	case UART_CH1:
		memset(Uart1_RX_buffer,0,UART1_BUFFER_LENGTH);
		Uart1_RX_buffer_counter = 0;
		CLEAR_FLAG(Uart1_u8Flags,UART_RX_INDICATION_FLAG);
		CLEAR_FLAG(Uart1_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		//Uart1_u16LastReadIndex=0;
		LocalReturn = E_OK;
		break;
#endif
#if(UART2_ENABLE==STD_ON)
	case UART_CH2:
		memset(Uart2_RX_buffer,0,UART2_BUFFER_LENGTH);
		Uart2_RX_buffer_counter = 0;
		CLEAR_FLAG(Uart2_u8Flags,UART_RX_INDICATION_FLAG);
		CLEAR_FLAG(Uart2_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		//Uart2_u16LastReadIndex=0;
		LocalReturn = E_OK;
		break;
#endif
#if(UART3_ENABLE==STD_ON)
	case UART_CH3:
		memset(Uart3_RX_buffer,0,UART3_BUFFER_LENGTH);
		Uart3_RX_buffer_counter = 0;
		CLEAR_FLAG(Uart3_u8Flags,UART_RX_INDICATION_FLAG);
		CLEAR_FLAG(Uart3_u8Flags,UART_RX_BUFFER_OVERFLOW_FLAG);
		//Uart3_u16LastReadIndex=0;
		LocalReturn = E_OK;
		break;
#endif
	default:
		LocalReturn = E_NOK;
		break;
	}
	return LocalReturn;
}

/******************************************************************/


/******************************************************************/
/********************** Read RX buffers ***************************/
/******************************************************************/

#if(UART1_ENABLE==STD_ON)
uint16_t UART1_u16ReadRxBuffer(uint8_t * outputBuf)
{
	memcpy(outputBuf,Uart1_RX_buffer,Uart1_RX_buffer_counter);
    //Uart1_u16LastReadIndex=Uart1_RX_buffer_counter-1;
	return Uart1_RX_buffer_counter;
}
#endif

#if(UART2_ENABLE==STD_ON)
uint16_t UART2_u16ReadRxBuffer(uint8_t * outputBuf)
{
	memcpy(outputBuf,Uart2_RX_buffer,Uart2_RX_buffer_counter);
    //Uart2_u16LastReadIndex=Uart2_RX_buffer_counter-1;
	return Uart2_RX_buffer_counter;
}
#endif

#if(UART3_ENABLE==STD_ON)
uint16_t UART3_u16ReadRxBuffer(uint8_t * outputBuf)
{
	memcpy(outputBuf,Uart3_RX_buffer,Uart3_RX_buffer_counter);
    //Uart3_u16LastReadIndex=Uart3_RX_buffer_counter-1;
	return Uart3_RX_buffer_counter;
}
#endif

uint16_t UART_u16ReadRxBuffer(Uart_udtChannelType Channel,uint8_t * outputBuf)
{
	uint16_t LocalReturn = 0;
	switch (Channel)
	{
#if(UART1_ENABLE==STD_ON)
	case UART_CH1:
		memcpy(outputBuf,Uart1_RX_buffer,Uart1_RX_buffer_counter);
        //Uart1_u16LastReadIndex=Uart1_RX_buffer_counter-1;
		LocalReturn = Uart1_RX_buffer_counter;
		break;
#endif
#if(UART2_ENABLE==STD_ON)
	case UART_CH2:
		memcpy(outputBuf,Uart2_RX_buffer,Uart2_RX_buffer_counter);
        //Uart2_u16LastReadIndex=Uart2_RX_buffer_counter-1;
		LocalReturn = Uart2_RX_buffer_counter;
		break;
#endif
#if(UART3_ENABLE==STD_ON)
	case UART_CH3:
		memcpy(outputBuf,Uart3_RX_buffer,Uart3_RX_buffer_counter);
        //Uart3_u16LastReadIndex=Uart3_RX_buffer_counter-1;
		LocalReturn = Uart3_RX_buffer_counter;
		break;
#endif
	default:
		LocalReturn = 0;
		break;
	}
	return LocalReturn;
}

/******************************************************************/




/******************************************************************/
/************************* Send byte ******************************/
/******************************************************************/

#if(UART1_ENABLE==STD_ON)
std_returnType UART1_udtSendByte(uint8_t copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart1,&copy_u8Byte,1,100);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART2_ENABLE==STD_ON)
std_returnType UART2_udtSendByte(uint8_t copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart2,&copy_u8Byte,1,100);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART3_ENABLE==STD_ON)
std_returnType UART3_udtSendByte(uint8_t copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart3,&copy_u8Byte,1,100);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

std_returnType UART_udtSendByte(Uart_udtChannelType Channel,uint8_t copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	switch (Channel)
	{
#if(UART1_ENABLE==STD_ON)
	case UART_CH1:
		sendStatus=HAL_UART_Transmit(&huart1,&copy_u8Byte,1,100);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART2_ENABLE==STD_ON)
	case UART_CH2:
		sendStatus=HAL_UART_Transmit(&huart2,&copy_u8Byte,1,100);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART3_ENABLE==STD_ON)
	case UART_CH3:
		sendStatus=HAL_UART_Transmit(&huart3,&copy_u8Byte,1,100);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
	default:
		LocalReturn = E_NOK;
		break;
	}
	return LocalReturn;
}

/******************************************************************/





/******************************************************************/
/************************* Send Data ******************************/
/******************************************************************/

#if(UART1_ENABLE==STD_ON)
std_returnType UART1_udtSendData(uint8_t * copy_u8Byte, uint16_t size)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart1,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART2_ENABLE==STD_ON)
std_returnType UART2_udtSendData(uint8_t * copy_u8Byte, uint16_t size)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart2,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART3_ENABLE==STD_ON)
std_returnType UART3_udtSendData(uint8_t * copy_u8Byte, uint16_t size)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	sendStatus=HAL_UART_Transmit(&huart3,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

std_returnType UART_udtSendData(Uart_udtChannelType Channel,uint8_t * copy_u8Byte, uint16_t size)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	switch (Channel)
	{
#if(UART1_ENABLE==STD_ON)
	case UART_CH1:
		sendStatus=HAL_UART_Transmit(&huart1,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART2_ENABLE==STD_ON)
	case UART_CH2:
		sendStatus=HAL_UART_Transmit(&huart2,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART3_ENABLE==STD_ON)
	case UART_CH3:
		sendStatus=HAL_UART_Transmit(&huart3,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
	default:
		LocalReturn = E_NOK;
		break;
	}
	return LocalReturn;
}

/******************************************************************/






/******************************************************************/
/************************* Send String ******************************/
/******************************************************************/

#if(UART1_ENABLE==STD_ON)
std_returnType UART1_udtSendString(uint8_t * copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	uint16_t size=0;
	size=strlen((const char *)copy_u8Byte);
	sendStatus=HAL_UART_Transmit(&huart1,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART2_ENABLE==STD_ON)
std_returnType UART2_udtSendString(uint8_t * copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	uint16_t size=0;
	size=strlen((const char *)copy_u8Byte);
	sendStatus=HAL_UART_Transmit(&huart2,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

#if(UART3_ENABLE==STD_ON)
std_returnType UART3_udtSendString(uint8_t * copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	uint16_t size=0;
	size=strlen((const char *)copy_u8Byte);
	sendStatus=HAL_UART_Transmit(&huart3,copy_u8Byte,size,10*size);
	if(HAL_OK==sendStatus)
	{
		LocalReturn=E_OK;
	}
	return LocalReturn;
}
#endif

std_returnType UART_udtSendString(Uart_udtChannelType Channel,uint8_t * copy_u8Byte)
{
	std_returnType LocalReturn = E_NOK;
	HAL_StatusTypeDef sendStatus;
	uint16_t size=0;
	size=strlen((const char *)copy_u8Byte);
	switch (Channel)
	{
#if(UART1_ENABLE==STD_ON)
	case UART_CH1:
		sendStatus=HAL_UART_Transmit(&huart1,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART2_ENABLE==STD_ON)
	case UART_CH2:
		sendStatus=HAL_UART_Transmit(&huart2,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
#if(UART3_ENABLE==STD_ON)
	case UART_CH3:
		sendStatus=HAL_UART_Transmit(&huart3,copy_u8Byte,size,10*size);
		if(HAL_OK==sendStatus)
		{
			LocalReturn=E_OK;
		}
		break;
#endif
	default:
		LocalReturn = E_NOK;
		break;
	}
	return LocalReturn;
}

/******************************************************************/

