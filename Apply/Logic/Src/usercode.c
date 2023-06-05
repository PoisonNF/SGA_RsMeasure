#include "usercode.h"		/* usercodeͷ�ļ� */
#include "drv_hal_conf.h"   /* SGA��ͷ�ļ����� */
#include "task_conf.h"      /* task��ͷ�ļ����� */
#include "ocd_conf.h"       /* OCD��ͷ�ļ����� */
#include "dev_conf.h"		/* Dev��ͷ�ļ����� */
#include "algo_conf.h"		/* Algo��ͷ�ļ����� */
#include "config.h"			/* I/O����ͷ�ļ����� */

//�Ӵ��ڽ�����������ʱ��
uint8_t SetTime[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
//���ùر�ʱ��
uint8_t TurnOffTime[5] = {0x00,0x00,0x00,0x00,0x00};
//���ÿ���ʱ��
uint8_t TurnOnTime[5] = {0x00,0x00,0x00,0x00,0x00};
//����״̬��־λ��0��δ���� 1�����ڹ���
uint8_t WorkingFlag = 0;

//��ѭ��ִ�д���
uint8_t MainRunCycle = 0;

/* �û��߼����� */
void UserLogic_Code(void)
{
	//ι��
	Drv_IWDG_Feed(&tIWDG);

	//DAC1��ʼ���1V
	Drv_DAC_SetValue(&tDAC[0],1);

	//��ȡ��ǰʱ��
	Task_DS3231_ReadTime();

	//���÷���ֵ��1��ʼ����
	Task_DS3231_SetOnTime();
	
	while(1)
	{
		Task_Measure();
	}
}
