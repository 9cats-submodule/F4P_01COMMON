#ifndef __DATA_H
#define __DATA_H
#include "base.h"
#include "cmsis_os2.h"
#include "FreeRTOSConfig.h"

extern u8 MEM_CCMRAM[][1024];

typedef struct _SVAR
{
  float ADS_AMP;        //所有ADS倍数补偿
  u16   ADS_OFFSET_ALL; //所有ADS的偏置补偿
}SVAR;
extern SVAR Svar;

//全局通用变量
extern u8 MODE;   //当前模式
extern u8 CH_NUM; //所选通道总数

//FreeRTOS--任务信息量句柄
extern osMessageQueueId_t USART6_RXHandle;
extern osSemaphoreId_t    TFT_TX_LEDHandle;
extern osSemaphoreId_t    TFT_RX_LEDHandle;
// ADS8688 采样完成信号量
extern u8  SAMPLE_FINISHED;
//用于 ADS8688 采样
#define SAMPLE_POINT_MAX 2048
#define SAMPLE_CH_MAX 2
extern u32 SAMPLE_POINT;
extern u16 ADS8688_BUF[][SAMPLE_POINT_MAX+200];
//FFT变换用
extern float FFT_INPUT[];
extern float FFT_OUTPUT[];
extern float FFT_OUTPUT_REAL[];
//FIR滤波用
extern u16   blockSize; //调用一次fir处理的采样点个数
extern float FIR_INPUT[];
extern float FIR_OUTPUT[];
extern float FIR_STATE[];
//等距采样
extern float TargetFrequency;
//ESP8266
#define ESP8266_RX_MAX 1024
extern u8  ESP8266_TX_BUF [50] ;
extern u8  ESP8266_RX_BUF [ESP8266_RX_MAX];
extern u8  ESP8266_ACK_BUF[10] ;
extern u8  ESP8266_ACK_Size    ;
extern u8  ESP8266_ACK_STA     ;
extern u16 ESP8266_Timeout_Tick;
extern u8  ESP8266_Response[ESP8266_RX_MAX];
extern u8* ESP8266_Response_Ptr;
//------以下基本不用动-------
extern u8 RxBuffer; //USART1接收BUF
#endif
