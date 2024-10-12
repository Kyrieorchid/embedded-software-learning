/*EXAMPLE 1 ~ 9, about task management*/

#include "taskm.h"

extern TaskHandle_t StartTaskM_Handler;
TaskHandle_t Task2_Handler;

static const char *pcInstance1 = "Instance1 is running\r\n";
static const char *pcInstance2 = "Instance2 is running\r\n";
volatile uint32 IdleCycleCnt1 = 0;
volatile uint64 IdleCycleCnt2 = 0;

//Idle task hook/call_back function, must be 'void vApplicationIdleHook'
void vApplicationIdleHook(void)
{
//	vTaskSuspendAll();
//	taskENTER_CRITICAL();
	IdleCycleCnt1++;
	IdleCycleCnt2++;
//	taskEXIT_CRITICAL();
//	xTaskResumeAll();
}

void vPrintIdleCycleCnt(void *Parameters)
{
//	vTaskSuspendAll();

	for(;;)
	{
		taskENTER_CRITICAL();
		printf("IdleCycleCnt1:%u\r\n", IdleCycleCnt1);
//		printf("IdleCycleCnt2:%d\r\n", *(uint32 *)(&IdleCycleCnt2));
		printf("IdleCycleCnt2:%llu\r\n", IdleCycleCnt2);
		taskEXIT_CRITICAL();
		vTaskDelay(300);
	}

//	vTaskResumeAll();
}

void vTask1(void *Parameters)
{
	const char *pcTaskName = "Task1 is running\r\n";
	portTickType xLastWakeTime;
	UBaseType_t uxPriority;

	uxPriority = uxTaskPriorityGet(NULL);

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("%s", pcTaskName);
		vTaskPrioritySet(Task2_Handler, (uxPriority + 1));
	//Task1 is a periodic task with Delay
//		vTaskDelay(300);
//		vTaskDelayUntil(&xLastWakeTime, 1000);										/*Todo:API 'vTaskDelayUntil()' is not working properly*/
	}
}

void vTask2(void *Parameters)
{
	const char *pcTaskName = "Task2 is running\r\n";
	portTickType xLastWakeTime;
	UBaseType_t uxPriority;

	uxPriority = uxTaskPriorityGet(NULL);
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("%s", pcTaskName);
		vTaskPrioritySet(Task2_Handler, (uxPriority - 2));
	//Task2 is a continuous task without Delay
//		vTaskDelay(300);
//		vTaskDelayUntil(&xLastWakeTime, 1000);
	}
}

void vTaskTemplate(void *Parameters)
{
	char *pcTaskName;
	pcTaskName = (char *)Parameters;

	for(;;)
	{
		printf("%s", pcTaskName);
		vTaskDelay(1000);
	}

}

void StartTaskM(void *Parameters)
{
	taskENTER_CRITICAL();

	//No parameters
	xTaskCreate(vTask1, "Task1", 1000, NULL, 3, NULL);
	xTaskCreate(vTask2, "Task2", 1000, NULL, 2, &Task2_Handler);
//	xTaskCreate(vPrintIdleCycleCnt, "PrintIdleCycleCnt", 1000, NULL, 2, NULL);

	//Using template with parameters
//	xTaskCreate(vTaskTemplate, "Task1", 1000, pcInstance1, 2, NULL);
//	xTaskCreate(vTaskTemplate, "Task2", 1000, pcInstance2, 2, NULL);

	vTaskDelete(NULL);

	taskEXIT_CRITICAL();
}
