#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

extern tagDS3231Time_T SysTime;

#define VIN_LT3042_EN_1 Drv_GPIO_Set(&VIN_LT3042_EN[0])
#define VIN_LT3042_EN_0 Drv_GPIO_Reset(&VIN_LT3042_EN[0])

#define START 0
#define STOP 96

//探针引脚序号 从0到95号
uint8_t Pin_Cont = 0;
//设备号
uint8_t DeviceNum = 0;
//采样电流偏差
float Sampling_Current_Error = 0.0f;

extern float Sampling_Current;
extern float Sampling_Voltage;
extern float Sampling_Voltage_Diff;

//第一次采样的电流
float Current_1;
//第二次采样的电流
float Current_2;
//第一次采样的电压
float Voltage_1;
//第二次采样的电压
float Voltage_2;
//电阻值
float Resistivity;
//最终电阻值
float Final_Resistivity;

//开尔文四线检测
void Kelvin_Measure(uint8_t Pin_Cont)
{
    /* 第一次测试 */
    PinChange1(Pin_Cont,Pin_Cont + 3);
    PinChange2(Pin_Cont + 1,Pin_Cont + 2);

    Drv_Delay_Ms(500);

    Task_Current_Control(&PID);

    //喂狗
    Drv_IWDG_Feed(&tIWDG);

    VOUT_Sampling(5);
    VOUT_Diff_Sampling(5);

    Current_1 = Sampling_Current - Sampling_Current_Error;

    if(Current_1 < 0.001)
    {
        Resistivity = Sampling_Voltage / Current_1;
        Voltage_1 = Sampling_Voltage;
    } 
    else
    {
        Resistivity = Sampling_Voltage_Diff / Current_1;
        Voltage_1 = Sampling_Voltage_Diff;
    }
        

    Final_Resistivity += Resistivity / 2;

    /* 第二次测试 */
    Sampling_Current = 0;
    Sampling_Voltage = 0;
    Sampling_Voltage_Diff = 0;
    Resistivity = 0;

    PinChange1(Pin_Cont + 3,Pin_Cont);
    PinChange2(Pin_Cont + 2,Pin_Cont + 1);

    Drv_Delay_Ms(500);

    Task_Current_Control(&PID);

    //喂狗
    Drv_IWDG_Feed(&tIWDG);

    VOUT_Sampling(5);
    VOUT_Diff_Sampling(5);

    Current_2 = Sampling_Current - Sampling_Current_Error;

    if(Current_2 < 0.001)
    {
        Resistivity = Sampling_Voltage / Current_2;
        Voltage_2 = Sampling_Voltage;
    }   
    else
    {
        Resistivity = Sampling_Voltage_Diff /Current_2;
        Voltage_2 = Sampling_Voltage_Diff;
    }
        
    Final_Resistivity = Final_Resistivity + Resistivity / 2;

    printf("ID0%d,wenner%d,%.3f,%.3f,%.3f,%.3f,%.3f\r\n",DeviceNum,Pin_Cont,
            Voltage_1,Current_1,
            Voltage_2,Current_2,
            Final_Resistivity);	

    Sampling_Current = 0;
    Sampling_Voltage = 0;
    Sampling_Voltage_Diff = 0;

    Voltage_1 = 0;
    Voltage_2 = 0;

    Current_1 = 0;
    Current_2 = 0;

    Resistivity = 0;
    Final_Resistivity = 0;
}

void Task_Measure(void)
{
    //主循环执行次数加一
    MainRunCycle++;

    //喂狗
    Drv_IWDG_Feed(&tIWDG);

    //获取当前系统时间
    OCD_DS3231_TimeGetHex(&DS3231,&SysTime);
    printf("20%02x年%02x月%02x日 %02x时%02x分%02x秒 周%02x\r\n",
        SysTime.ucYear,SysTime.ucMonth,SysTime.ucDate,
        SysTime.ucHour,SysTime.ucMinute,SysTime.ucSecond,
        SysTime.ucWeek);

    //主循环执行每执行100次 并且 不在工作状态
    if(MainRunCycle % 100 == 0 && WorkingFlag == 0)
    {
		//打印信息
		printf("ID0%d,wenner%d,%.3f,%.3f,%.3f,%.3f,%.3f\r\n",DeviceNum,Pin_Cont,
                    Voltage_1,Current_1,
                    Voltage_2,Current_2,
                    Final_Resistivity);		
		//循环次数清零
		MainRunCycle = 0;
    }

    //当读取到的时间为设定工作时间
	if( SysTime.ucYear == TurnOnTime[0]&&
        SysTime.ucMonth == TurnOnTime[1]&&
        SysTime.ucDate == TurnOnTime[2]&&
        SysTime.ucHour == TurnOnTime[3]&&
        SysTime.ucMinute == TurnOnTime[4])
	{
        //工作标志位置1
        WorkingFlag = 1;
    }

    //当工作标志位置1时
    while(WorkingFlag)
    {
        //LT3042使能脚置1，电源输入
		VIN_LT3042_EN_1;

        Drv_Delay_Ms(100);

        for(Pin_Cont = START; Pin_Cont + 1 <= STOP; Pin_Cont++)
        {
            //开尔文四线检测
            Kelvin_Measure(Pin_Cont);
        }

        Pin_Cont = 0;

        //LT3042使能脚置0，关闭电源
        VIN_LT3042_EN_0;

        printf("-1\r\n");

        break;
    }

    Drv_Delay_Ms(1000);

}
