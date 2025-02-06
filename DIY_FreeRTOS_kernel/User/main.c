#include <stdio.h>
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

#define TASK_STACK_SIZE 128
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];

#define LINKED_LIST_DS 0
#define TASK_DEF_SWITCH 1
#define CRITICAL_PROTECT 0
#define IDLE_TASK_BLOCK 0
#define MULTI_PRIORITY 0
#define TASK_DELAY_LIST 0
#define TIME_SLICE 0

ListItem_t ListItem1, ListItem2, ListItem3;
List_t List_test;

portCHAR flag1, flag2, flag3;
extern List_t pxReadyTaskLists[configMAX_PRIORITIES]; 

TaskHandle_t Task1Handle, Task2Handle, Task3Handle, xIdleTaskHandle;
StackType_t Task1Stack[TASK_STACK_SIZE], Task2Stack[TASK_STACK_SIZE], Task3Stack[TASK_STACK_SIZE];
TCB_t Task1TCB, Task2TCB, Task3TCB, IdleTaskTCB;

void delay(uint32_t count);
void Task1_Entry(void * pvParameters);
void Task2_Entry(void * pvParameters);
void Task3_Entry(void * pvParameters);

int main(void)
{
#if (LINKED_LIST_DS == 1)
	vListInitilise(&List_test);
	
	vListInitialiseItem(&ListItem1);
	vListInitialiseItem(&ListItem2);
	vListInitialiseItem(&ListItem3);

	ListItem1.xItemValue = 1;
	ListItem2.xItemValue = 2;
	ListItem3.xItemValue = 3;

	vListInsert(&List_test, &ListItem2);
	vListInsert(&List_test, &ListItem1);
	vListInsert(&List_test, &ListItem3);
#endif /*LINKED_LIST_DS*/
	
#if (TASK_DEF_SWITCH == 1)
	//prvInitialiseTaskLists(); It'll be Initialised during first task's create. 
	
	Task1Handle = xTaskCreateStatic((TaskFunction_t)Task1_Entry,
																	(char *)"Task1",
																	(uint32_t)TASK_STACK_SIZE,
																	NULL,
																	(StackType_t *)Task1Stack,
																	(UBaseType_t)2,
																	(TCB_t *)&Task1TCB);
	Task2Handle = xTaskCreateStatic((TaskFunction_t)Task2_Entry,
																	(char *)"Task2",
																	(uint32_t)TASK_STACK_SIZE,
																	NULL,
																	(UBaseType_t)2,
																	(StackType_t *)Task2Stack,
																	(TCB_t *)&Task2TCB);
	Task3Handle = xTaskCreateStatic((TaskFunction_t)Task3_Entry,
																	(char *)"Task3",
																	(uint32_t)TASK_STACK_SIZE,
																	NULL,
																	(UBaseType_t)3,
																	(StackType_t *)Task3Stack,
																	(TCB_t *)&Task3TCB);
	
	//vListInsertEnd(&pxReadyTaskLists[1], (ListItem_t *)(&Task1TCB.xStateListItem));
	//vListInsertEnd(&pxReadyTaskLists[2], (ListItem_t *)(&Task2TCB.xStateListItem));
	portDISABLE_INTERRUPTS();
																	
	vTaskStartScheduler();
	
	for(;;)
	{
		//Never get here.
	}
#endif /*TASK_DEF_SWITCH*/
	
}

void delay(uint32_t count)
{
	for(;count != 0;count--)
	{
		//nop
	}
}

void Task1_Entry(void * pvParameters)
{
	for(;;)
	{
#if 1
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
		//Switch manually
		//taskYIELD();
#else
		flag1 = 1;
		vTaskDelay(2);
		flag1 = 0;
		vTaskDelay(2);
#endif
	}
}

void Task2_Entry(void * pvParameters)
{
	for(;;)
	{
#if 1
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		//taskYIELD();
#else
		flag2 = 1;
		vTaskDelay(2);
		flag2 = 0;
		vTaskDelay(2);
#endif
	}
}

void Task3_Entry(void * pvParameters)
{
	for(;;)
	{
		flag3 = 1;
		vTaskDelay(10);
		flag3 = 0;
		vTaskDelay(10);
	}
}

TaskHandle_t xIdleTaskHandle;
TCB_t IdleTaskTCB;
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
