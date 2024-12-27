#ifndef _QUEUE_H
#define _QUEUE_H

#include "FreeRTOS.h"
#include "list.h"

typedef struct QueueDefinition
{
    int8_t *pcHead;
    int8_t *pcTail;
    int8_t *pcWriteTo;  //指向下一个可用的空间（Current available sapce）

    union   //用union实现两个互斥变量，同时只能存储一个变量的值
    {
        int8_t *pcReadFrom; //指向下一个即将出队的消息
        UBaseType_t uxRecursiveCallCount;
    }u;

    List_t xTasksWaitingToSend; //等待向该队列发送的任务列表（队列满）
    List_t xTasksWaitingToReceive;  //等待从该队列读取的任务列表（队列空）
    
    volatile UBaseType_t uxMessagesWaiting; //该列表当前有多少个消息
    UBaseType_t uxLength;
    UBaseType_t uxItemSize;

    //读写锁，确保同一时间只有一个中断或任务操作队列
    volatile int8_t cRxLock;
    volatile int8_t cTxLock;

#if((configSUPPORT_STATIC_ALLOCATION == 1) && (configSUPPORT_DYNAMIC_ALLOCATION == 1))
    uint8_t ucStaticallyAllocated;
#endif

#if(configUSE_QUEUE_SETS == 1)
    struct QueueDefinition *pxQueueSetContainer;
#endif

#if(configUSE_TRACE_FACILITY == 1)
    UBaseType_t uxQueueNumber;
    uint8_t ucQueueType;
#endif
}xQueue;

typedef xQueue Queue_t;

#endif
