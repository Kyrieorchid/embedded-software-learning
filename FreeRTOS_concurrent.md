# FreeRTOS 中全局变量的并发问题及应对措施

## 背景
在单核 CPU 上运行 FreeRTOS 时，虽然 FreeRTOS 模拟了多任务并发，但由于单核的特性，CPU 在任何时刻只会执行一个任务。任务间的并发访问问题主要来源于以下两种情况：

1. **任务切换**：多个任务访问同一个全局变量，可能因任务调度引发冲突。
2. **中断与任务的竞争**：中断处理程序（ISR）和任务同时访问全局变量，可能引发数据不一致。

因此，正确处理全局变量的并发访问问题是开发稳定可靠系统的关键。

---

## 并发访问的场景分析

### 场景 1: 只有一个任务访问全局变量
- 如果只有一个任务访问某个全局变量，且没有中断访问该变量，则不需要额外的保护措施。

### 场景 2: 多个任务访问全局变量
- 如果多个任务需要访问同一个全局变量，任务切换可能导致访问冲突。例如：
  - 一个任务正在写入全局变量，但尚未完成写入时，发生了任务切换。
- **解决方法**：
  - 使用 FreeRTOS 的同步机制（如互斥锁或信号量）。

### 场景 3: 中断与任务同时访问全局变量
- 如果中断和任务共享某个全局变量，可能发生以下问题：
  - 任务在访问变量时被中断，导致中断修改了该变量的值，任务最终读取到不一致的数据。
- **解决方法**：
  - 禁用中断保护代码段。
  - 使用 FreeRTOS 提供的中断屏蔽函数。

---

## 应对并发问题的保护措施

### 1. 使用互斥锁
FreeRTOS 提供的互斥锁（Mutex）可以保护共享资源，避免任务间的竞争。

```c
xSemaphoreTake(xMutex, portMAX_DELAY);
global_var = new_value;
xSemaphoreGive(xMutex);
```

**优点**：
- 易于使用。
- 支持优先级继承，避免优先级反转问题。

**缺点**：
- 只能用于任务之间，不适用于中断。

---

### 2. 使用关键区
通过 `taskENTER_CRITICAL()` 和 `taskEXIT_CRITICAL()` 禁用中断，保护临界区代码。

```c
taskENTER_CRITICAL();
global_var = new_value;
taskEXIT_CRITICAL();
```

**优点**：
- 适用于任务和中断共享全局变量的场景。

**缺点**：
- 禁用中断会影响系统实时性。
- 不适合长时间运行的临界区。

---

### 3. 使用原子操作
对于简单的变量更新操作，可以使用硬件或编译器提供的原子操作指令。

```c
__atomic_add_fetch(&global_var, 1, __ATOMIC_SEQ_CST);
```

**优点**：
- 高效，避免了禁用中断。

**缺点**：
- 不适用于复杂的数据操作。

---

### 4. 使用 FreeRTOS 队列
通过 FreeRTOS 队列，可以在任务之间安全传递数据，而无需直接访问全局变量。

```c
xQueueSend(xQueue, &value, portMAX_DELAY);
xQueueReceive(xQueue, &received_value, portMAX_DELAY);
```

**优点**：
- 任务间数据传递的安全方法。

**缺点**：
- 较复杂的数据操作可能影响性能。

---

### 5. 使用中断屏蔽函数
FreeRTOS 提供 `portSET_INTERRUPT_MASK_FROM_ISR()` 和 `portCLEAR_INTERRUPT_MASK_FROM_ISR()` 来屏蔽中断，保护共享资源。

```c
UBaseType_t uxSavedInterruptStatus;
uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
global_var = new_value;
portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedInterruptStatus);
```

**优点**：
- 适用于中断和任务共享全局变量的场景。

**缺点**：
- 会影响部分中断的响应时间。

---

## 注意事项
1. **声明 `volatile` 全局变量**：
   如果中断和任务都访问某个全局变量，建议使用 `volatile` 关键字声明变量，确保编译器不会优化掉对该变量的访问。

   ```c
   volatile int global_var;
   ```

2. **减少临界区长度**：
   在临界区内只执行必要操作，避免长时间占用 CPU。

3. **任务优先级设计**：
   合理设计任务优先级，避免高优先级任务频繁打断低优先级任务对全局变量的访问。

---

## 总结
在 FreeRTOS 的单核环境中，全局变量的并发访问主要来源于任务切换和中断。通过互斥锁、关键区、原子操作、队列或中断屏蔽函数，可以有效解决并发问题。选择合适的保护方法需要综合考虑系统的实时性、复杂性和性能需求。
