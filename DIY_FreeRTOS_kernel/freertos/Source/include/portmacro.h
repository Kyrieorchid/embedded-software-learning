#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "stdint.h"
#include "stddef.h"

#define portINLINE __inline
#ifndef portFORCE_INLINE
	#define portFORCE_INLINE __forceinline
#endif

#define portCHAR char
#define portFLOAT float
#define portDOUBLE double
#define portLONG long
#define portSHORT short
#define portSTACK_TYPE uint32_t
#define portBASE_TYPE long

#define configUSE_OPTIMISED_TASK_SELECTION 1

#define portNVIC_INT_CTRL_REG (*((volatile uint32_t *)0xe000ed04))
#define portNVIC_PENDSVSET_BIT (1UL << 28UL)
#define portSY_FULL_READ_WRITE (15)
#define portYIELD()\
{\
	portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;\
	__dsb( portSY_FULL_READ_WRITE );\
	__isb( portSY_FULL_READ_WRITE );\
}

/*Using leading zero, every single bit of uxTopReadyPriority is a priority, 
'1' represents ready, therefore 31 minus 'lz' is the top ready priority.*/
#define protGET_HIGHEST_PRIORITY(uxTopPriority, uxTopReadyPriority) \
				(uxTopPriority) = (31UL - (uint32_t)__clz((uxTopReadyPriority)))

void vPortEnterCritical(void);
void vPortExitCritical(void);

#define portENTER_CRITICAL() vPortEnterCritical()

/*Disable intrrupt without return.*/
#define portDISABLE_INTERRUPTS() vPortRaiseBASEPRI()

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif

static portFORCE_INLINE void vPortRaiseBASEPRI(void)
{
	uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
	__asm
	{
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}
}
/*Disable intrrupt with return.*/
#define portSET_INTERRUPT_MASK_FROM_ISR() ulPortRaiseBASEPRI()

static portFORCE_INLINE uint32_t ulPortRaiseBASEPRI()
{
	uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;
	__asm
	{
		mrs ulReturn, basepri
		msr basepri, ulNewBASEPRI
		
		dsb
		isb
	}
	return ulReturn;
}

#define portEXIT_CRITICAL() vPortExitCritical()

/*Enable interrupt without return.*/
#define portENABLE_INTERRUPTS() vPortSetBASEPRI(0)
/*Enable interrupt with return.*/
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x) vPortSetBASEPRI(x)

static portFORCE_INLINE void vPortSetBASEPRI(uint32_t ulBASEPRI)
{
	__asm
	{
		msr basepri, ulBASEPRI
	}
}

#endif/* PORTMACRO_H */
