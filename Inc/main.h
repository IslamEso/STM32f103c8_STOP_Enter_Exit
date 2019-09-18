/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define UART_DEBUG 1
#define BuiltIn_LED_Pin GPIO_PIN_13
#define BuiltIn_LED_GPIO_Port GPIOC
#undef RTC_BKP_NUMBER
#define RTC_BKP_NUMBER 42
#define RTC_BKP_DR11                        0x00000010U
#define RTC_BKP_DR12                        0x00000011U
#define RTC_BKP_DR13                        0x00000012U
#define RTC_BKP_DR14                        0x00000013U
#define RTC_BKP_DR15                        0x00000014U
#define RTC_BKP_DR16                        0x00000015U
#define RTC_BKP_DR17                        0x00000016U
#define RTC_BKP_DR18                        0x00000017U
#define RTC_BKP_DR19                        0x00000018U
#define RTC_BKP_DR20                        0x00000019U
#define RTC_BKP_DR21                        0x0000001AU
#define RTC_BKP_DR22                        0x0000001BU
#define RTC_BKP_DR23                        0x0000001CU
#define RTC_BKP_DR24                        0x0000001DU
#define RTC_BKP_DR25                        0x0000001EU
#define RTC_BKP_DR26                        0x0000001FU
#define RTC_BKP_DR27                        0x00000020U
#define RTC_BKP_DR28                        0x00000021U
#define RTC_BKP_DR29                        0x00000022U
#define RTC_BKP_DR30                        0x00000023U
#define RTC_BKP_DR31                        0x00000024U
#define RTC_BKP_DR32                        0x00000025U
#define RTC_BKP_DR33                        0x00000026U
#define RTC_BKP_DR34                        0x00000027U
#define RTC_BKP_DR35                        0x00000028U
#define RTC_BKP_DR36                        0x00000029U
#define RTC_BKP_DR37                        0x0000002AU
#define RTC_BKP_DR38                        0x0000002BU
#define RTC_BKP_DR39                        0x0000002CU
#define RTC_BKP_DR40                        0x0000002DU
#define RTC_BKP_DR41                        0x0000002EU
#define RTC_BKP_DR42                        0x0000002FU





void RTC_AlarmConfig(void);
void RTC_SetDate(uint8_t Date, uint8_t Month, uint8_t Year);
void RTC_SetTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
void	RTC_SetAlarmTo(uint8_t Hours, uint8_t Minutes, uint8_t Seconds);
void RTC_SetAlarmAfterXsec(uint16_t seconds);

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define USART2_TX_LORA_Pin GPIO_PIN_2
#define USART2_TX_LORA_GPIO_Port GPIOA
#define USART2_RX_LORA_Pin GPIO_PIN_3
#define USART2_RX_LORA_GPIO_Port GPIOA
#define ADC1_IN4_PA4_PRESSURE_Pin GPIO_PIN_4
#define ADC1_IN4_PA4_PRESSURE_GPIO_Port GPIOA
#define ADC1_IN5_PA5_SENSOR2_Pin GPIO_PIN_5
#define ADC1_IN5_PA5_SENSOR2_GPIO_Port GPIOA
#define GPIO_OUTPUT_LORA_PA6_Pin GPIO_PIN_6
#define GPIO_OUTPUT_LORA_PA6_GPIO_Port GPIOA
#define GPIO_OUTPUT_LORA_PA7_Pin GPIO_PIN_7
#define GPIO_OUTPUT_LORA_PA7_GPIO_Port GPIOA
#define GPIO_INPUT_LORA_PB1_Pin GPIO_PIN_1
#define GPIO_INPUT_LORA_PB1_GPIO_Port GPIOB
#define USER_GSM_POWER_Pin GPIO_PIN_8
#define USER_GSM_POWER_GPIO_Port GPIOA
#define USART1_TX_GSM_Pin GPIO_PIN_9
#define USART1_TX_GSM_GPIO_Port GPIOA
#define USART1_RX_GSM_Pin GPIO_PIN_10
#define USART1_RX_GSM_GPIO_Port GPIOA
#define GPIO_OP_PA11_DCDC_EN_Pin GPIO_PIN_11
#define GPIO_OP_PA11_DCDC_EN_GPIO_Port GPIOA
#define SD_SCK_Pin GPIO_PIN_3
#define SD_SCK_GPIO_Port GPIOB
#define SD_MISO_Pin GPIO_PIN_4
#define SD_MISO_GPIO_Port GPIOB
#define SD_MOSI_Pin GPIO_PIN_5
#define SD_MOSI_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_6
#define SD_CS_GPIO_Port GPIOB
#define GSM_RESET_Pin GPIO_PIN_9
#define GSM_RESET_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
