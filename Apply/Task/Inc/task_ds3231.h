#ifndef __TASK_DS3231_H_
#define __TASK_DS3231_H_

extern uint8_t TurnOnTime[5];

void Task_DS3231_ReadTime(void);
void Task_DS3231_SetOnTime(void);

#endif // !__TASK_DS3231_H_
