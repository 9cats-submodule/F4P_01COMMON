#include "AD9959.h"
#include "base.h"
sweep_freq sweepfreq;
sinw_ave sinwave;

u8 CSR_DATA0[1] = {0x10}; // �� CH0 
u8 CSR_DATA1[1] = {0x20}; // �� CH1 
u8 CSR_DATA2[1] = {0x40}; // �� CH2 
u8 CSR_DATA3[1] = {0x80}; // �� CH3 

u8 FR2_DATA[2] = {0x00,0x00}; //default Value = 0x0000 
u8 CFR_DATA[3] = {0x00,0x03,0x02}; //default Value = 0x000302 

u8 CPOW0_DATA[2] = {0x00,0x00}; //default Value = 0x0000 @ = POW/2^14*360 

u8 LSRR_DATA[2] = {0x00,0x00}; //default Value = 0x---- 

u8 RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x-------- 

u8 FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

 //��ʱ 
void dds_delay(u32 length) 
{ 
	length = length*12; 
	while(length--);
}

//IO�ڳ�ʼ�� 
void Intserve(void) 
{ 
	AD9959_PWR_L; 
	AD9959_CS_H; 
	AD9959_SCLK_L; 
	AD9959_UPDATE_L; 
	AD9959_PS0_L; 
	AD9959_PS1_L; 
	AD9959_PS2_L; 
	AD9959_PS3_L; 
	AD9959_SDIO0_L; 
	AD9959_SDIO1_L; 
	AD9959_SDIO2_L; 
	AD9959_SDIO3_L; 
}
//AD9959��λ 
void IntReset(void) 
{ 
	AD9959_Reset_L;
	HAL_Delay(1);
	AD9959_Reset_H;
	HAL_Delay(30);
	AD9959_Reset_L; 
}
//AD9959�������� 
void IO_Update(void) 
{
	AD9959_UPDATE_L; 
	HAL_Delay(2);
	AD9959_UPDATE_H; 
	HAL_Delay(4);
	AD9959_UPDATE_L; 
}
/*-------------------------------------------- 
�������ܣ�������ͨ��SPI��AD9959д���� 
RegisterAddress: �Ĵ�����ַ 
NumberofRegisters: �����ֽ��� 
*RegisterData: ������ʼ��ַ 
temp: �Ƿ����IO�Ĵ��� 
----------------------------------------------*/ 
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp) 
{ 
	u8 ControlValue = 0; 
	u8 ValueToWrite = 0; 
	u8 RegisterIndex = 0; 
	u8 i = 0; 
	
	ControlValue = RegisterAddress; 
	//д���ַ 
	AD9959_SCLK_L;
	AD9959_CS_L;
	for(i=0; i<8; i++) 
	{ 
		AD9959_SCLK_L;
		if(0x80 == (ControlValue & 0x80)) AD9959_SDIO0_H; 
		else AD9959_SDIO0_L;
		AD9959_SCLK_H; 
		ControlValue <<= 1;
	}
	AD9959_SCLK_L; 
	//д������ 
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++) 
	{ 
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++) 
		{ 
			AD9959_SCLK_L; 
			if(0x80 == (ValueToWrite & 0x80)) AD9959_SDIO0_H; 
			else AD9959_SDIO0_L; 
			AD9959_SCLK_H; 
			ValueToWrite <<= 1;
		}
		AD9959_SCLK_L; 
	}
	if(temp==1) IO_Update();
	AD9959_CS_H;
}
/*--------------------------------------- 
�������ܣ�����ͨ�����Ƶ�� 
Channel: ���ͨ�� 
Freq: ���Ƶ�� 
---------------------------------------*/ 
void Write_frequence(u8 Channel,u32 Freq) 
{ 
	u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};//�м���� 
	u32 Temp; 
	Temp=(u32)Freq*8.589934592; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ� 4.294967296=(2^32)/500000000 
	
	CFTW0_DATA[3]=(u8)Temp; 
	CFTW0_DATA[2]=(u8)(Temp>>8); 
	CFTW0_DATA[1]=(u8)(Temp>>16); 
	CFTW0_DATA[0]=(u8)(Temp>>24);
	
	if(Channel==0) 
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ�� 
		WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ�� 
	}else if(Channel==1) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH1ͨ�� 
		WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH1�趨Ƶ�� 
	}
	else if(Channel==2) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH2ͨ�� 
		WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH2�趨Ƶ�� 
	}
	else if(Channel==3) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH3ͨ�� 
		WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.���CH3�趨Ƶ�� 
	} 
}
/*--------------------------------------- 
�������ܣ�����ͨ��������� 
Channel: ���ͨ�� 
Ampli: ������� 
---------------------------------------*/ 
void Write_Amplitude(u8 Channel, u16 Ampli) 
{ 
	u16 A_temp;//=0x23ff; 
	u8 ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout
	A_temp=Ampli|0x1000; 
	ACR_DATA[2] = (u8)A_temp; //��λ���� 
	ACR_DATA[1] = (u8)(A_temp>>8); //��λ���� 
	if(Channel==0) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
	else if(Channel==1) 
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
	else if(Channel==2) 
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
	else if(Channel==3) 
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
}
/*--------------------------------------- 
�������ܣ�����ͨ�������λ 
Channel: ���ͨ�� 
Phase: �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��) 
---------------------------------------*/ 
void Write_Phase(u8 Channel,u16 Phase) 
{
	u16 P_temp=0; 
	P_temp=(u16)Phase;
	CPOW0_DATA[1]=(u8)P_temp;
	CPOW0_DATA[0]=(u8)(P_temp>>8);
	if(Channel==0) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,0); 
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
	}
	else if(Channel==1) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,0);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
	}
	else if(Channel==2) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,0);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
	}
	else if(Channel==3) 
	{ 
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,0);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0); 
	}
}
	
//AD9959��ʼ�� 
void Init_AD9959(void) 
{ 
	u8 FR1_DATA[3] = {0xD0,0x00,0x00};//20��Ƶ Charge pump control = 75uA FR1<23> -- VCO gain control =0ʱ system clock below 160 MHz; 
	
	Intserve(); //IO�ڳ�ʼ�� 
	IntReset(); //AD9959��λ 
	
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//д���ܼĴ���1 
	
	HAL_Delay(200);
}

void Out_mV(u8 ch, float nmV) 
{ 
	nmV=nmV/500*1024; 
	if(nmV>1023)nmV=1023;//��Χ����
	Write_Amplitude(ch,nmV);
}
void Out_freq(u8 ch, u32 freq) 
{ 
	if(freq>FreqMax)freq=FreqMax; 
	if(freq<FreqMin)freq=FreqMin;//��Χ���� 
	Write_frequence(ch,freq); 
}

