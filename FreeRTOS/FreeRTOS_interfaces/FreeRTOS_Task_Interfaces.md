
# FreeRTOS 任务管理接口列表

## **任务创建与删除**
1. **`BaseType_t xTaskCreate( TaskFunction_t pxTaskCode, const char * const pcName, configSTACK_DEPTH_TYPE usStackDepth, void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask );`**  
   **说明**：创建一个任务。

2. **`BaseType_t xTaskCreateStatic( TaskFunction_t pxTaskCode, const char * const pcName, const uint32_t ulStackDepth, void *pvParameters, UBaseType_t uxPriority, StackType_t * const puxStackBuffer, StaticTask_t * const pxTaskBuffer );`**  
   **说明**：创建静态任务 (用户提供栈和任务控制块)。

3. **`void vTaskDelete( TaskHandle_t xTaskToDelete );`**  
   **说明**：删除任务。

## **任务调度与控制**
4. **`void vTaskStartScheduler( void );`**  
   **说明**：启动任务调度器。

5. **`void vTaskEndScheduler( void );`**  
   **说明**：停止调度器，系统停止运行 (通常用于模拟环境)。

6. **`void vTaskSuspend( TaskHandle_t xTaskToSuspend );`**  
   **说明**：挂起任务。

7. **`void vTaskResume( TaskHandle_t xTaskToResume );`**  
   **说明**：恢复被挂起的任务。

8. **`void vTaskResumeFromISR( TaskHandle_t xTaskToResume );`**  
   **说明**：在中断服务函数 (ISR) 中恢复任务。

9. **`void vTaskDelay( const TickType_t xTicksToDelay );`**  
   **说明**：任务延时指定的时间片。

10. **`void vTaskDelayUntil( TickType_t *pxPreviousWakeTime, const TickType_t xTimeIncrement );`**  
    **说明**：相对时间延时 (实现周期性任务)。

## **任务优先级管理**
11. **`void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority );`**  
    **说明**：设置任务的优先级。

12. **`UBaseType_t uxTaskPriorityGet( TaskHandle_t xTask );`**  
    **说明**：获取任务的优先级。
