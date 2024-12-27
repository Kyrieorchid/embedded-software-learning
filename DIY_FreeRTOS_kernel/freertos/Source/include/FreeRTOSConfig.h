#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 1

#define configUSE_16_BIT_TICKS 0
#define configMAX_TASK_NAME_LEN 16
#define configSUPPORT_STATIC_ALLOCATION 1
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 5
#define configMAX_PRIORITIES 6 //Priority can be 0~4.
#define configMINIMAL_STACK_SIZE ((unsigned short) 128)
	
#define configCPU_CLOCK_HZ ((unsigned long)25000000)
#define configTICK_RATE_HZ ((TickType_t)100)

#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
#define vPortSVCHandler SVC_Handler

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { portDISABLE_INTERRUPTS(); for( ;; ); }

#endif /*FREERTOS_CONFIG_H*/
