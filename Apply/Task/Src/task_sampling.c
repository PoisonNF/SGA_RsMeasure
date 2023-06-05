#include "drv_hal_conf.h"
#include "ocd_conf.h"
#include "config.h"
#include "task_conf.h"

float Sampling_Voltage;
float Sampling_Voltage_Diff;

//VOUT/VOUT_AD采样
void VOUT_Sampling(uint8_t ads_time)
{
	int i;
	Sampling_Voltage = 0;

	for(i = 0;i < ads_time; i++)
	{
		Sampling_Voltage += OCD_ADS1256_ReadOneChannelVoltage(&ADS1256,0)*5/ads_time;	
		Drv_Delay_Us(10);
	}
}

//VOUT_AD1 采样
void VOUT_Diff_Sampling(uint8_t ads_time)
{
	int i;
	
	for(i = 0;i < ads_time; i++)
	{
		Sampling_Voltage_Diff += OCD_ADS1256_ReadOneChannelVoltage(&ADS1256,2);	
		Drv_Delay_Us(10);
	}
	
	//求ads_time次的平均
	Sampling_Voltage_Diff = Sampling_Voltage_Diff/ads_time;
	
	Sampling_Voltage_Diff = Sampling_Voltage_Diff-1.23;
	
	Sampling_Voltage_Diff = Sampling_Voltage_Diff*5;
	
}

