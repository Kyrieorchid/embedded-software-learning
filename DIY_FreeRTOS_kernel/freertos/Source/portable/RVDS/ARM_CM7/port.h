#ifndef PORT_H
#define PORT_H

#include "FreeRTOS.h"

#define portNVIC_SYSPRI2_REG (*((volatile uint32_t*)0xE000ED20))
#define portNVIC_SYSTICK_CTRL_REG (*((volatile uint32_t *)0xe000e010 ))
#define portNVIC_SYSTICK_LOAD_REG (*((volatile uint32_t *)0xe000e014 ))
	
#ifndef configSYSTICK_CLOCK_HZ
	#define configSYSTICK_CLOCK_HZ configCPU_CLOCK_HZ
	//To makesure the CLKs of Systick and kernel are the same.
	#define portNVIC_SYSTICK_CLK_BIT ( 1UL << 2UL )
#else
	#define portNVIC_SYSTICK_CLK_BIT ( 0 )
#endif

#define portNVIC_SYSTICK_INT_BIT ( 1UL << 1UL )
#define portNVIC_SYSTICK_ENABLE_BIT ( 1UL << 0UL)

#define configKERNEL_INTERRUPT_PRIORITY 255
#define protNVIC_PENDSV_PRI ((uint32_t)(configKERNEL_INTERRUPT_PRIORITY << 16UL))
#define portNVIC_SYSTICK_PRI ((uint32_t)(configKERNEL_INTERRUPT_PRIORITY << 24UL))
#define protINITIAL_XPSR	(0x01000000)
#define portSTART_ADDRESS_MASK ((StackType_t)0xfffffffeUL)


StackType_t *pxPortInitialiseStack(StackType_t * pxTopOfStack, TaskFunction_t pxCode, void * pvParameters);
BaseType_t xPortStartScheduler(void);
void vPortSetupTimerInterrupt(void);

#endif /*PORT_H*/
