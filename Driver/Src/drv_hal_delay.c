/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_delay.c

* ���ݼ�������ʱ�����ļ�

* �ļ���ʷ��

* �汾��	    ����	  ����		     ˵��
*  2.4		2023-05-12	�����		���FreeRTOS��ʼ������ǰ�޷�ʹ����ʱ������

* 2.3.1		2023-05-05	�����		������ʱ��������

*  2.3		2023-04-23	�����		�ṩ���Ӿ�׼����ʱ����

*  2.2		2023-03-29	�����		����FreeRTOS,������API

* 1.1.8		2022-10-22	�����		����RTT����ʹ��hal��ʱ�����������,����us��ʱ����

* 1.0.0a 	2020-02-22	���		�������ļ�

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_DELAY_ENABLE
/**
 * @brief ��ʱ����(ms)
 * @param _ulVal-��ʱʱ����Чֵ����λms��
 * @retval Null
*/
void Drv_Delay_Ms(uint32_t _ulVal)
{
	/* RT-Thread ��ʱ���� */
	#ifdef RTT_ENABLE
	rt_thread_mdelay(_ulVal);
	#endif

	/* FreeRTOS ��ʱ���� */
	#ifdef FREERTOS_ENABLE
    /* ���δ������������ʹ��HAL����ʱ���� */
    if(xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)
        HAL_Delay(_ulVal);
    else
        osDelay(_ulVal);
	#endif

	/* ��� ��ʱ���� */
	#if !defined(FREERTOS_ENABLE) && !defined(RTT_ENABLE)
	HAL_Delay(_ulVal);
	#endif
}

/**
 * @brief ��ʱ����(us)
 * @param _ulVal-��ʱʱ����Чֵ����λus��
 * @retval Null
 * @note ��ʱus��ԽС�Ἣ�䲻��׼���ر�����10us����ʱ������ʱ�����ʱ����ʹ��RTOS�ڲ���us����ʱ����
*/
void Drv_Delay_Us(uint32_t _ulVal)
{
	/* ��ʱС��50usʹ����ͨ��ʱ����Ϊ��׼ */
	if(_ulVal < 50)
	{
		int i,j;

		for(i = 0; i < _ulVal; i++)
			for(j = 0; j < 8; j++);
	}
	else	/* ����50usʹ�ò�ѯ����Ϊ��׼ */
	{
		uint32_t ulTemp;
		
		SysTick->LOAD = 9*_ulVal;
		SysTick->VAL  = 0X00;	/* ��ռ����� */
		SysTick->CTRL = 0X01;	/* ʹ�ܣ����������޶����������ⲿʱ��Դ */

		do
			ulTemp = SysTick->CTRL;							/* ��ȡ��ǰ������ֵ */
		while((ulTemp & 0x01) && (!(ulTemp & (1<<16))));	/* �ȴ�ʱ�䵽�� */

		SysTick->CTRL = 0x00; 	/* �رռ����� */
		SysTick->VAL  = 0X00; 	/* ��ռ����� */
	}
}
#endif