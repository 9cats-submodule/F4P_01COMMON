#include "base.h"
#include "stdio.h"

const u32 SAVE_ADDR = 0x0000f000;//FLASH储存地址
u8 STR_BUF[200]={0};

/*!
 *  \brief 按键扫描函数
 *  \param mode 是否支持连按
 */
//按键扫描函数
//不使用时注释
u8 KEY_Scan(u8 mode) {
	static u8 key_up = 1; //按键按松开标志
	if (mode)
		key_up = 1; //持连按
	if (key_up && (KEY0 == 0 || KEY1 == 0)) {
		HAL_Delay(10); //去抖动
		key_up = 0;
		if      (KEY0 == 0)
			return KEY0_PRES;
		else if (KEY1 == 0)
			return KEY1_PRES;
	} else if (KEY0 == 1 && KEY1 == 1)
		key_up = 1;
	return 0; // 按键按下
}

/*!
 *  \brief  数据保存操作，0-写入 1-读出 2-写入
 *  \param mode 操作模式
 */
void DATA_OP(u8 mode)
{
  u8 *VAR_ADDR   = (u8*)&Svar; //变量地址
  u32 FLASH_ADDR = SAVE_ADDR ; //FLASH储存首地址
  u8  data;                    //暂存数据
  u16 size;                    //当前已经储存大小

  for(size=0;size<sizeof(SVAR);size++,VAR_ADDR++,FLASH_ADDR++)
  {
		switch(mode)
		{
			case 0:W25QXX_Write(VAR_ADDR,FLASH_ADDR,1);break;
			case 1:W25QXX_Read (VAR_ADDR,FLASH_ADDR,1);break;
			case 2:{
					W25QXX_Read (&data,FLASH_ADDR,1);
				if(data != *VAR_ADDR) W25QXX_Write(VAR_ADDR,FLASH_ADDR,1);
			}
		}
  }
}

/*!
 *  \brief 数据初始化，若按下KEY0则恢复默认
 */
void DATA_INIT() {
  u8 key = KEY_Scan(0);
  if(key == KEY0_PRES)  DATA_OP(0);
  else                  DATA_OP(1);
}

/*!
 *  \brief 数据更新
 */
void DATA_UPDATE() {
    DATA_OP(2);
}
