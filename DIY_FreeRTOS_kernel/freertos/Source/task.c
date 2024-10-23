#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
#include "port.h"

TCB_t * pxCurrentTCB;
TickType_t xTickCount;
extern TCB_t Task1TCB, Task2TCB, IdleTaskTCB;
extern StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
extern TaskHandle_t xIdleTaskHandle;
extern TCB_t IdleTaskTCB;
extern StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
List_t pxReadyTaskLists[configMAX_PRIORITIES];

static volatile UBaseType_t uxTopReadyPriority = tskIDLE_PRIORIY;
static volatile UBaseType_t uxCurrentNumberOfTasks = 0;

#define prvAddTaksToReadList(pxTCB) \
				taskRECORD_READY_PRIORITY((pxTCB)->uxPriority); \
				vListInsertEnd(&(pxReadyTaskLists[(pxTCB)->uxPriority]), &((pxTCB)->xStateListItem));

/*Look for ready task with the highest priority============================*/
#if (configUSE_OPTIMISED_TASK_SELECTION == 0)

	#define taskRECORD_READY_PRIORITY(uxPriority) \
	{ \
		if((uxPriority) > uxTopReadyPriority) \
		{ \
			uxTopPriority = uxPriority; \
		} \
	} /*taskRECORD_READY_PRIORITY*/
	/**************************************************/
	#define taskSELECT_HIGHEST_PRIORITY_TASK() \
	{ \
		UBaseType_t uxTopPriority = uxTopReadyPriority; \
		while(listLIST_IS_EMPTY(&(pxReadyList[uxTopPriority]))) \
		{ \
			--uxTopPriority; \
		} \
		listGET_OWNER_OF_NEXT_ENTRY(pxCurrentTCB, &(pxReadyList[uxTopPriority]); \
		uxTopReadyPriority = uxTopPriority; \
	} /*taskSELECT_HIGHEST_PRIORITY_TASK*/
	/**************************************************/
	#define taskRESET_READY_PRIORITY(uxPriority)
	#define portRESET_READY_PRIORITY(uxPriority, uxTopReadyPriority)
	
/*Optimised according to CPU Arch.*/
#else /*configUSE_OPTIMISED_TASK_SELECTION*/ //#################Using leading zeros#############/
	
	#define taskRECORD_READY_PRIORITY(uxPriority) \
					portRECORD_READY_PRIORITY(uxPriority, uxTopReadyPriority)
	#define portRECORD_READY_PRIORITY(uxPriority, uxReadyPriorities) \
						(uxReadyPriorities) |= (1UL << (uxPriority)) //Every single bit represents a priority, '1' means ready.
	#define portRESET_READY_PRIORITY(uxPriority, uxReadyPriorities) \
						(uxReadyPriorities) &= ~(1UL << (uxPriority))
	/**************************************************/
	#define taskSELECT_HIGHEST_PRIORITY_TASK() \
	{\
		UBaseType_t uxTopPriority; \
		protGET_HIGHEST_PRIORITY(uxTopPriority, uxTopReadyPriority); \
		listGET_OWNER_OF_NEXT_ENTRY(pxCurrentTCB, &(pxReadyTaskLists[uxTopPriority])); \
	}
	
	/**************************************************/
	
#if 0
	#define taskRESET_READY_PRIORITY(uxPriority) \//Attention
	{ \
		if(listCURRENT_LIST_LENGTH(&(pxReadyList[(uxTopPriority)])) == (UBaseType_t)0)\
		{ \
			portRESET_READY_PRIORITY((uxPriority), uxTopReadyPriority); \
		} \
	}
#else
	#define taskRESET_READY_PRIORITY(uxPriority) \
	{ \
		portRESET_READY_PRIORITY((uxPriority), uxTopReadyPriority); \
	}
#endif
	
#endif /*configUSE_OPTIMISED_TASK_SELECTION*/
/*Look for ready task with the highest priority==========================*/

static void prvInitialiseNewTask(TaskFunction_t pxTaskCode, const char * const pcName,
																const uint32_t ulStackDepth, void * const pvParameters,
																UBaseType_t uxPriority,TaskHandle_t * const pxCreatedTask,
																TCB_t * pxNewTCB)
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
	
	if(uxPriority >= (UBaseType_t)configMAX_PRIORITIES)
	{
		uxPriority = (UBaseType_t)configMAX_PRIORITIES - (UBaseType_t)1U;
	}
	pxNewTCB->uxPriority = uxPriority;
	
	pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);
	
	if((void *)pxCreatedTask != NULL)
	{
		*pxCreatedTask = (TaskHandle_t)pxNewTCB; //In parameters, 'TaskHandle_t * const pxCreatedTask', pxCreatedTask is 'void **'.
	}
}
	
static void prvAddNewTaskToReadyList(TCB_t *pxNewTCB)
{
	//vListInsertEnd(&(pxReadyTaskLists[pxNewTCB->uxPriority]), pxNewTCB->xStateListItem);
	taskENTER_CRITICAL();
	{
		uxCurrentNumberOfTasks++;
		if(pxCurrentTCB == NULL)
		{
			pxNewTCB = pxNewTCB;
			if(uxCurrentNumberOfTasks ==	1)
			{
				prvInitialiseTaskLists();
			}
		}
		else
		{
			if(pxCurrentTCB->uxPriority <= pxNewTCB->uxPriority)
			{
				pxCurrentTCB = pxNewTCB;
			}
		}
		
		prvAddTaksToReadList(pxNewTCB);
	}
	taskEXIT_CRITICAL();
}

#if (configSUPPORT_STATIC_ALLOCATION == 1)
	TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
																	const char * const pcName,
																	const uint32_t ulStackDepth,
																	void * const pvParameters,
																	UBaseType_t uxPriority,
																	StackType_t * const puxStackBuffer,
																	TCB_t * const pxTaskBuffer)
	{
		TCB_t * pxNewTCB;
		TaskHandle_t xReturn;
		
		if((puxStackBuffer != NULL) && (pxTaskBuffer != NULL))
		{
			pxNewTCB = (TCB_t *)pxTaskBuffer;
			pxNewTCB->pxStack = (StackType_t *)puxStackBuffer;
			
			prvInitialiseNewTask(pxTaskCode, pcName, ulStackDepth, pvParameters, uxPriority, &xReturn, pxNewTCB);
		
			prvAddNewTaskToReadyList(pxNewTCB);
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
																				(UBaseType_t)tskIDLE_PRIORIY,
																				(StackType_t *)pxIdleTaskStackBuffer,
																				(TCB_t *)pxIdleTaskTCBBuffer);
	//vListInsertEnd(&(pxReadyTaskLists[0]), &(pxIdleTaskTCBBuffer->xStateListItem));
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
	//Now multiple priorities schedule is accessiable.
	taskSELECT_HIGHEST_PRIORITY_TASK();
	
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

/*
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
*/
}

void xTaskIncrementTick(void)
{
	TCB_t * pxTCB = NULL;
	BaseType_t i = 0;
	
	const TickType_t xConstTickCount = xTickCount + 1;
	xTickCount = xConstTickCount;
	
	for(i = 0;i < configMAX_PRIORITIES;i++)
	{
		pxTCB = (TCB_t *)listGET_OWNER_OF_HEAD_ENTRY(&pxReadyTaskLists[i]);
		if(pxTCB->xTicksToDelay > 0)
		{
			pxTCB->xTicksToDelay --;
			
			if(pxTCB->xTicksToDelay == 0)
			{
				taskRECORD_READY_PRIORITY(pxTCB->uxPriority);
			}
		}
	}
	
	portYIELD();
}

void vTaskDelay(const TickType_t xTicks2Delay)
{
	TCB_t *pxTCB = NULL;
	pxTCB = pxCurrentTCB;
	
	pxTCB->xTicksToDelay = xTicks2Delay;
	
	/*Delay list is not supported yet.
	uxListRemove(&(pxTCB->xStateListItem));
	*/
	taskRESET_READY_PRIORITY(pxTCB->uxPriority);
	
	taskYIELD();
}
