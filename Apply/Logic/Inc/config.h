#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "algo_conf.h"
#include "dev_conf.h"

/* 用户句柄声明包含区 */

extern tagGPIO_T CD74P1_EN[];
extern tagGPIO_T CD74P2_EN[];
extern tagGPIO_T CD74P3_EN[];
extern tagGPIO_T CD74P4_EN[];
extern tagGPIO_T WX[];
extern tagGPIO_T VIN_LT3042_EN[];

extern tagDS3231_T DS3231;
extern tagADS1256_T ADS1256;

extern tagIWDG_T tIWDG;

extern tagDAC_T tDAC[];

extern tagUART_T Uart1;

extern tagPID_T PID;

#endif
