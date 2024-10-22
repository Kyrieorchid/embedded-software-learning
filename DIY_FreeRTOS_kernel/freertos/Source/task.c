#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
#include "port.h"

TCB_t * pxCurrentTCB;
extern TCB_t Task1TCB, Task2TCB, IdleTaskTCB;
extern StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
extern TaskHandle_t xIdleTaskHandle;
extern TCB_t IdleTaskTCB;
extern StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
List_t pxReadyTaskLists[configMAX_PRIORITIES];


	
static void prvInitialiseNewTask(TaskFunction_t pxTaskCode, const char * const pcName,
																const uint32_t ulStackDepth, void * const pvParameters,
																TaskHandle_t * const pxCreatedTask, TCB_t * pxNewTCB)
{
	/*Actually initialise the TCB of new task.*/
	StackType_t *pxTopOfStack;
	UBaseType_t x;
	
	pxTopOfStack = pxNewTCB->pxStack + (ulStackDepth - (uint32_t)1);
	pxTopOfStack = (StackType_t *)((uint32_t)pxTopOfStack & (~((uint32_t)0x0007))); //Align 8B.
	
	for(x = (UBaseType_t)0;x < (UBaseType_t)configMAX_TASK_NAME_LEN;x++)
	{
		pxNewTCB->pcTaskName[x] = pcName[x];
		if(pcName[x] == '\0')
		{
			break;
		}
	}
	
	pxNewTCB->pcTaskName[configMAX_TASK_NAME_LEN - 1] = '\0'; //Cut off.
	
	vListInitialiseItem(&(pxNewTCB->xStateListItem));
	listSET_LIST_ITEM_OWNER(&(pxNewTCB->xStateListItem), pxNewTCB);
	
	pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);
	
	if((void *)pxCreatedTask != NULL)
	{
		*pxCreatedTask = (TaskHandle_t)pxNewTCB; //In parameters, 'TaskHandle_t * const pxCreatedTask', pxCreatedTask is 'void **'.
	}
}
	

#if (configSUPPORT_STATIC_ALLOCATION == 1)
	TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
																	const char * const pcName,
																	const uint32_t ulStackDepth,
																	void * const pvParameters,
																	StackType_t * const puxStackBuffer,
																	TCB_t * const pxTaskBuffer)
	{
		TCB_t * pxNewTCB;
		TaskHandle_t xReturn;
		
		if((puxStackBuffer != NULL) && (pxTaskBuffer != NULL))
		{
			pxNewTCB = (TCB_t *)pxTaskBuffer;
			pxNewTCB->pxStack = (StackType_t *)puxStackBuffer;
			
			prvInitialiseNewTask(pxTaskCode, pcName, ulStackDepth, pvParameters, &xReturn, pxNewTCB);
		}
		else
		{
			xReturn = NULL;
		}
		
		return xReturn;
	}
#endif /*configSUPPORT_STATIC_ALLOCATION*/

void prvInitialiseTaskLists(void)
{
	UBaseType_t uxPriority;
	
	for(uxPriority = (UBaseType_t)0U;uxPriority < configMAX_PRIORITIES;uxPriority++)
	{
		vListInitilise(&(pxReadyTaskLists[uxPriority]));
	}
}

/*************************************/
void prvIdleTask(void *pvParameters)
{
	for(;;)
	{
		//Doing nothing.
	}
}

void vApplicationGetIdleTaskMemory(TCB_t **ppxIdleTaskTCBBuffer,
																		StackType_t **ppxIdleTaskStackBuffer,
																		uint32_t *pulIdleTaskStackSize);
void vTaskStartScheduler(void)
{
	/***********Create Idle Task when start scheduler***************/
	TCB_t *pxIdleTaskTCBBuffer = NULL;
	StackType_t *pxIdleTaskStackBuffer = NULL;
	uint32_t ulIdleTaskStackSize;
	
	vApplicationGetIdleTaskMemory(&pxIdleTaskTCBBuffer, &pxIdleTaskStackBuffer, &ulIdleTaskStackSize);
	xIdleTaskHandle = xTaskCreateStatic((TaskFunction_t)prvIdleTask,
																				(char *)"Idle Task",
																				(uint32_t)ulIdleTaskStackSize,
																				(void *)NULL,
																				(StackType_t *)pxIdleTaskStackBuffer,
																				(TCB_t *)pxIdleTaskTCBBuffer);
	vListInsertEnd(&(pxReadyTaskLists[0]), &(pxIdleTaskTCBBuffer->xStateListItem));
	/***************************************************************/
	
	pxCurrentTCB = &Task1TCB;
	if(xPortStartScheduler() != pdFALSE)
	{
		//Never supposed to get here as scheduler started by 'xPortStartScheduler'.
	}
}

void vApplicationGetIdleTaskMemory(TCB_t **ppxIdleTaskTCBBuffer,
																		StackType_t **ppxIdleTaskStackBuffer,
																		uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	*ppxIdleTaskStackBuffer = IdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vTaskSwitchContext(void)
{
/*
	//Priority schedule is not provided until now
	if(pxCurrentTCB == &Task1TCB)
	{
		pxCurrentTCB = &Task2TCB;
	}
	else
	{
		pxCurrentTCB = &Task1TCB;
	}
*/ 
	//Newly involved idle task
	if(pxCurrentTCB == &IdleTaskTCB)
	{
		if(Task1TCB.xTicksToDelay == 0)
		{
			pxCurrentTCB = &Task1TCB;
		}
		else if(Task2TCB.xTicksToDelay == 0)
		{
			pxCurrentTCB = &Task2TCB;
		}
		else
		{
			return;
		}	
	}
	else if(pxCurrentTCB == &Task1TCB)
	{
		if(Task2TCB.xTicksToDelay == 0)
		{
			pxCurrentTCB = &Task2TCB;
		}
		else if(Task1TCB.xTicksToDelay != 0)
		{
			pxCurrentTCB = &IdleTaskTCB;
		}
		else
		{
			return;
		}
	}
	else if(pxCurrentTCB == &Task2TCB)
	{
		if(Task1TCB.xTicksToDelay == 0)
		{
			pxCurrentTCB = &Task1TCB;
		}
		else if(Task2TCB.xTicksToDelay != 0)
		{
			pxCurrentTCB = &IdleTaskTCB;
		}
		else
		{
			return;
		}
	}
}

void vTaskDelay(const TickType_t xTicks2Delay)
{
	TCB_t *pxTCB = NULL;
	pxTCB = pxCurrentTCB;
	
	pxTCB->xTicksToDelay = xTicks2Delay;
	
	taskYIELD();
}



















