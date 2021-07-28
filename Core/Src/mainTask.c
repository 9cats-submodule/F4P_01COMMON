#include "main.h"
#include "ADS8688.h"
#include "AD9959.h"
#include "hmi_driver.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "fdacoefs.h"

///*!
// *  \brief  TIM1 配置 PRC, ARR
// *  \param  PRC 预分配系数
// *  \param  ARR 自动重装载值
// */
void TIM1_CONFIG(u32 PRC,u32 ARR)
{
	__HAL_TIM_DISABLE(&htim1);
	__HAL_TIM_SET_PRESCALER(  &htim1, PRC);
	__HAL_TIM_SET_AUTORELOAD( &htim1, ARR);
	__HAL_TIM_SET_COUNTER(    &htim1,   0);
	__HAL_TIM_ENABLE(&htim1);
}
//
///*!
// *  \brief  ADS8688 多通道 动态配置
// *  \param  CH 所选通道 (例 0b11011101)
// *  \param  range 通道范围
// *  \warn!  初始化后120ms左右内采样值不精确
// */
void ADS8688_MUL_CONFIG(u8 CH,u8 range)
{
	CH_NUM = 0;
	ADS8688_CONFIG(CH,range);
	while(CH)
	{
		CH_NUM += CH & 0x01;
		CH >>= 1;
	}
}
//
///*!
// *  \brief  AD9959 动态配置
// *  \param  freq 频率
// *  \param  amp  幅度
// *  \warn!  初始化后需要一定时间
// */
void AD9959_CONFIG(float freq,float mv)
{
	//只有通道1 和 通道3可用
	Out_freq(2, freq);
	Out_mV(2, mv);
}

///*!
// *  \brief  开启 TIM1 定时采样一定点数
// *  \param  point 每个通道的采样点数
// */
void ADS8688_SAMPLE(u16 point)
{
	SAMPLE_POINT = CH_NUM * point;
	__HAL_TIM_SET_COUNTER( &htim1, 0);
	__HAL_TIM_ENABLE_IT(   &htim1, TIM_IT_UPDATE);
	while(SAMPLE_FINISHED == NO)
		osDelay(1);
	SAMPLE_FINISHED = NO;
}
//
///*!
// *  \brief    FFT变换
// *  \param    CH 所选通道 (0~CH_NUL)
// *  \detail   执行后 FFT_OUTPUT 和 FFT_OUTPUT_REAL 存下结果
// */
void FFT(u8 CH)
{
	arm_rfft_fast_instance_f32 S;
	u16 i;

	for(i=0;i<2048;i++)
	{
		FFT_INPUT[i] = ((float)ADS8688_BUF[CH][i] - Svar.ADS_OFFSET_ALL)*Svar.ADS_AMP/0x10000;
	}
	arm_rfft_fast_init_f32(&S,2048);                    //FFT初始化
	arm_rfft_fast_f32(&S, FFT_INPUT, FFT_OUTPUT,0);     //FFT变化
	arm_cmplx_mag_f32(FFT_OUTPUT,FFT_OUTPUT_REAL,2048); //求模
}
//
///*!
// *  \brief    THD 求失真度
// *  \param    index 对应基波的频率
// *  \detail   要先进行 FFT
// */
float THD(u16 index)
{
  //基波
  float basic = FFT_OUTPUT_REAL[index];
  //谐波
  float harmon[5],harmon_power,high;
  u8 i;

  for(i=0;i<5;i++)
  {
  	harmon[i] = FFT_OUTPUT_REAL[index*(i+2)];
  }
  arm_power_f32(harmon, 5, &harmon_power);
  arm_sqrt_f32(harmon_power,&high);

  return high / basic;
}
//
///*!
// *  \brief    FFT滤波
// *  \param    CH 所选通道 (0~CH_NUL)
// *  \param    point 点数
// */
void FIR(u8 CH,u32 point)
{
	u32 i;
	arm_fir_instance_f32 S;
	u16 numBlocks = point/blockSize; //需要调用arm_fir_f32的次数

	/* 初始化输入缓存 */
	for(i=0;i<point;i++)
		FIR_INPUT[i] = ((float)ADS8688_BUF[CH][i] - Svar.ADS_OFFSET_ALL)*Svar.ADS_AMP/0x10000;

	/* 初始化结构体S */
	arm_fir_init_f32(&S, firCoeffsNum,(float*)firCoeffs, FIR_STATE, blockSize);

	/* 实现FIR滤波 */
	for(i=0;i<numBlocks;i++)
		arm_fir_f32(&S, FIR_INPUT + (i * blockSize), FIR_OUTPUT + (i * blockSize), blockSize);
}

///*!
// *  \brief  主任务
// */

void MainTask_Start(void *argument)
{
  /* Infinite loop */
	TIM1_CONFIG(25-1,210-1);						//采样率 32K
	ADS8688_MUL_CONFIG(0b00000100,2);		//ADS 3通道开启，±5.12 V
	osDelay(300);

	for(;;){
		SetTextValue(1, 41, (u8*)"233");
		osDelay(1000);
	}
}
