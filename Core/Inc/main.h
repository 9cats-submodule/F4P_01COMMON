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
#define KEY0_Pin GPIO_PIN_2
#define KEY0_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOE
#define TCS_Pin GPIO_PIN_13
#define TCS_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_8
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define TCLK_Pin GPIO_PIN_0
#define TCLK_GPIO_Port GPIOB
#define PEN_Pin GPIO_PIN_1
#define PEN_GPIO_Port GPIOB
#define DOUT_Pin GPIO_PIN_2
#define DOUT_GPIO_Port GPIOB
#define TDIN_Pin GPIO_PIN_11
#define TDIN_GPIO_Port GPIOF
#define W25Q128_CS_Pin GPIO_PIN_14
#define W25Q128_CS_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define DDS_P1_Pin GPIO_PIN_12
#define DDS_P1_GPIO_Port GPIOD
#define DDS_P0_Pin GPIO_PIN_13
#define DDS_P0_GPIO_Port GPIOD
#define DDS_P3_Pin GPIO_PIN_2
#define DDS_P3_GPIO_Port GPIOG
#define DDS_P2_Pin GPIO_PIN_3
#define DDS_P2_GPIO_Port GPIOG
#define DDS_NC_Pin GPIO_PIN_4
#define DDS_NC_GPIO_Port GPIOG
#define DDS_IOUP_Pin GPIO_PIN_5
#define DDS_IOUP_GPIO_Port GPIOG
#define DDS_CS_Pin GPIO_PIN_6
#define DDS_CS_GPIO_Port GPIOG
#define DDS_SCLK_Pin GPIO_PIN_7
#define DDS_SCLK_GPIO_Port GPIOG
#define DDS_SD0_Pin GPIO_PIN_8
#define DDS_SD0_GPIO_Port GPIOG
#define DDS_SD1_Pin GPIO_PIN_6
#define DDS_SD1_GPIO_Port GPIOC
#define DDS_SD2_Pin GPIO_PIN_7
#define DDS_SD2_GPIO_Port GPIOC
#define DDS_SD3_Pin GPIO_PIN_8
#define DDS_SD3_GPIO_Port GPIOC
#define DDS_REST_Pin GPIO_PIN_9
#define DDS_REST_GPIO_Port GPIOC
#define DDS_PWR_Pin GPIO_PIN_8
#define DDS_PWR_GPIO_Port GPIOA
#define TFT_UART_TX_Pin GPIO_PIN_9
#define TFT_UART_TX_GPIO_Port GPIOA
#define TFT_UART_RX_Pin GPIO_PIN_10
#define TFT_UART_RX_GPIO_Port GPIOA
#define ADS8688_CS_Pin GPIO_PIN_15
#define ADS8688_CS_GPIO_Port GPIOA
#define ADS8688_SCK_Pin GPIO_PIN_10
#define ADS8688_SCK_GPIO_Port GPIOC
#define ADS8688_MISO_Pin GPIO_PIN_11
#define ADS8688_MISO_GPIO_Port GPIOC
#define ADS8688_MOSI_Pin GPIO_PIN_12
#define ADS8688_MOSI_GPIO_Port GPIOC
#define ADS8688_GND_Pin GPIO_PIN_2
#define ADS8688_GND_GPIO_Port GPIOD
#define ADS8688_GNDD3_Pin GPIO_PIN_3
#define ADS8688_GNDD3_GPIO_Port GPIOD
#define IIC_SCL_Pin GPIO_PIN_8
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_9
#define IIC_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
