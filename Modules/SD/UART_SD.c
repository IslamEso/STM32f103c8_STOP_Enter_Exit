/**
 * @file 	UART_SD.c
 * @author 	Ahmed Hashesh
 * @date 	
 * @brief File contain the main functions used for the SD when configured to use the UART Interface.
 *
 * 
 */
 #include "SD_Config.h"


#ifdef MCAL_SD_DRIVER_UART_CONFIG_H_
#include "stm32f10x_usart.h"
#include "UART_SD.h"

void UART3_voidInit(void)
{
	USART_InitTypeDef USART_InitStruct;
	
	USART_StructInit(&USART_InitStruct);
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init( USART3, &USART_InitStruct);
	USART_ITConfig(USART3,  USART_IT_TXE,  ENABLE);
	USART_ITConfig(USART3,  USART_IT_RXNE,  ENABLE);
	USART_ITConfig(USART3,USART_IT_TC,ENABLE);
/*Enabling the USART 3 prepheral  */
	USART_Cmd(USART3, ENABLE);
}

void UART3_voidSendByte(u8 copy_u8Byte)
{
	/*to make sure that the last transmission is done*/
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==0);
	USART_ClearFlag(USART3,USART_FLAG_TC);
	/*send the data to the USART3 to handle the transmission*/
	USART_SendData(USART3, copy_u8Byte);
	

}

u8 UART3_voidReceiveByte(void)
{
	u8 Data_Recieved;
	while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) ==0);
	Data_Recieved = USART_ReceiveData(USART3);
	return Data_Recieved;
}

 void UART3_voidSendString(u8* copy_u8Byte, u8 SizeBytes)
{
	u8 i=0;
	while(i<SizeBytes)
	{
		UART3_voidSendByte(copy_u8Byte[i]);
		i++;
	}
}


void USART3_IRQHandler(void)
{

	/* interrupt generated if Transmission complete */
	if (USART_GetFlagStatus(USART3,USART_FLAG_TC))
	{
		USART_ClearFlag(USART3,USART_FLAG_TC);
		// the the code of handling
		//TODO[AH]: ADD logs for the data transmission completed
	}


	/* interrupt generated if Receive buffer not empty */
	if (USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
		USART_ClearFlag(USART3,USART_FLAG_RXNE);
		// the the code of handling

	}
}


#endif /* MCAL_SD_DRIVER_UART_CONFIG_H_ */
