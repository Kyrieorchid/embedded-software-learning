
# FreeRTOS Task Notification APIs

## `xTaskNotify`
- **Prototype**:
  ```c
  BaseType_t xTaskNotify(TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction);
  ```
- **Description**: Sends a notification to a task and updates its notification value.

---

## `xTaskNotifyWait`
- **Prototype**:
  ```c
  BaseType_t xTaskNotifyWait(
      uint32_t ulBitsToClearOnEntry,
      uint32_t ulBitsToClearOnExit,
      uint32_t *pulNotificationValue,
      TickType_t xTicksToWait
  );
  ```
- **Description**: A task waits for a notification and optionally clears notification bits.

---

## `xTaskNotifyGive`
- **Prototype**:
  ```c
  void xTaskNotifyGive(TaskHandle_t xTaskToNotify);
  ```
- **Description**: Sends a notification to a task, incrementing its notification value.

---

## `ulTaskNotifyTake`
- **Prototype**:
  ```c
  uint32_t ulTaskNotifyTake(BaseType_t xClearCountOnExit, TickType_t xTicksToWait);
  ```
- **Description**: A task waits for a notification and decreases the notification value.

---

## `xTaskNotifyStateClear`
- **Prototype**:
  ```c
  BaseType_t xTaskNotifyStateClear(TaskHandle_t xTask);
  ```
- **Description**: Clears the notification state of a task.

---

## `xTaskNotifyIndexed`
- **Prototype**:
  ```c
  BaseType_t xTaskNotifyIndexed(
      TaskHandle_t xTaskToNotify,
      UBaseType_t uxIndexToNotify,
      uint32_t ulValue,
      eNotifyAction eAction
  );
  ```
- **Description**: Sends a notification to a specific index of a task’s notification array.

---

## `xTaskNotifyWaitIndexed`
- **Prototype**:
  ```c
  BaseType_t xTaskNotifyWaitIndexed(
      UBaseType_t uxIndexToWait,
      uint32_t ulBitsToClearOnEntry,
      uint32_t ulBitsToClearOnExit,
      uint32_t *pulNotificationValue,
      TickType_t xTicksToWait
  );
  ```
- **Description**: Waits for a notification on a specific index and optionally clears bits.

---

## `ulTaskNotifyTakeIndexed`
- **Prototype**:
  ```c
  uint32_t ulTaskNotifyTakeIndexed(
      UBaseType_t uxIndexToTake,
      BaseType_t xClearCountOnExit,
      TickType_t xTicksToWait
  );
  ```
- **Description**: Waits for and takes a notification from a specific index.

---

## `xTaskNotifyGiveIndexed`
- **Prototype**:
  ```c
  void xTaskNotifyGiveIndexed(TaskHandle_t xTaskToNotify, UBaseType_t uxIndexToNotify);
  ```
- **Description**: Sends a notification to a specific index, incrementing its notification value.

---

## `vTaskNotifyGiveFromISR`
- **Prototype**:
  ```c
  void vTaskNotifyGiveFromISR(TaskHandle_t xTaskToNotify, BaseType_t *pxHigherPriorityTaskWoken);
  ```
- **Description**: Sends a notification to a task from an ISR.

---

## `xTaskNotifyFromISR`
- **Prototype**:
  ```c
  BaseType_t xTaskNotifyFromISR(
      TaskHandle_t xTaskToNotify,
      uint32_t ulValue,
      eNotifyAction eAction,
      BaseType_t *pxHigherPriorityTaskWoken
  );
  ```
- **Description**: Sends a notification to a task from an ISR with specific action.

---

## `xTaskNotifyGiveIndexedFromISR`
- **Prototype**:
  ```c
  void xTaskNotifyGiveIndexedFromISR(
      TaskHandle_t xTaskToNotify,
      UBaseType_t uxIndexToNotify,
      BaseType_t *pxHigherPriorityTaskWoken
  );
  ```
- **Description**: Sends a notification to a specific index of a task’s notification array from an ISR.
