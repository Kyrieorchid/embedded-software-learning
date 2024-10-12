#include "queueM.h"

xQueueHandle xQueue;

void vSenderTask(void *Parameters);
void vReceiverTask(void *Parameters);

typedef struct
{
	uint8 ucValue;
	uint8 ucSource;
}xData;

static const xData xStruct2Send[2] =
{
		{100, 101},
		{200, 201}
};

void StartQueueM(void *Parameters)
{
	taskENTER_CRITICAL();
	xQueue = xQueueCreate(3, sizeof(xData));

	xTaskCreate(vSenderTask, "Send1", 1000, &(xStruct2Send[0]), 3, NULL);
	xTaskCreate(vSenderTask, "Send2", 1000, &(xStruct2Send[1]), 3, NULL);
	xTaskCreate(vReceiverTask, "Receive", 1000, NULL, 2, NULL);

	vTaskDelete(NULL);
	taskEXIT_CRITICAL();
}

void vSenderTask(void *Parameters)
{
//	long lValue2Send;
	portBASE_TYPE xStatus;

//	lValue2Send = (xData)Parameters;

	for(;;)
	{
		//Receive task has higher priority, it will take the data ASAP from the queue so the queue is always empty when Send task running.
		xStatus = xQueueSendToBack(xQueue, (xData *)Parameters, 100);

		if(xStatus != pdPASS)
		{
			printf("Send to queue FAILED!\r\n");
		}

		//Discard the remaining time slice.
		taskYIELD();
	}
}

void vReceiverTask(void *pvParameters)
{
	xData lReceivedValue;
	portBASE_TYPE xStatus;

	for(;;)
	{

		/*This task will be blocked at 'xQueueReceive' from where it will re-run when it's unblocked,
		 * that is, get the data and remove it from the queue,
		 * so the queue is always empty here as a new loop starts.*/
		if(uxQueueMessagesWaiting(xQueue) != 3)
		{
			printf("Queue is supposed to be empty!");
		}
		/**/

		xStatus = xQueueReceive(xQueue, &lReceivedValue, 0);
		if(xStatus == pdPASS)
		{
				printf("Received data from %d: %d\r\n", lReceivedValue.ucSource, lReceivedValue.ucValue);

		}
		else
		{
			printf("Have not received any data from queue\r\n");
		}
	}
}
