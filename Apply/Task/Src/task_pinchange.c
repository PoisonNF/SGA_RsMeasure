#include "task_conf.h"
#include "drv_hal_conf.h"   /* SGA库头文件配置 */
#include "config.h"			/* I/O配置头文件配置 */

uint8_t Variable_judgment(uint8_t GPIOValue)
{
	if(GPIOValue == 0)
		return 0;
	else
		return 1;
}

void PinChange1(uint8_t toVOUT,uint8_t toGND)
{
    uint8_t pxV;
	uint8_t pxA;
	uint8_t wxV;
	uint8_t wxA;

	int GPIOValue = 0;
	
	wxV = toVOUT % 16;			//测量电压端，求余数，用于位选
	wxA = toGND % 16;			//测量电流端，求余数，用于位选
	pxV = toVOUT / 16;			//测量电压端，求商，用于片选
	pxA = toGND / 16;			//测量电流端，求商，用于片选

    //电压端根据商去选择第几分区，并且使能
    pxV == 0 ? CD74P1_EN1_0 : CD74P1_EN1_1;
    pxV == 1 ? CD74P1_EN2_0 : CD74P1_EN2_1;
    pxV == 2 ? CD74P1_EN3_0 : CD74P1_EN3_1;
    pxV == 3 ? CD74P1_EN4_0 : CD74P1_EN4_1;
    pxV == 4 ? CD74P1_EN5_0 : CD74P1_EN5_1;
    pxV == 5 ? CD74P1_EN6_0 : CD74P1_EN6_1;

    //电流端根据商去选择第几分区，并且使能
    pxA == 0 ? CD74P2_EN1_0 : CD74P2_EN1_1;
    pxA == 1 ? CD74P2_EN2_0 : CD74P2_EN2_1;
    pxA == 2 ? CD74P2_EN3_0 : CD74P2_EN3_1;
    pxA == 3 ? CD74P2_EN4_0 : CD74P2_EN4_1;
    pxA == 4 ? CD74P2_EN5_0 : CD74P2_EN5_1;
    pxA == 5 ? CD74P2_EN6_0 : CD74P2_EN6_1;    

    wxV = 15 - wxV;
	wxA = 15 - wxA;  

    //位选
    GPIOValue = wxV&0x01;
	Variable_judgment(GPIOValue) ? S0_WX_1 : S0_WX_0;
	
	GPIOValue = wxV&0x02;
	Variable_judgment(GPIOValue) ? S1_WX_1 : S1_WX_0;
	
	GPIOValue = wxV&0x04;
	Variable_judgment(GPIOValue) ? S2_WX_1 : S2_WX_0;
	
	GPIOValue = wxV&0x08;
	Variable_judgment(GPIOValue) ? S3_WX_1 : S3_WX_0;
	
	GPIOValue = wxA&0x01;
	Variable_judgment(GPIOValue) ? S4_WX_1 : S4_WX_0;
	
	GPIOValue = wxA&0x02;
	Variable_judgment(GPIOValue) ? S5_WX_1 : S5_WX_0;
	
	GPIOValue = wxA&0x04;
	Variable_judgment(GPIOValue) ? S6_WX_1 : S6_WX_0;
	
	GPIOValue = wxA&0x08;
	Variable_judgment(GPIOValue) ? S7_WX_1 : S7_WX_0;
}

void PinChange2(uint8_t toVINPlus,uint8_t toVINMinus)
{
    uint8_t pxV;
	uint8_t pxA;
	uint8_t wxV;
	uint8_t wxA;

	int GPIOValue = 0;
	
	wxV = toVINPlus % 16;			//测量电压端，求余数，用于位选
	wxA = toVINMinus % 16;			//测量电流端，求余数，用于位选
	pxV = toVINPlus / 16;			//测量电压端，求商，用于片选
	pxA = toVINMinus / 16;			//测量电流端，求商，用于片选

    //电压端根据商去选择第几分区，并且使能
    pxV == 0 ? CD74P3_EN1_0 : CD74P3_EN1_1;
    pxV == 1 ? CD74P3_EN2_0 : CD74P3_EN2_1;
    pxV == 2 ? CD74P3_EN3_0 : CD74P3_EN3_1;
    pxV == 3 ? CD74P3_EN4_0 : CD74P3_EN4_1;
    pxV == 4 ? CD74P3_EN5_0 : CD74P3_EN5_1;
    pxV == 5 ? CD74P3_EN6_0 : CD74P3_EN6_1;

    //电流端根据商去选择第几分区，并且使能
    pxA == 0 ? CD74P4_EN1_0 : CD74P4_EN1_1;
    pxA == 1 ? CD74P4_EN2_0 : CD74P4_EN2_1;
    pxA == 2 ? CD74P4_EN3_0 : CD74P4_EN3_1;
    pxA == 3 ? CD74P4_EN4_0 : CD74P4_EN4_1;
    pxA == 4 ? CD74P4_EN5_0 : CD74P4_EN5_1;
    pxA == 5 ? CD74P4_EN6_0 : CD74P4_EN6_1;    

    wxV = 15 - wxV;
	wxA = 15 - wxA;  

    //位选
    GPIOValue = wxV&0x01;
	Variable_judgment(GPIOValue) ? S8_WX_1 : S8_WX_0;
	
	GPIOValue = wxV&0x02;
	Variable_judgment(GPIOValue) ? S9_WX_1 : S9_WX_0;
	
	GPIOValue = wxV&0x04;
	Variable_judgment(GPIOValue) ? S10_WX_1 : S10_WX_0;
	
	GPIOValue = wxV&0x08;
	Variable_judgment(GPIOValue) ? S11_WX_1 : S11_WX_0;
	
	GPIOValue = wxA&0x01;
	Variable_judgment(GPIOValue) ? S12_WX_1 : S12_WX_0;
	
	GPIOValue = wxA&0x02;
	Variable_judgment(GPIOValue) ? S13_WX_1 : S13_WX_0;
	
	GPIOValue = wxA&0x04;
	Variable_judgment(GPIOValue) ? S14_WX_1 : S14_WX_0;
	
	GPIOValue = wxA&0x08;
	Variable_judgment(GPIOValue) ? S15_WX_1 : S15_WX_0;
}
