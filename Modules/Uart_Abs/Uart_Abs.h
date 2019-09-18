/*
 * Uart_Abs.h
 *
 *  Created on: Jul 28, 2018
 *      Author: Maged
 */

#ifndef MODULES_UART_ABS_UART_ABS_H_
#define MODULES_UART_ABS_UART_ABS_H_
#include "Types.h"

#define TEST_UART STD_OFF

#define UARTX_BUFFER_LENGTH  128
#define UART1_BUFFER_LENGTH  UARTX_BUFFER_LENGTH
#define UART2_BUFFER_LENGTH  UARTX_BUFFER_LENGTH
#define UART3_BUFFER_LENGTH  UARTX_BUFFER_LENGTH


#define UART1_ENABLE  STD_ON
#define UART2_ENABLE  STD_ON
#define UART3_ENABLE  STD_OFF


#define UART_RX_INDICATION_FLAG         (uint8_t)0x01
#define UART_RX_BUFFER_OVERFLOW_FLAG    (uint8_t)0x02

#define GET_FLAG(x,y)	 ((x)&(y))
#define SET_FLAG(x,y)	 (x=(x|y))
#define CLEAR_FLAG(x,y)  (x=(x&(~y)))


typedef enum {UART_CH1=1,UART_CH2=2,UART_CH3=3} Uart_udtChannelType;
typedef enum {UART_OK=1,UART_NOK,UART_OVERFLOW} Uart_udtStatusType;


extern void UART_voidInit(void);
extern void UART1_voidInit(void);
extern void UART2_voidInit(void);
extern void UART3_voidInit(void);
extern void UART_voidDeinit(void);
extern void UART1_voidDeinit(void);
extern void UART2_voidDeinit(void);
extern void UART3_voidDeinit(void);
extern void UART1_voidFlushRxBuffer(void);
extern void UART2_voidFlushRxBuffer(void);
extern void UART3_voidFlushRxBuffer(void);
extern std_returnType UART_udtFlushRxBuffer(Uart_udtChannelType Channel);
extern uint16_t UART1_u16ReadRxBuffer(uint8_t * outputBuf);
extern uint16_t UART2_u16ReadRxBuffer(uint8_t * outputBuf);
extern uint16_t UART3_u16ReadRxBuffer(uint8_t * outputBuf);
extern uint16_t UART_u16ReadRxBuffer(Uart_udtChannelType Channel,uint8_t * outputBuf);
extern std_returnType UART1_udtSendByte(uint8_t copy_u8Byte);
extern std_returnType UART2_udtSendByte(uint8_t copy_u8Byte);
extern std_returnType UART3_udtSendByte(uint8_t copy_u8Byte);
extern std_returnType UART_udtSendByte(Uart_udtChannelType Channel,uint8_t copy_u8Byte);
extern std_returnType UART1_udtSendData(uint8_t * copy_u8Byte, uint16_t size);
extern std_returnType UART2_udtSendData(uint8_t * copy_u8Byte, uint16_t size);
extern std_returnType UART3_udtSendData(uint8_t * copy_u8Byte, uint16_t size);
extern std_returnType UART_udtSendData(Uart_udtChannelType Channel,uint8_t * copy_u8Byte, uint16_t size);
extern std_returnType UART1_udtSendString(uint8_t * copy_u8Byte);
extern std_returnType UART2_udtSendString(uint8_t * copy_u8Byte);
extern std_returnType UART3_udtSendString(uint8_t * copy_u8Byte);
extern std_returnType UART_udtSendString(Uart_udtChannelType Channel,uint8_t * copy_u8Byte);


#if(TEST_UART==STD_ON)
extern void UART_test_task(void);
#endif

#endif /* MODULES_UART_ABS_UART_ABS_H_ */
