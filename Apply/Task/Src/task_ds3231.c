#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"
#include "task_ds3231.h"

//存储当前系统时间
tagDS3231Time_T SysTime;

//DS3231读取时间
void Task_DS3231_ReadTime(void)
{
    //读取当前时间值保存到SysTime中。再存储到全局变量TurnOnTime中
    if(OCD_DS3231_TimeGetHex(&DS3231,&SysTime))
    {
        TurnOnTime[0] = SysTime.ucYear;
        TurnOnTime[1] = SysTime.ucMonth;
        TurnOnTime[2] = SysTime.ucDate;
        TurnOnTime[3] = SysTime.ucHour;
        TurnOnTime[4] = SysTime.ucMinute;
    }
}

//DS3231设置开始测量时间
void Task_DS3231_SetOnTime(void)
{
    //当前分钟数加一小于60
	if(TurnOnTime[4] + 1 < 60)
	{
		//开始时间为1分钟后
		TurnOnTime[4] = TurnOnTime[4] + 1;
	}
	else	
	{
		//超过60需要进位，小时数增加
		TurnOnTime[4] = TurnOnTime[4] + 1 - 60;
		
		//小时数不超过23可以直接加一
		if(TurnOnTime[3] < 23)			
			TurnOnTime[3] = TurnOnTime[3] + 1;										
		else	//等于23直接清零，代表第二天
			TurnOnTime[3] = 0;
	}
}

