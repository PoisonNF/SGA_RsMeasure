#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"
#include "task_ds3231.h"

//�洢��ǰϵͳʱ��
tagDS3231Time_T SysTime;

//DS3231��ȡʱ��
void Task_DS3231_ReadTime(void)
{
    //��ȡ��ǰʱ��ֵ���浽SysTime�С��ٴ洢��ȫ�ֱ���TurnOnTime��
    if(OCD_DS3231_TimeGetHex(&DS3231,&SysTime))
    {
        TurnOnTime[0] = SysTime.ucYear;
        TurnOnTime[1] = SysTime.ucMonth;
        TurnOnTime[2] = SysTime.ucDate;
        TurnOnTime[3] = SysTime.ucHour;
        TurnOnTime[4] = SysTime.ucMinute;
    }
}

//DS3231���ÿ�ʼ����ʱ��
void Task_DS3231_SetOnTime(void)
{
    //��ǰ��������һС��60
	if(TurnOnTime[4] + 1 < 60)
	{
		//��ʼʱ��Ϊ1���Ӻ�
		TurnOnTime[4] = TurnOnTime[4] + 1;
	}
	else	
	{
		//����60��Ҫ��λ��Сʱ������
		TurnOnTime[4] = TurnOnTime[4] + 1 - 60;
		
		//Сʱ��������23����ֱ�Ӽ�һ
		if(TurnOnTime[3] < 23)			
			TurnOnTime[3] = TurnOnTime[3] + 1;										
		else	//����23ֱ�����㣬����ڶ���
			TurnOnTime[3] = 0;
	}
}

