#include <stdio.h>
#include "Mcu.h"
#include "Mcu_Drv.h"
#include "Port_Drv.h"
#include "Uart_Drv.h"
#include "FreeRTOS.h"
#include "task.h"
#include "taskm.h"
/****************************************************************************
*    BSP包移植注意事项：
*    1.FreeRTOS需要用到SysTick中断，在base的界面配置中请勿打开System Tick Irq Enable开关
*    2.只能使用GCC编译器，使用其他编译器需要重新移植
****************************************************************************/

void StartTaskM(void *Parameters);
void StartQueueM(void *Parameters);

int main(void)
{
    uint32 SystemClock = 0;
    /* 时钟初始化 */
    Mcu_Init(NULL_PTR);
#if (MCU_INIT_CLOCK == STD_ON)
    Mcu_InitClock(0);
#endif
#if (MCU_NO_PLL == STD_OFF)
    Mcu_DistributePllClock();
#endif
    /* IO和Uart初始化 */
    Port_Drv_Init(&Port_ConfigData);
    Uart_Drv_Init(NULL_PTR);

    Mcu_Drv_Clk_GetPeriph(MCU_CLOCK_SYSTEM, &SystemClock);
    printf("Frequency of processor %dMHZ\r\n", SystemClock / 1000 / 1000);
/**********************************************************************************/
    //==============================TASK MANAGEMENT
//    xTaskCreate(StartTaskM,
//    			"StartTaskManagement",
//				1000,
//				NULL,
//				1,
//				NULL);

    //===============================QUEUE MANAGEMENT
    xTaskCreate(StartQueueM, "StartQueueManagement", 1000, NULL, 1, NULL);

    vTaskStartScheduler();
/**********************************************************************************/
}


