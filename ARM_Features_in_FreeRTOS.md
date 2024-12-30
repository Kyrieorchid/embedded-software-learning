
# ARM特性在FreeRTOS中的作用

## 1. MSP 和 PSP
- **MSP（Main Stack Pointer）**  
  Cortex-M 内核有两个堆栈指针：
  - MSP 是主堆栈指针，主要用于异常处理程序（包括中断）和系统初始化。
  - 在 FreeRTOS 中，MSP 通常用于处理内核态任务（如中断和调度器）。

- **PSP（Process Stack Pointer）**  
  PSP 是进程堆栈指针，专为用户任务而设计。  
  - FreeRTOS 在任务切换时切换到 PSP，为每个任务提供独立的堆栈。
  - 这种堆栈分离增强了系统的安全性和稳定性。

---

## 2. SysTick
- **系统滴答定时器**  
  SysTick 是 Cortex-M 提供的一个硬件定时器，FreeRTOS 用于生成内核时钟节拍。  
  - 实现时间片轮转调度（时间片调度任务）。
  - 提供任务延时功能（如 `vTaskDelay`）。
  - 用于计时器服务模块。

---

## 3. PendSV
- **挂起的系统服务异常**  
  PendSV 是 Cortex-M 提供的一个异常，专门用于上下文切换。
  - FreeRTOS 使用 PendSV 异常触发任务切换。
  - PendSV 优先级较低，不会干扰高优先级中断。

---

## 4. SVC
- **超级用户调用（Supervisor Call）**  
  SVC 是通过软件触发的异常，用于执行系统级操作。
  - FreeRTOS 使用 SVC 初始化内核，例如启动第一个任务。
  - 在 FreeRTOS 的启动过程中，SVC 切换到 PSP 并进入第一个任务。

---

## 5. 排他访问指令
- **LDREX/STREX**  
  Cortex-M 提供的排他访问指令用于实现原子操作。
  - FreeRTOS 利用这些指令实现任务间的同步机制，例如队列和信号量。
  - 避免资源争用，保证数据一致性。

---

## 6. FreeRTOS 低功耗机制
- **WFI 和 WFE 指令**  
  - 在 FreeRTOS 的 Tickless Idle 模式中，使用 `WFI`（Wait For Interrupt）或 `WFE`（Wait For Event）指令将处理器置于低功耗状态。
  - 系统空闲时调用 `portSUPPRESS_TICKS_AND_SLEEP`，结合 SysTick 或外部定时器中断唤醒系统。
