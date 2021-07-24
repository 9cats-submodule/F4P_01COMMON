#include "main.h"
#include "cmsis_os.h"
#include "cmd_process.h"
#include "ADS8688.h"
#include "AD9959.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "fdacoefs.h"

/*!
 *  \brief  TIM1 配置 PRC, ARR
 *  \param  PRC 预分配系数
 *  \param  ARR 自动重装载值
 *  \
 */
void TIM1_CONFIG(u32 PRC,u32 ARR)
{
	__HAL_TIM_DISABLE(&htim1);
	__HAL_TIM_SET_PRESCALER(  &htim1, PRC);
	__HAL_TIM_SET_AUTORELOAD( &htim1, ARR);
	__HAL_TIM_SET_COUNTER(    &htim1,   0);
	__HAL_TIM_ENABLE(&htim1);
}

/*!
 *  \brief  ADS8688 多通道 动态配置
 *  \param  CH 所选通道 (例 0b11011101)
 *  \param  range 通道范围
 *  \warn!  初始化后120ms左右内采样值不精确
 */
void ADS8688_MUL_CONFIG(u8 CH,u8 range)
{
	CH_NUM = 0;
	ADS8688_CONFIG(CH,0x01);
	while(CH)
	{
		CH_NUM += CH & 0x01;
		CH >>= 1;
	}
}

/*!
 *  \brief  AD9959 动态配置
 *  \param  freq 频率
 *  \param  amp  幅度
 *  \warn!  初始化后需要一定时间
 */
void AD9959_CONFIG(float freq,float mv)
{
	//只有通道1 和 通道3可用
	Out_freq(2, freq);
	Out_mV(2, mv);
}

/*!
 *  \brief  开启 TIM1 定时采样一定点数
 *  \param  point 每个通道的采样点数
 */
void ADS8688_SAMPLE(u16 point)
{
	SAMPLE_POINT = CH_NUM * point;
	__HAL_TIM_SET_COUNTER( &htim1, 0);
	__HAL_TIM_ENABLE_IT(   &htim1, TIM_IT_UPDATE);
	while(SAMPLE_FINISHED == NO)
		osDelay(1);
	SAMPLE_FINISHED = NO;
//	while(osSemaphoreAcquire(SAMPLE_FINISHEDHandle, 0) != osOK)
//		osDelay(1);
}

/*!
 *  \brief    FFT变换
 *  \param    CH 所选通道 (0~CH_NUL)
 *  \detail   执行后 FFT_OUTPUT 和 FFT_OUTPUT_REAL 存下结果
 */
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

/*!
 *  \brief    THD 求失真度
 *  \param    index 对应基波的频率
 *  \detail   要先进行 FFT
 */
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

/*!
 *  \brief    FFT滤波
 *  \param    CH 所选通道 (0~CH_NUL)
 *  \param    point 点数
 */
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

/*!
 *  \brief  主任务
 */
void MainTask_Start(void const *argument) {
	TIM1_CONFIG(25-1,210-1);						//采样率 32K
	ADS8688_MUL_CONFIG(0b00000100,2);		//ADS 3通道开启，±5.12 V
//	AD9959_CONFIG(1000,300);						//DDS 3通道开启，1KHZ，300mV

	osDelay(300);

	for(;;){
		ADS8688_SAMPLE(2248);
		FFT(0);
		FIR(0,2048);

		//波形显示
		{
			u16 i=0,j=0;
			u8 raiseTime=0,fallTime=0;
			u8 DATA_SHOW[512];
			//先得到上升沿
			for(i=200;i<500;i++)
			{
				if(FIR_OUTPUT[i] > FIR_OUTPUT[i-1])raiseTime++;
				else raiseTime = 0;
				if(raiseTime == 3)break;
			}
			//在下降点触发
			for(;i<500;i++)
			{
				if(FIR_OUTPUT[i] < FIR_OUTPUT[i-1])fallTime++;
				else fallTime=0;
				if(fallTime == 3)break;
			}

			for(j=0;j<256;j++)
			{
				DATA_SHOW[j] = FIR_INPUT[i+j]*128/5 + 128;
			}

			GraphChannelDataAdd(1,7,1,DATA_SHOW,256);
		}
		//失真度显示
		{
			SetTextValue(1, 41, Str("%.2f%%",THD(64)*100));
		}

		osDelay(1000);
	}
}


//		FFT(0);
//		{
//			u16 i;
//			for(i=0;i<2048;i++)
//			{
//				OutData[0] = (float)ADS8688_BUF[0][i] - Svar.ADS_OFFSET_ALL;
//				OutData[1] = FFT_INPUT[i];
//				OutData[2] = FFT_OUTPUT[i];
//				OutData[3] = i<1024?FFT_OUTPUT_REAL[i]:0;
//				OutPut_Data();
//				osDelay(1);
//			}
//		}

//		FIR(0,2048);
//		{
//			u16 i;
//			for(i=0;i<2048;i++)
//			{
//				OutData[0] = FIR_INPUT[i]*4000;
//				OutData[1] = FIR_OUTPUT[i]*4000;
//				OutPut_Data();
//				osDelay(1);
//			}
//		}
