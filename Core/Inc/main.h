/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "base.h"
#include "tim.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Measure(void);
void ScanFreq(void);
void FaultChecK(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY0_Pin GPIO_PIN_6
#define KEY0_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOF
#define DAC8563_SCK_Pin GPIO_PIN_14
#define DAC8563_SCK_GPIO_Port GPIOE
#define DAC8563_LD_Pin GPIO_PIN_15
#define DAC8563_LD_GPIO_Port GPIOE
#define DAC8563_SYN_Pin GPIO_PIN_10
#define DAC8563_SYN_GPIO_Port GPIOB
#define DAC8563_DIN_Pin GPIO_PIN_11
#define DAC8563_DIN_GPIO_Port GPIOB
#define DAC8563_CLR_Pin GPIO_PIN_12
#define DAC8563_CLR_GPIO_Port GPIOB
#define AD9959_GND_Pin GPIO_PIN_8
#define AD9959_GND_GPIO_Port GPIOD
#define AD9959_P0_Pin GPIO_PIN_9
#define AD9959_P0_GPIO_Port GPIOD
#define AD9959_PWR_Pin GPIO_PIN_10
#define AD9959_PWR_GPIO_Port GPIOD
#define AD9959_P1_Pin GPIO_PIN_11
#define AD9959_P1_GPIO_Port GPIOD
#define AD9959_REST_Pin GPIO_PIN_12
#define AD9959_REST_GPIO_Port GPIOD
#define AD9959_P2_Pin GPIO_PIN_13
#define AD9959_P2_GPIO_Port GPIOD
#define AD9959_IOUP_Pin GPIO_PIN_14
#define AD9959_IOUP_GPIO_Port GPIOD
#define AD9959_P3_Pin GPIO_PIN_15
#define AD9959_P3_GPIO_Port GPIOD
#define AD9959_CS_Pin GPIO_PIN_2
#define AD9959_CS_GPIO_Port GPIOG
#define AD9959_SD0_Pin GPIO_PIN_3
#define AD9959_SD0_GPIO_Port GPIOG
#define AD9959_SCLK_Pin GPIO_PIN_4
#define AD9959_SCLK_GPIO_Port GPIOG
#define AD9959_SD1_Pin GPIO_PIN_5
#define AD9959_SD1_GPIO_Port GPIOG
#define AD9959_SD3_Pin GPIO_PIN_6
#define AD9959_SD3_GPIO_Port GPIOG
#define AD9959_SD2_Pin GPIO_PIN_7
#define AD9959_SD2_GPIO_Port GPIOG
#define W25QXX_CS_Pin GPIO_PIN_8
#define W25QXX_CS_GPIO_Port GPIOG
#define TFT_USART_TX_Pin GPIO_PIN_6
#define TFT_USART_TX_GPIO_Port GPIOC
#define TFT_USART_RX_Pin GPIO_PIN_7
#define TFT_USART_RX_GPIO_Port GPIOC
#define DEBUG_USART_TX_Pin GPIO_PIN_9
#define DEBUG_USART_TX_GPIO_Port GPIOA
#define DEBUG_USART_RX_Pin GPIO_PIN_10
#define DEBUG_USART_RX_GPIO_Port GPIOA
#define ADS8688_CS_Pin GPIO_PIN_15
#define ADS8688_CS_GPIO_Port GPIOA
#define ADS8688_SCK_Pin GPIO_PIN_10
#define ADS8688_SCK_GPIO_Port GPIOC
#define ADS8688_MISO_Pin GPIO_PIN_11
#define ADS8688_MISO_GPIO_Port GPIOC
#define ADS8688_MOSI_Pin GPIO_PIN_12
#define ADS8688_MOSI_GPIO_Port GPIOC
#define ADS8688_DAISY_Pin GPIO_PIN_2
#define ADS8688_DAISY_GPIO_Port GPIOD
#define ADS8688_RST_Pin GPIO_PIN_3
#define ADS8688_RST_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_13
#define LED0_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOG
#define W24QXX_SCK_Pin GPIO_PIN_3
#define W24QXX_SCK_GPIO_Port GPIOB
#define W24QXX_MISO_Pin GPIO_PIN_4
#define W24QXX_MISO_GPIO_Port GPIOB
#define W24QXX_MOSI_Pin GPIO_PIN_5
#define W24QXX_MOSI_GPIO_Port GPIOB
#define AT24CXX_SCL_Pin GPIO_PIN_8
#define AT24CXX_SCL_GPIO_Port GPIOB
#define AT24CXX_SDA_Pin GPIO_PIN_9
#define AT24CXX_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define _CCM __attribute__((section(".ccmram")))
#define _RAM __attribute__((section(".RamFunc")))
extern u8 STR_BUF[200];
#define printf(...)  HAL_UART_Transmit(&huart1, (uint8_t *)STR_BUF,sprintf((char*)STR_BUF,__VA_ARGS__), 0xFFFF);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
