#include "task_conf.h"

#include "config.h"

/**
 * @brief �ⲿ�ж�5-9������
 * @param null
 * @retval Null
*/
__weak void Task_EXTI9_5_IRQHandler(void)
{
	
}

/**
 * @brief �ⲿ�ж�5-9������
 * @param null
 * @retval Null
*/
void EXTI9_5_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&DS3231_ALARM_IRQ);	/* ����ӣ��������޸� */
	
	Task_EXTI9_5_IRQHandler();
}

/**
 * @brief �ⲿ�ж�10-15������
 * @param null
 * @retval Null
*/
__weak void Task_EXTI15_10_IRQHandler(void)
{
	
}

/**
 * @brief �ⲿ�ж�10-15������
 * @param null
 * @retval Null
*/
void EXTI15_10_IRQHandler(void)
{
//	Drv_GPIO_EXTI_IRQHandler(&tPCUart.tGPIO[1]);	/* ����ӣ��������޸� */
	
	Task_EXTI15_10_IRQHandler();
}

/**
 * @brief ����1�ж�������
 * @param null
 * @retval Null
*/
__weak void Task_USART1_IRQHandler(void)
{
	
}

/**
 * @brief ����1�жϷ�����
 * @param null
 * @retval Null
*/
void USART1_IRQHandler(void)
{
	/* ʾ�� */
//	Drv_Uart_IRQHandler(&tPCUart);		/* ���貿�� */
	
	Task_USART1_IRQHandler();
}

/**
 * @brief ����2�ж�������
 * @param null
 * @retval Null
*/
__weak void Task_USART2_IRQHandler(void)
{
	
}

/**
 * @brief ����1�жϷ�����
 * @param null
 * @retval Null
*/
void USART2_IRQHandler(void)
{
		/* ʾ�� */
//	Drv_Uart_IRQHandler(&tJY901B.tUART);		/* ���貿�� */
//	
//	Task_USART2_IRQHandler();
}

/**
 * @brief ����3�жϷ�����
 * @param null
 * @retval Null
*/
void USART3_IRQHandler(void)
{

}

/**
 * @brief ����4�жϷ�����
 * @param null
 * @retval Null
*/
void UART4_IRQHandler(void)
{

}

/**
 * @brief ����5�жϷ�����
 * @param null
 * @retval Null
*/
void UART5_IRQHandler(void)
{

}

/**
 * @brief ��ʱ��2�жϷ�����
 * @param null
 * @retval Null
*/
void TIM2_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��3�жϷ�����
 * @param null
 * @retval Null
*/
void TIM3_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��4�жϷ�����
 * @param null
 * @retval Null
*/
void TIM4_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��5�жϷ�����
 * @param null
 * @retval Null
*/
void TIM5_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��6�жϷ�����
 * @param null
 * @retval Null
*/
void TIM6_IRQHandler(void)
{
    /* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}

/**
 * @brief ��ʱ��7�жϷ�����
 * @param null
 * @retval Null
*/
void TIM7_IRQHandler(void)
{
	/* ʾ�� */
//    Drv_Timer_IRQHandler(&demoTIM);
}



