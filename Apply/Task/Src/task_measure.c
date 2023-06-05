#include "task_conf.h"
#include "ocd_conf.h"
#include "config.h"

extern tagDS3231Time_T SysTime;

#define VIN_LT3042_EN_1 Drv_GPIO_Set(&VIN_LT3042_EN[0])
#define VIN_LT3042_EN_0 Drv_GPIO_Reset(&VIN_LT3042_EN[0])

#define START 0
#define STOP 96

//̽��������� ��0��95��
uint8_t Pin_Cont = 0;
//�豸��
uint8_t DeviceNum = 0;
//��������ƫ��
float Sampling_Current_Error = 0.0f;

extern float Sampling_Current;
extern float Sampling_Voltage;
extern float Sampling_Voltage_Diff;

//��һ�β����ĵ���
float Current_1;
//�ڶ��β����ĵ���
float Current_2;
//��һ�β����ĵ�ѹ
float Voltage_1;
//�ڶ��β����ĵ�ѹ
float Voltage_2;
//����ֵ
float Resistivity;
//���յ���ֵ
float Final_Resistivity;

//���������߼��
void Kelvin_Measure(uint8_t Pin_Cont)
{
    /* ��һ�β��� */
    PinChange1(Pin_Cont,Pin_Cont + 3);
    PinChange2(Pin_Cont + 1,Pin_Cont + 2);

    Drv_Delay_Ms(500);

    Task_Current_Control(&PID);

    //ι��
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

    /* �ڶ��β��� */
    Sampling_Current = 0;
    Sampling_Voltage = 0;
    Sampling_Voltage_Diff = 0;
    Resistivity = 0;

    PinChange1(Pin_Cont + 3,Pin_Cont);
    PinChange2(Pin_Cont + 2,Pin_Cont + 1);

    Drv_Delay_Ms(500);

    Task_Current_Control(&PID);

    //ι��
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
    //��ѭ��ִ�д�����һ
    MainRunCycle++;

    //ι��
    Drv_IWDG_Feed(&tIWDG);

    //��ȡ��ǰϵͳʱ��
    OCD_DS3231_TimeGetHex(&DS3231,&SysTime);
    printf("20%02x��%02x��%02x�� %02xʱ%02x��%02x�� ��%02x\r\n",
        SysTime.ucYear,SysTime.ucMonth,SysTime.ucDate,
        SysTime.ucHour,SysTime.ucMinute,SysTime.ucSecond,
        SysTime.ucWeek);

    //��ѭ��ִ��ÿִ��100�� ���� ���ڹ���״̬
    if(MainRunCycle % 100 == 0 && WorkingFlag == 0)
    {
		//��ӡ��Ϣ
		printf("ID0%d,wenner%d,%.3f,%.3f,%.3f,%.3f,%.3f\r\n",DeviceNum,Pin_Cont,
                    Voltage_1,Current_1,
                    Voltage_2,Current_2,
                    Final_Resistivity);		
		//ѭ����������
		MainRunCycle = 0;
    }

    //����ȡ����ʱ��Ϊ�趨����ʱ��
	if( SysTime.ucYear == TurnOnTime[0]&&
        SysTime.ucMonth == TurnOnTime[1]&&
        SysTime.ucDate == TurnOnTime[2]&&
        SysTime.ucHour == TurnOnTime[3]&&
        SysTime.ucMinute == TurnOnTime[4])
	{
        //������־λ��1
        WorkingFlag = 1;
    }

    //��������־λ��1ʱ
    while(WorkingFlag)
    {
        //LT3042ʹ�ܽ���1����Դ����
		VIN_LT3042_EN_1;

        Drv_Delay_Ms(100);

        for(Pin_Cont = START; Pin_Cont + 1 <= STOP; Pin_Cont++)
        {
            //���������߼��
            Kelvin_Measure(Pin_Cont);
        }

        Pin_Cont = 0;

        //LT3042ʹ�ܽ���0���رյ�Դ
        VIN_LT3042_EN_0;

        printf("-1\r\n");

        break;
    }

    Drv_Delay_Ms(1000);

}
