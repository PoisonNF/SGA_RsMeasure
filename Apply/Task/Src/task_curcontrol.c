#include "task_conf.h"
#include "task_curcontrol.h"
#include "algo_conf.h"
#include "drv_hal_conf.h"
#include "config.h"

#define DC_CONT_TIME 20 

int Set_voltage = 2000;

int SetCurrent = 20;

float Sampling_Current;

void Task_Current_Control(tagPID_T *tPID)
{
    float temp = 0.0f;
    float PIDValue = 0.0f;
    Set_voltage = 2000;

    for(int i = 0;i < DC_CONT_TIME; i++)
    {
        //ι��
        Drv_IWDG_Feed(&tIWDG);

        Drv_DAC_SetData(&tDAC[0],Set_voltage/10);

        Drv_Delay_Ms(100);

        //ͨ��0Ϊ��ѹ�ɼ�
        //Sampling_Voltage = OCD_ADS1256_ReadOneChannelVoltage(&ADS1256,0) * 5;

        //ͨ��1Ϊ�����ɼ�
        Sampling_Current = (OCD_ADS1256_ReadOneChannelVoltage(&ADS1256,1) - 1.25) / 0.33 /50;
        temp = Sampling_Current * 1000;

        //PID����
        PIDValue = Algo_PID_Calculate(&PID,temp,SetCurrent);

        Set_voltage += PIDValue;

        if(Set_voltage < 0)
        {
            Set_voltage = 0;

            PID.fError[0] = 0;

            PID.fDbuf[0]  = 0;

            PIDValue = 0;
        }
    }

    Set_voltage = 0;
}

