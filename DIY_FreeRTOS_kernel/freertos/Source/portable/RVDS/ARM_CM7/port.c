#include "FreeRTOS.h"
#include "port.h"
#include "list.h"
#include "task.h"

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK					( 0xFFUL )

BaseType_t xTaskIncrementTick(void);
void vPortSetupTimerInterrupt(void);

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

static void prvTaskExitError(void)
{
	//Halted here.
	for(;;);
}

StackType_t *pxPortInitialiseStack(StackType_t * pxTopOfStack, TaskFunction_t pxCode, void * pvParameters)
{
	/*Stack Structure
		xPSR		(bit24==1)
		r15(PC)	entry of task function
		r14(LR)	entry of prvTaskExitError(), when task function returns which is not expected.
		r12:0
	  r3:0
	  r2:0
	  r1:0
	  r0:Parameters
		r4~r11:Initialise as zero
	*/
	pxTopOfStack--;
	*pxTopOfStack = protINITIAL_XPSR; //bit24 must be 1, represents 'Thumb' ISA.
	pxTopOfStack--;
	/*Thumb requires PC 2B-aligned, but as a function pointer 'pxCode', its bit0 must be 1 to represent 'Thumb' ISA.*/
	*pxTopOfStack = ((StackType_t)pxCode) & portSTART_ADDRESS_MASK;
	pxTopOfStack--;
	*pxTopOfStack = (StackType_t)prvTaskExitError;
	pxTopOfStack -= 5;
	*pxTopOfStack = (StackType_t)pvParameters;
	
	pxTopOfStack -= 8;//r4~r11 register, initialise as 0.
	
	return pxTopOfStack;
}


__asm void prvStartFirstTask( void )
{
	PRESERVE8

	/* Use the NVIC offset register to locate the stack. */
	ldr r0, =0xE000ED08
	ldr r0, [r0]
	ldr r0, [r0]
	/* Set the msp back to the start of the stack. */
	msr msp, r0
	/* Clear the bit that indicates the FPU is in use in case the FPU was used
	before the scheduler was started - which would otherwise result in the
	unnecessary leaving of space in the SVC stack for lazy saving of FPU
	registers. */
	//mov r0, #0
	//msr control, r0
	/* Globally enable interrupts. */
	cpsie i
	cpsie f
	dsb
	isb
	/* Call SVC to start the first task. */
	svc 0
	nop
	nop
}

__asm void vPortSVCHandler( void )
{	
	extern pxCurrentTCB;
	
	PRESERVE8
	
	/* Get the location of the current TCB. */
	ldr	r3, =pxCurrentTCB
	ldr r1, [r3]
	ldr r0, [r1]
	/* Pop the core registers. */
	//ldmia r0!, {r4-r11, r14}
	ldmia r0!, {r4-r11}
	msr psp, r0
	isb
	mov r0, #0
	msr	basepri, r0
	
	orr r14, #0xd //1101 *EXC_RETURN* Use PSP to pop and return to thumb status
	
	bx r14
}

BaseType_t xPortStartScheduler()
{
	//Set Systick's&Pendsv's priority 255.
	portNVIC_SYSPRI2_REG |= protNVIC_PENDSV_PRI;
	portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;
	
	//Initialise Systick.
	vPortSetupTimerInterrupt();
	
	prvStartFirstTask();
	
	return 0;
}

__asm void xPortPendSVHandler(void)
{
	extern pxCurrentTCB;
	extern vTaskSwitchContext;
	
	PRESERVE8
	
	mrs r0, psp
	isb
	
	ldr r3, =pxCurrentTCB
	ldr r2, [r3]
	
	stmdb r0!, {r4-r11}
	str r0, [r2]
	
	stmdb sp!, {r3, r14}
	
	mov r0, #configMAX_SYSCALL_INTERRUPT_PRIORITY
	msr basepri, r0
	dsb
	isb
	bl vTaskSwitchContext
	mov r0, #0
	msr basepri, r0
	ldmia sp!, {r3, r14}
	
	ldr r1, [r3]
	ldr r0, [r1]
	ldmia r0!, {r4-r11}
	msr psp, r0
	isb
	
	bx r14
}

void vPortEnterCritical(void)
{
	portDISABLE_INTERRUPTS();
	uxCriticalNesting++;
	
	if(uxCriticalNesting == 1)
	{
		configASSERT(( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0);
	}
}

void vPortExitCritical(void)
{
	configASSERT(uxCriticalNesting);
	uxCriticalNesting--;
	if(uxCriticalNesting == 0)
	{
		portENABLE_INTERRUPTS();
	}
}

void xPortSysTickHandler(void)
{
	/* The SysTick runs at the lowest interrupt priority, so when this interrupt
	executes all interrupts must be unmasked.  There is therefore no need to
	save and then restore the interrupt mask value as its value is already
	known. */
	portDISABLE_INTERRUPTS();
	//Update system_time_base counter
	if(xTaskIncrementTick() != pdFALSE)
	{
		taskYIELD();
	}
	
	portENABLE_INTERRUPTS();
}

void vPortSetupTimerInterrupt(void)
{
	//Set Systick reload value.
	portNVIC_SYSTICK_LOAD_REG = (configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ) - 1UL;
	//Set Systick CLK as kernel CLK, enable Systick as well its interrupt.
	portNVIC_SYSTICK_CTRL_REG = (portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT);
}
