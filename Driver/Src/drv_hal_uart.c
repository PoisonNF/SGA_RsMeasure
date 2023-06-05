/****************************************************************************

* Sigma�Ŷ�

* �ļ���: drv_hal_uart.c

* ���ݼ��������������ļ�

* �ļ���ʷ��

* �汾��	  ����		  ����				˵��
*  2.4		2023-05-12   �����		���������жϽ�����غ�������ʽ�Ż�

* 2.2.1		2023-04-03   �����		������Ϣ�ṹ���Ա���ģ���������DMA���ݽ��պ���

*  1.2		2023-02-26   �����		��������DMA������غ������Ż�ע��

* 1.1.7 	2022-10-11   �����		��������DMA������غ���

* 1.1.4 	2022-09-03   �����		��������������ӳ�����

* 1.1.1 	2022-08-04   �����		�޸��˴����������ȷ������

* 1.0.0a 	2020-02-22	 ���		�������ļ�

****************************************************************************/
#include "drv_hal_conf.h"

#ifdef DRV_HAL_UART_ENABLE

/**
 * @brief �����ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null 
*/
static void S_Uart_NVICConfig(tagUART_T *_tUART)
{	
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		HAL_NVIC_SetPriority(USART1_IRQn, _tUART->ucPriority, _tUART->ucSubPriority);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	}       
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		HAL_NVIC_SetPriority(USART2_IRQn, _tUART->ucPriority, _tUART->ucSubPriority);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		HAL_NVIC_SetPriority(USART3_IRQn, _tUART->ucPriority, _tUART->ucSubPriority);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == UART4)
	{
		HAL_NVIC_SetPriority(UART4_IRQn, _tUART->ucPriority, _tUART->ucSubPriority);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
	}
	else if(_tUART->tUARTHandle.Instance == UART5)
	{
		HAL_NVIC_SetPriority(UART5_IRQn, _tUART->ucPriority, _tUART->ucSubPriority);
		HAL_NVIC_EnableIRQ(UART5_IRQn);
	}
}

/**
 * @brief ����DMA�ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null 
*/
static void S_Uart_DMA_NVICConfig(tagUART_T *_tUART)
{
	/* DMA����ʹ�� */
	if(_tUART->tUartDMA.bRxEnable == true)
	{
		if(_tUART->tUARTHandle.Instance == USART1)
		{
			/* DMA1_Channel5_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel5_IRQn,_tUART->tUartDMA.ucDMARxPriority, _tUART->tUartDMA.ucDMARxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == USART2)
		{
			/* DMA1_Channel6_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel6_IRQn,_tUART->tUartDMA.ucDMARxPriority, _tUART->tUartDMA.ucDMARxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == USART3)
		{
			/* DMA1_Channel3_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel3_IRQn,_tUART->tUartDMA.ucDMARxPriority, _tUART->tUartDMA.ucDMARxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == UART4)
		{
			/* DMA2_Channel3_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA2_Channel3_IRQn,_tUART->tUartDMA.ucDMARxPriority, _tUART->tUartDMA.ucDMARxSubPriority);
			HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
		}
	}
	
	/* DMA����ʹ�� */
	if(_tUART->tUartDMA.bTxEnable == true)
	{
		if(_tUART->tUARTHandle.Instance == USART1)
		{
			/* DMA1_Channel4_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel4_IRQn,_tUART->tUartDMA.ucDMATxPriority,_tUART->tUartDMA.ucDMATxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == USART2)
		{
			/* DMA1_Channel7_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel7_IRQn,_tUART->tUartDMA.ucDMATxPriority,_tUART->tUartDMA.ucDMATxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == USART3)
		{
			/* DMA1_Channel2_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA1_Channel2_IRQn,_tUART->tUartDMA.ucDMATxPriority,_tUART->tUartDMA.ucDMATxSubPriority);
			HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
		}
		else if(_tUART->tUARTHandle.Instance == UART4)
		{
			/* DMA2_Channel5_IRQn interrupt configuration */
			HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn,_tUART->tUartDMA.ucDMATxPriority,_tUART->tUartDMA.ucDMATxSubPriority);
			HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);
		}
	}
}

/**
 * @brief ���ڲ������ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null
*/
static void S_Uart_ParamConfig(tagUART_T *_tUART)
{
	/* ���ô��ڳ�ʼ������ */
	if (HAL_UART_Init(&_tUART->tUARTHandle) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
}

/**
 * @brief ����DMA�������ú���
 * @param _tUART-����ʵ��ָ��
 * @retval Null
*/
static void S_Uart_DMAParamConfig(tagUART_T *_tUART)
{
	/* ���ʹ��DMA���� */
	if(_tUART->tUartDMA.bRxEnable == true)
	{
		if(HAL_DMA_Init(&_tUART->tUartDMA.tDMARx) != HAL_OK)	Drv_HAL_Error(__FILE__,__LINE__);
	}

	/* ���ʹ��DMA���� */
	if(_tUART->tUartDMA.bTxEnable == true)
	{
		if(HAL_DMA_Init(&_tUART->tUartDMA.tDMATx) != HAL_OK)	Drv_HAL_Error(__FILE__,__LINE__);
	}
}

/**
 * @brief ����ʱ�ӳ�ʼ������---L4ʹ��
 * @param Null
 * @retval Null
*/
static void S_Uart_CLKConfig(void)
{
#if defined (STM32L4_SGA_ENABLE)
/* Select UART function start */
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_UART5;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Drv_HAL_Error(__FILE__, __LINE__);
	}
/* Select UART function end */	
#endif
}

/**
 * @brief ����ʱ��ʹ�ܺ���
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null
*/
static void S_UART_CLKEnable(tagUART_T *_tUART)
{
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		__HAL_RCC_USART2_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		__HAL_RCC_USART3_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == UART4)
	{
		__HAL_RCC_UART4_CLK_ENABLE();
	}
	else if(_tUART->tUARTHandle.Instance == UART5)
	{
		__HAL_RCC_UART5_CLK_ENABLE();
	}
}

/**
 * @brief DMAʱ��ʹ�ܺ���
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null
*/
static void S_UART_DMA_CLKEnable(tagUART_T *_tUART)
{
	if(_tUART->tUARTHandle.Instance == USART1)			__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == USART2)		__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == USART3)		__HAL_RCC_DMA1_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == UART4)		__HAL_RCC_DMA2_CLK_ENABLE();
	else if(_tUART->tUARTHandle.Instance == UART5)
	{
		/* Uart5����ʹ��DMA */
		Drv_HAL_Error(__FILE__,__LINE__);
		while(1);
	}
}

/**
 * @brief UART��GPIO�������ú���
 * @param _tUART-���ھ��ָ��
 * @retval Null
*/
static void S_UART_GPIOConfig(tagUART_T *_tUART)
{
	/* ��������ģʽʱ�� */
	__HAL_RCC_AFIO_CLK_ENABLE();

	/* ���ݲ�ͬ���ڵ�ucAFMode������Ӧ����ӳ�䣬��ӳ�����drv_hal_uart.h�� */
	if(_tUART->tUARTHandle.Instance == USART1)
	{
		if(_tUART->tGPIO->ucAFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART1_DISABLE();
		else if(_tUART->tGPIO->ucAFMode == FULL_REMAP) 	    __HAL_AFIO_REMAP_USART1_ENABLE();
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP)	while(1);
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP2)	while(1);
	}
	else if(_tUART->tUARTHandle.Instance == USART2)
	{
		if(_tUART->tGPIO->ucAFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART2_DISABLE();
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP)	while(1);
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP2)	while(1);
		else if(_tUART->tGPIO->ucAFMode == FULL_REMAP)		__HAL_AFIO_REMAP_USART2_ENABLE();
	}	
	else if(_tUART->tUARTHandle.Instance == USART3)
	{
		if(_tUART->tGPIO->ucAFMode == NO_REMAP)		    	__HAL_AFIO_REMAP_USART3_DISABLE();
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP)	__HAL_AFIO_REMAP_USART3_PARTIAL();
		else if(_tUART->tGPIO->ucAFMode == PARTIAL_REMAP2)	while(1);
		else if(_tUART->tGPIO->ucAFMode == FULL_REMAP)		__HAL_AFIO_REMAP_USART3_ENABLE();
	}
	
	Drv_GPIO_Init(_tUART->tGPIO, 2); 	/* GPIO��ʼ�� */
}

/**
 * @brief ���ڷ������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpTxData-�������ݵ�ַָ��
 * @param _uspSize-�������ݴ�С
 * @retval Null
*/
void Drv_Uart_Transmit(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize)
{
	HAL_UART_Transmit(&_tUART->tUARTHandle, _ucpTxData, _uspSize, UART_TIME_OUT);
}

/**
 * @brief �����жϷ������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpTxData-�������ݵ�ַָ��
 * @param _uspSize-�������ݴ�С
 * @retval Null
*/
void Drv_Uart_Transmit_IT(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize)
{
	HAL_UART_Transmit_IT(&_tUART->tUARTHandle, _ucpTxData, _uspSize);
}

/**
 * @brief �����жϽ������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpRxData-�������ݵ�ַָ��
 * @retval uint16_t ���յ��ĳ���
*/
uint16_t Drv_Uart_Receive_IT(tagUART_T *_tUART, uint8_t *_ucpRxData)
{
	if(_tUART->tRxInfo.ucRxCplt)
	{
		/* ���ݿ��� */
		memcpy(_ucpRxData,_tUART->tRxInfo.ucpITRxCache,_tUART->tRxInfo.usRxLength);

		/* ��־λ���� */
		_tUART->tRxInfo.ucRxCplt = 0;

		return _tUART->tRxInfo.usRxLength;
	}
	
	return 0;
}

/**
 * @brief ����DMA�������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpTxData-�������ݵ�ַָ��
 * @param _uspSize-�������ݴ�С
 * @retval Null
*/
void Drv_Uart_Transmit_DMA(tagUART_T *_tUART, uint8_t *_ucpTxData, uint16_t _uspSize)
{
	/* ��ȡDMA״̬ */
	while(HAL_DMA_GetState(&_tUART->tUartDMA.tDMATx) != HAL_DMA_STATE_READY);

	/* ׼��״̬���ɷ��� */
	HAL_UART_Transmit_DMA(&_tUART->tUARTHandle, _ucpTxData, _uspSize);
}

/**
 * @brief ����DMA�������ݺ���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpRxData-�������ݵ�ַָ��
 * @retval uint16_t usRxNum ���յ��ĳ���
*/
uint16_t Drv_Uart_Receive_DMA(tagUART_T *_tUART, uint8_t *_ucpRxData)
{
	uint16_t usRxNum;
    
	/* �ж��Ƿ������� */
	if(_tUART->tRxInfo.ucDMARxCplt != 1)
	{
		return 0;
	}
	else
	{
		/* ���������ݵĳ��ȱ��� */
		usRxNum = _tUART->tRxInfo.usDMARxLength;

		/* ��ս������ݵ�ַָ�� */
        memset(_ucpRxData,0,usRxNum+1);

		/* ���ݿ��� */
		memcpy(_ucpRxData,_tUART->tRxInfo.ucpDMARxCache,usRxNum);

		/* �����־λ */
		_tUART->tRxInfo.ucDMARxCplt = 0;

		return usRxNum;
	}
}

/**
 * @brief ���ڽ����ж����ú���
 * @param _tUART-����ʵ��ָ��
 * @param _ucpBuffer-��������ָ��
 * @param _usSize-�������ݴ�С
 * @retval Null 
*/
void Drv_Uart_ReceIT_Enable(tagUART_T *_tUART, uint8_t *_ucpBuffer, uint16_t _usSize)
{
	HAL_UART_Receive_IT(&_tUART->tUARTHandle, _ucpBuffer, _usSize);
}

/**
 * @brief ������ͨ�ж�ģʽ��ʼ������
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null 
*/
void Drv_Uart_ITInit(tagUART_T *_tUART)
{
	S_Uart_CLKConfig();
	S_UART_CLKEnable(_tUART);
	S_UART_GPIOConfig(_tUART);
	S_Uart_ParamConfig(_tUART);		/* ���ô��ڲ��� */
	S_Uart_NVICConfig(_tUART);		/* �����ж����ȼ� */

	/* Ϊcache����һ�γ��ȵĶ�̬�ڴ� */
	_tUART->tRxInfo.ucpITRxCache = (uint8_t *)malloc(UART_IT_RX_CACHE_SIZE);

	/* ��һ���������н���һ���ַ� */
	HAL_UART_Receive_IT(&_tUART->tUARTHandle, _tUART->tRxInfo.ucpRxBuffer, 1);
}

/**
 * @brief ����DMAģʽ��ʼ������
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null 
*/
void Drv_Uart_DMAInit(tagUART_T *_tUART)
{
	S_Uart_CLKConfig();				/* L4���� */
	
	/* DMA���� */
	S_UART_DMA_CLKEnable(_tUART);
	S_Uart_DMA_NVICConfig(_tUART);	/* DMA�ж����� */
	S_Uart_DMAParamConfig(_tUART);	/* ����DMA���� */

	/* �������� */
	S_UART_CLKEnable(_tUART);
	S_UART_GPIOConfig(_tUART);
	S_Uart_NVICConfig(_tUART);		/* �����ж����� */
	S_Uart_ParamConfig(_tUART);		/* ���ô��ڲ��� */

	/* ���ʹ��DMA���� */
	if(_tUART->tUartDMA.bRxEnable == true)
	{
		/* �������ں�DMA���� */
		__HAL_LINKDMA(&_tUART->tUARTHandle,hdmarx,_tUART->tUartDMA.tDMARx);

		/* Ϊcache����һ�γ��ȵĶ�̬�ڴ� */
		_tUART->tRxInfo.ucpDMARxCache = (uint8_t *)malloc(_tUART->tRxInfo.usDMARxMAXSize);

		/*	�򿪿����ж� */
		__HAL_UART_ENABLE_IT(&_tUART->tUARTHandle,UART_IT_IDLE);

		/* ����DMA���� */
		HAL_UART_Receive_DMA(&_tUART->tUARTHandle,_tUART->tRxInfo.ucpDMARxCache,_tUART->tRxInfo.usDMARxMAXSize);
	}

	/* ���ʹ��DMA���� */
	if(_tUART->tUartDMA.bTxEnable == true)
	{
		/* �������ں�DMA���� */
		__HAL_LINKDMA(&_tUART->tUARTHandle,hdmatx,_tUART->tUartDMA.tDMATx);

		/* Ϊcache����һ�γ��ȵĶ�̬�ڴ� */
		_tUART->tTxInfo.ucpDMATxCache = (uint8_t *)malloc(_tUART->tTxInfo.usDMATxMAXSize);
	}
}

/**
 * @brief ����1�ж�ñ�Ӻ���
 * @param _tUART-���ڽṹ��ָ��
 * @retval Null
*/
void Drv_Uart_IRQHandler(tagUART_T *_tUART)
{
	HAL_UART_IRQHandler(&_tUART->tUARTHandle);
}

/**
 * @brief �����жϽ��մ����Ӻ���(���ڴ����жϽ�����ɻص�������)
 * @param _tUART-���ڽṹ��ָ��
 * @note Ĭ�ϼ�⻻�з������ݱ������ʼ��ַΪucpITRxCache,���յ��ĳ���ΪusRxLength��
 * @retval Null
*/
void Drv_Uart_IT_RxHandler(tagUART_T *_tUART)
{
	/* Ĭ�ϼ�⵽���з�'\n'������ս��� */
	if(_tUART->tRxInfo.ucpRxBuffer[0] == '\n')
	{
		/* �滻Ϊ'\0'��ʾ�ַ�����β */
		_tUART->tRxInfo.ucpITRxCache[_tUART->tRxInfo.usRxCnt] = '\0';

		/* ������յ��ĳ��� */
		_tUART->tRxInfo.usRxLength = _tUART->tRxInfo.usRxCnt;

		/* ���ռ��������� */
		_tUART->tRxInfo.usRxCnt = 0;

		/* ������ɱ�־λ��1 */
		_tUART->tRxInfo.ucRxCplt = 1;
	}

	/* δ����β�������� */
	else
	{
		/* δ�������������޼������� */
		if(_tUART->tRxInfo.usRxCnt < UART_IT_RX_CACHE_SIZE)
		{
			/* �洢1�ֽ����ݣ�ͬʱ���ռ�������һ */
			_tUART->tRxInfo.ucpITRxCache[_tUART->tRxInfo.usRxCnt] = _tUART->tRxInfo.ucpRxBuffer[0];
			_tUART->tRxInfo.usRxCnt++;
		}
		else	/* ������cache��С������֪������ɣ�������������ն����ֽ� */
		{
			/* ������յ��ĳ��� */
			_tUART->tRxInfo.usRxLength = UART_IT_RX_CACHE_SIZE;

			/* ���ռ��������� */
			_tUART->tRxInfo.usRxCnt = 0;

			/* ������ɱ�־λ��1 */
			_tUART->tRxInfo.ucRxCplt = 1;			
		}
	}

	/* �ȴ���һ���ֽڽ������ */
	while(HAL_UART_Receive_IT(&_tUART->tUARTHandle,_tUART->tRxInfo.ucpRxBuffer,1) != HAL_OK);
}

/**
 * @brief ����DMA�жϽ��մ����Ӻ���(���ڴ����жϴ�������)
 * @param _tUART-���ڽṹ��ָ��
 * @note ���ݱ������ʼ��ַΪucpDMARxCache�����յ��ĳ���ΪusDMARxLength
 * @retval Null
*/
void Drv_Uart_DMA_RxHandler(tagUART_T *_tUART)
{
	/* �����жϱ�Ǳ���λ */
	if(__HAL_UART_GET_FLAG(&_tUART->tUARTHandle,UART_FLAG_IDLE) != RESET) 
	{
		/* ����жϱ�� */
		__HAL_UART_CLEAR_IDLEFLAG(&_tUART->tUARTHandle);

		/* ֹͣDMA���� */
		HAL_UART_DMAStop(&_tUART->tUARTHandle);

		/* ����������ȥδ���յ���������Ϊ�Ѿ����յ��������� */
		_tUART->tRxInfo.usDMARxLength = _tUART->tRxInfo.usDMARxMAXSize - __HAL_DMA_GET_COUNTER(_tUART->tUARTHandle.hdmarx);

		/* ���ձ�־λ��1 */
        _tUART->tRxInfo.ucDMARxCplt = 1;

		/* ��������DMA���� */
        HAL_UART_Receive_DMA(&_tUART->tUARTHandle,_tUART->tRxInfo.ucpDMARxCache,_tUART->tRxInfo.usDMARxMAXSize);
	}
}

/**
 * @brief ����DMA�жϷ��ʹ����Ӻ���(����DMA�жϴ�������)
 * @param _tUART-���ڽṹ��ָ��
 * @note ����DMA�������ͱ����ڶ�ӦDMA�жϴ������м���˺�������Ȼֻ�ܵ��η���
 * @retval Null
*/
void Drv_Uart_DMA_TxHandler(tagUART_T *_tUART)
{
	uint32_t ulDMAFlag;

	/* UART1����ͨ�� */
	if(_tUART->tUartDMA.tDMATx.Instance == DMA1_Channel4)		ulDMAFlag = DMA_FLAG_TC4;

	/* UART2����ͨ�� */
	else if(_tUART->tUartDMA.tDMATx.Instance == DMA1_Channel7)	ulDMAFlag = DMA_FLAG_TC7;

	/* UART3����ͨ�� */
	else if(_tUART->tUartDMA.tDMATx.Instance == DMA1_Channel2) 	ulDMAFlag = DMA_FLAG_TC2;

	/* UART4����ͨ�� */
	else if(_tUART->tUartDMA.tDMATx.Instance == DMA2_Channel5)	ulDMAFlag = DMA_FLAG_TC5;

	/* �ж϶�Ӧͨ���Ƿ���ɷ��� */
	if(__HAL_DMA_GET_TC_FLAG_INDEX(&_tUART->tUartDMA.tDMATx) == ulDMAFlag)
	{
		/* �رմ���DMA */
		HAL_UART_DMAStop(&_tUART->tUARTHandle);

		/* ���������ɱ�־λ */
		__HAL_DMA_CLEAR_FLAG(&_tUART->tUartDMA.tDMATx,ulDMAFlag);

		/* ����CNDTR�Ĵ���������Ϊ��󴫵������С */
		_tUART->tUartDMA.tDMATx.Instance->CNDTR = _tUART->tTxInfo.usDMATxMAXSize;

		/* ����DMA���� */
		__HAL_DMA_ENABLE(&_tUART->tUartDMA.tDMATx);
	}
}

#endif
