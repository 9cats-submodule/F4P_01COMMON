#include "data.h"

//�ɴ������
SVAR Svar = {
  /*float ADS_AMP;        //����ADS��������*/  10.24f,
  /*u16   ADS_OFFSET_ALL; //����ADS��ƫ�ò���*/0x8000
};

//ȫ��ͨ�ñ���
u8 MODE = 0;   //��ǰģʽ
u8 CH_NUM = 0; //��ѡͨ������
// ADS8688 ��������ź���
u8  SAMPLE_FINISHED = 0;
//���� ADS8688 ����
u32 SAMPLE_POINT      =  0;
u16 ADS8688_BUF[SAMPLE_CH_MAX][SAMPLE_POINT_MAX+200] = {0};
//FFT�任��
float FFT_INPUT[SAMPLE_POINT_MAX]      ={0};
float FFT_OUTPUT[SAMPLE_POINT_MAX]     ={0};
float FFT_OUTPUT_REAL[SAMPLE_POINT_MAX]={0};
//FIR�˲���
u16 blockSize = 32; //��Ҫ����arm_fir_f32�Ĵ���
float FIR_INPUT[SAMPLE_POINT_MAX]      ={0};
float FIR_OUTPUT[SAMPLE_POINT_MAX]     ={0};
float FIR_STATE[200]      ={0};

//------���»������ö�-------
u8 RxBuffer; //USART1����BUF
