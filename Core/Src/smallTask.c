#include "main.h"
#include "cmsis_os.h"
#include "cmd_process.h"
#include "semphr.h"


/*!
 *  \brief    变量自动存储
 *  \details  每隔0.1s储存一次数据，优先级最低
 */
void FLASH_Data_AutoUpdate_Start(void *arguement)	{
	for(;;)
	{
		DATA_UPDATE();
		osDelay(100);
	}
}

/*!
 *  \brief    TFT串口指令处理
 *  \details  当USART1串口接收到TFT的指令时接触阻塞
 */
void TFT_CMD_Process_Start(void *argument)	{
	CTRL_MSG   TFT_CMD_MSG = {0};

  for(;;)
  {
  	if(USART1_RXHandle != NULL)
  	{
  		if(osMessageQueueGet(USART1_RXHandle, &TFT_CMD_MSG, 0, 0) == osOK)
  		{
  				ProcessMessage(&TFT_CMD_MSG,0);
  				osSemaphoreRelease(TFT_RX_LEDHandle);
  		}
  		osDelay(20);
  	}
  	osDelay(20);
  }
}

/*!
 *  \brief    TFT-发送 LED0 闪烁
 *  \details  每次发送一次指令, LED0 闪烁一次，持续0.02 s
 */
void StartLED0Toggle(void const *argument) {
	for (;;) {
		if(osSemaphoreAcquire(TFT_TX_LEDHandle , 0) == osOK)
		{
			LED0_ON;
			osDelay(20);
			LED0_OFF;
		}
		osDelay(20);
	}
}

/*!
 *  \brief    TFT-接收 LED1 闪烁
 *  \details  每处理一次指令, LED1 闪烁一次,持续 0.02 s
 */
void StartLED1Toggle(void const *argument) {
  for (;;) {
		if(osSemaphoreAcquire(TFT_RX_LEDHandle , 0) == osOK)
  	{
    	LED1_ON;
    	osDelay(20);
    	LED1_OFF;
  	}
		osDelay(20);
  }
}

/*!
 *  \brief    0.6s LED2 闪烁一次
 */
void StartLED2Toggle(void *argument)	{
  for(;;)
  {
  	LED2_ON;
  	osDelay(300);
  	LED2_OFF;
  	osDelay(300);
  }
}

