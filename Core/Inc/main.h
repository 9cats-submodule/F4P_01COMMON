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
#define _EXR __attribute__((section(".ex_sram")))
#define _RAM __attribute__((section(".RamFunc")))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
