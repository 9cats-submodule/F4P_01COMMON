#ifndef __DATA_H
#define __DATA_H
#include "base.h"
#include "cmsis_os2.h"
#include "FreeRTOSConfig.h"

extern u8 MEM_CCMRAM[][1024];

typedef struct _SVAR
{
  float ADS_AMP;        //����ADS��������
  u16   ADS_OFFSET_ALL; //����ADS��ƫ�ò���
}SVAR;
extern SVAR Svar;

//ȫ��ͨ�ñ���
extern u8 MODE;   //��ǰģʽ
extern u8 CH_NUM; //��ѡͨ������

//FreeRTOS--������Ϣ�����
extern osMessageQueueId_t USART6_RXHandle;
extern osSemaphoreId_t    TFT_TX_LEDHandle;
extern osSemaphoreId_t    TFT_RX_LEDHandle;
// ADS8688 ��������ź���
extern u8  SAMPLE_FINISHED;
//���� ADS8688 ����
#define SAMPLE_POINT_MAX 2048
#define SAMPLE_CH_MAX 2
extern u32 SAMPLE_POINT;
extern u16 ADS8688_BUF[][SAMPLE_POINT_MAX+200];
//FFT�任��
extern float FFT_INPUT[];
extern float FFT_OUTPUT[];
extern float FFT_OUTPUT_REAL[];
//FIR�˲���
extern u16   blockSize; //����һ��fir����Ĳ��������
extern float FIR_INPUT[];
extern float FIR_OUTPUT[];
extern float FIR_STATE[];
//�Ⱦ����
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
//------���»������ö�-------
extern u8 RxBuffer; //USART1����BUF
#endif
