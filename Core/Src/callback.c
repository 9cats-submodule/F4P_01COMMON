#include "main.h"
#include "stm32f4xx_it.h"

#include "usart.h"
#include "spi.h"
#include "cmsis_os.h"
#include "ADS8688.h"
#include "cmd_process.h"
#include "cmd_queue.h"

//-------------------ADS8688接收和发送BUF-----------------
static u8  rxbuf [4]    = {0};
static u8  txbuf [2]    = {0};
//--------------------------------------------------------

//-------------------------------标志---------------------------------------------
u8 ADS8688_BUSY   = 0;     //ADS8688 DMA接收还未完成
u8 FreMeasure_STA = 0;     //等距测量状态 0-预备 1-初次捕获 2-正在 3-过阈值 4-完成
float RefFrequency = 84001168.0f;
//--------------------------------------------------------------------------------
void TIM1_PeriodElapsedCallback(void);  //TIM1 更新ISR--用于ADS采样

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6) HAL_IncTick(); // FreeRTOS 系统时钟
  if (htim == &htim1) TIM1_PeriodElapsedCallback();
  if (htim == &htim5) {
  	FreMeasure_STA=3;
  }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  static u32 CNT_First,CNT_Last;
  static u32 Ni=0,Nu=0;
  if (htim == &htim3) {
    switch(FreMeasure_STA) {
    	case 0:{
    		__HAL_TIM_SET_COUNTER(&htim5,0);
    		__HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);
    		FreMeasure_STA = 1;
    	};break;
    	case 1:{
    		CNT_First = __HAL_TIM_GET_COUNTER(&htim5);
    		Ni++;
    		FreMeasure_STA = 2;
    	}break;
    	case 2:{
    		Ni++;
    	}break;
    	case 3:{
    		CNT_Last = __HAL_TIM_GET_COUNTER(&htim5);
    		__HAL_TIM_DISABLE_IT(&htim5,TIM_IT_UPDATE);
    		Nu = (htim5.Instance->ARR+1) * (htim5.Instance->PSC+1) * 1 + CNT_Last - CNT_First;
    		TargetFrequency = Ni * RefFrequency / Nu;
    		Ni = Nu = 0;
    		FreMeasure_STA = 0;
    	}break;
    }
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart6)
	{
		huart6.RxState = HAL_UART_STATE_READY;
		__HAL_UNLOCK(&huart6);
		queue_push(RxBuffer);
		if(queue_find_cmd(cmd_buffer,CMD_MAX_SIZE))
		{
			osMessageQueuePut(USART6_RXHandle,cmd_buffer,0,0);
		}
		HAL_UART_Receive_IT(&huart6, &RxBuffer, 1);
	}
}

void TIM1_PeriodElapsedCallback(void) {
  static u16 i=0;
  static u8  IS_FIRST = 1; //是否第一次进入中断 （第一次进入中断无法获取到值）
  if(!ADS8688_BUSY) {
    //开启下一次扫描
    ADS8688_BUSY = 1;
    SAMPLE_BEGIN;  //重新拉低CS，ADS8688开始运输
  	if(IS_FIRST == YES) {
  		HAL_SPI_TransmitReceive_DMA(&hspi3, txbuf, rxbuf, 2);
  		IS_FIRST = NO;
  	}
  	else {
  		ADS8688_BUF[i%CH_NUM][i/CH_NUM] = *(u16*)(&rxbuf[2]); //将采样值储存在BUF中
  		HAL_SPI_TransmitReceive_DMA(&hspi3, txbuf, rxbuf, 2);

  		if(++i == SAMPLE_POINT) {
  			//定时器任务结束
  			i=0;
  			SAMPLE_FINISHED = IS_FIRST = YES;
  			__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_UPDATE);
  		}
  	}
  }
  else
  {
  //正常情况无法到此处
    ADS8688_BUSY = ADS8688_BUSY;
  }
}

