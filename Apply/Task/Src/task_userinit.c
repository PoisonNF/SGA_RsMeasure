#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

void Task_UserInit(void)
{
    Drv_Uart_DMAInit(&Uart1);
    printf("Uart1 Init\r\n");

	Drv_GPIO_Init(CD74P1_EN, 6);
    Drv_GPIO_Init(CD74P2_EN, 6);
    Drv_GPIO_Init(CD74P3_EN, 6);
    Drv_GPIO_Init(CD74P4_EN, 6);
    printf("CD74 Init\r\n");

    Drv_GPIO_Init(WX,16);
    printf("WX Init\r\n");

    Drv_GPIO_Init(VIN_LT3042_EN,1);
    
    OCD_DS3231_Init(&DS3231);
    printf("DS3231 Init\r\n");
    
    OCD_ADS1256_Init(&ADS1256);
    printf("ADS1256 Init\r\n");

    Drv_IWDG_Init(&tIWDG);
    printf("IWDG Init\r\n");

    Drv_DAC_Init(tDAC,1);
    printf("DAC1 Init\r\n");

    Algo_PID_Init(&PID);
}
