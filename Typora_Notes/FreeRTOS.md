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
    |--|--|
    |私有函数|prv|
    |void|v|
    |portBASE_TYPE|x|

4. 宏

    * 小写字母前缀 + 大写字母，前缀表示定义该宏的头文件，such as：`taskENTER_CRITICAL()` is defined in `task.h`。
    * 要注意的是信号量的函数都是一个宏定义，但是它的函数的命名方法是遵循函数的命名方法而不是宏定义的方法。
    * 通用宏：
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

## 