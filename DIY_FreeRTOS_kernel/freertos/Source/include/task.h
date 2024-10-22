#ifndef TASK_H
#define TASK_H

#include "FreeRTOS.h"
#include "list.h"
#include "portmacro.h"

#define taskENTER_CRITICAL() portENTER_CRITICAL()
#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()
#define taskEXIT_CRITICAL() portEXIT_CRITICAL()
#define taskEXIT_CRITICAL_FROM_ISR(x) portCLEAR_INTERRUPT_MASK_FROM_ISR(x)

#define taskYIELD() portYIELD()

extern List_t pxReadyTaskLists[configMAX_PRIORITIES];

typedef void * TaskHandle_t;

typedef struct tskTaskControlBlock
{
	volatile StackType_t * pxTopOfStack;
	ListItem_t xStateListItem;
	StackType_t * pxStack;
	char pcTaskName[configMAX_TASK_NAME_LEN];
	
	TickType_t xTicksToDelay;
}tskTCB;
typedef tskTCB TCB_t;

TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
																	const char * const pcName,
																	const uint32_t ulStackDepth,
																	void * const pvParameters,
																	StackType_t * const puxStackBuffer,
																	TCB_t * const pxTaskBuffer);
void prvInitialiseTaskLists(void);
void vTaskStartScheduler(void);
void vTaskDelay(const TickType_t xTicks2Delay);																	
#endif /*TASK_H*/
