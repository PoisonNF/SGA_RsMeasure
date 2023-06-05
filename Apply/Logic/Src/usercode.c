#include "usercode.h"		/* usercode头文件 */
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "task_conf.h"      /* task层头文件配置 */
#include "ocd_conf.h"       /* OCD层头文件配置 */
#include "dev_conf.h"		/* Dev层头文件配置 */
#include "algo_conf.h"		/* Algo层头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

//从串口接收用于设置时间
uint8_t SetTime[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
//设置关闭时间
uint8_t TurnOffTime[5] = {0x00,0x00,0x00,0x00,0x00};
//设置开启时间
uint8_t TurnOnTime[5] = {0x00,0x00,0x00,0x00,0x00};
//工作状态标志位，0：未工作 1：正在工作
uint8_t WorkingFlag = 0;

//主循环执行次数
uint8_t MainRunCycle = 0;

/* 用户逻辑代码 */
void UserLogic_Code(void)
{
	//喂狗
	Drv_IWDG_Feed(&tIWDG);

	//DAC1初始输出1V
	Drv_DAC_SetValue(&tDAC[0],1);

	//读取当前时间
	Task_DS3231_ReadTime();

	//设置分钟值加1后开始测量
	Task_DS3231_SetOnTime();
	
	while(1)
	{
		Task_Measure();
	}
}
