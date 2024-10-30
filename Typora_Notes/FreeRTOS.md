# FreeRTOS入门手册

## 任务管理

## 队列管理

## 中断管理

## 资源管理

## 内存管理

## 错误排查


# 野火FreeRTOS-内核实现与应用

## A Glance, Coding Style

1. 数据类型

    * 对标准c数据类型重定义，such as`#define portCHAR char`，其中port表示接口的意思，即在移植到不同cpu上时需要其作为“中间变量”。
    portTickType -> unsigned shortint/unsigned int，由宏选择；
    portBASE_TYPE -> long，ARM中为32位。

    * 在FreeRTOS中，int型从不使用，只使用short和 long型。在Cortex-M内核的MCU中，short为16位，long为32位。

    * 对于char，若没有显示说明有/无符号，则由编译器决定，所以code中要指定符号。

2. 变量名

    * 类型作为前缀：
    |type|pre|
    |--|--|
    |char|c|
    |short|s|
    |long|l|
    |portBASE_TYPE|x|
    |数据结构、任务句柄、队列句柄|x|
    |unsigned|u|
    |pointer|p|

3. 函数名

    * 返回类型作为前缀：
    | | |
    |--|--|
    |私有函数|prv|
    |void|v|
    |portBASE_TYPE|x|

4. 宏

    * 小写字母前缀 + 大写字母，前缀表示定义该宏的头文件，such as：`taskENTER_CRITICAL()` is defined in `task.h`。
    * 要注意的是信号量的函数都是一个宏定义，但是它的函数的命名方法是遵循函数的命名方法而不是宏定义的方法。
    * 通用宏：
    | | |
    |--|--|
    |pdTRUE|1|
    |pdFALSE|0|
    |pdPASS|1|
    |pdFAIL|0|

5. 格式

    * 一个tab键盘等于四个空格键。我们在编程的时候最好使用空格键而不是使用tab键，当两个编译器的tab键设置的大小不 一样的时候，代码移植的时候代码的格式就会变乱，而使用空格键则不会出现这种问题。

## 裸机与多任务系统

1. 裸机系统：
    1.1 轮询系统
        循环地顺序执行各操作。
    1.2 前后台系统
        前台中断实时响应事件，后台轮询处理事件。
2. 多任务系统
    中断实时响应事件，处理事件的任务具有优先级，若优先级足够高，事件可立即处理。

对于中断事件，如果事件要处理的事情很简短，则可在中断服务程序里面处理，如果事件要处理的事情比较多，则返回到后台程序或者任务里面处理。

## 链表实现

1. 双向循环链表、尾（根）节点、Index常指向尾节点、按节点Value升序插入/插入尾部。

## 任务的定义&切换

### 概述

1. 任务是<u>独立函数</u>，主体<u>无限循环</u><u>不能返回</u>，每个任务分配有独立的栈（以字为单位）。
2. 任务由系统调度，它为每个任务额外定义一个<b>任务控制块(struct tskTaskControlBlock)</b>，相当于该任务的ID Card，存储包括任务的栈指针、任务名和形参等。
3. 任务控制块中包含`ListTtem_t`的任务节点，通过该节点可以将任务<u>挂载</u>到不同链表。

### 任务创建函数的实现

1. 动态创建：任务的栈与内存动态分配，删除任务时可释放；
    静态创建：事先定义好栈与内存，删除任务不能释放。
2. 创建任务就是将任务的栈、函数实体和任务控制块联系起来，包括初始化栈、TCB和返回指向TCB的任务句柄等。
3. 任务栈中存有任务入口位置、形参等，上下文切换时会弹栈到cpu寄存器，比如entry被弹到PC，从而跳转任务。

### 就绪态任务列表的实现
任务创建后需要添加到不同链表中，如就绪态任务列表。

1. 就绪列表：<u><b>List_t类型的数组，不同下标对应不同优先级，同一优先级的任务在同一List中。</b></u>（最大支持256个优先级）
2. Insert/InsertEnd将TCB中的节点添加到相应的链表中。

### 调度器Scheduler

1. 配置PendSV和SysTick的中断优先级为最低。SysTick和PendSV都会涉及系统调度，系统调度的优先级要低于系统的其他硬件中断优先级。
2. <u><b>任务切换通过软件触发PnedSV，在Handler中实现上下文切换，调度器在每个Systick Handler中判断是否要切换，若有则置起PendSV挂起位。</b></u>就是在就绪列表中寻找最高优先级任务并执行，多个最高优先级按时间片执行。

## Critical临界段

Simply, critical region is a section of instructions that can't be interrupted. The kernel protects it by ENABLE/DISABLE interrupt through PRIMASK, FAULTMASK and BASEPRI.

1. 在FreeRTOS中通过BASEPRI操作中断的开关，BASEPRI屏蔽自身及以下优先级的中断响应。（PRIMASK置1只响应NMI(-2) & HardFault(-1)，FaultMASK只响应NMI）。

## 空闲任务与延时阻塞

1. 阻塞延时：任务中需要延时时，进入阻塞状态，cpu运行其他任务，若没有任务可运行则进入空闲任务，IDLEtask是在启用调度器时创建的优先级最低的任务，主要做内存的回收，也可在空闲任务中让cpu休眠。