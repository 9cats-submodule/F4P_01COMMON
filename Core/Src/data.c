#include "data.h"

typedef struct HeapRegion
{
	uint8_t *pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;
//_CCM u8 MEM_CCMRAM[48 ][1024] = {0};

//可储存变量
SVAR Svar = {
  /*float ADS_AMP;        //所有ADS倍数补偿*/  10.24f,
  /*u16   ADS_OFFSET_ALL; //所有ADS的偏置补偿*/0x8000
};

//全局通用变量
u8 MODE = 0;   //当前模式
u8 CH_NUM = 0; //所选通道总数
// ADS8688 采样完成信号量
u8  SAMPLE_FINISHED = 0;
//用于 ADS8688 采样
u32 SAMPLE_POINT      =  0;
u16 ADS8688_BUF[SAMPLE_CH_MAX][SAMPLE_POINT_MAX+200] = {0};
//FFT变换用
float FFT_INPUT[SAMPLE_POINT_MAX]      ={0};
float FFT_OUTPUT[SAMPLE_POINT_MAX]     ={0};
float FFT_OUTPUT_REAL[SAMPLE_POINT_MAX]={0};
//FIR滤波用
u16 blockSize = 32; //需要调用arm_fir_f32的次数
float FIR_INPUT[SAMPLE_POINT_MAX]      ={0};
float FIR_OUTPUT[SAMPLE_POINT_MAX]     ={0};
float FIR_STATE[200]      ={0};

//------以下基本不用动-------
u8 RxBuffer; //USART1接收BUF

// FreeRTOS 堆栈区
_CCM u8 ucHeap[configTOTAL_HEAP_SIZE];
const HeapRegion_t xHeapRegions[] =
{
    { ucHeap, configTOTAL_HEAP_SIZE },
    { NULL, 0 }
};
