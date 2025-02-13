
# FreeRTOS Semaphore API

## Semaphore Creation
1. **`xSemaphoreCreateBinary`**
   - **Functionality**: Create a binary semaphore.

2. **`xSemaphoreCreateCounting`**
   - **Functionality**: Create a counting semaphore.

3. **`xSemaphoreCreateMutex`**
   - **Functionality**: Create a mutex.

4. **`xSemaphoreCreateRecursiveMutex`**
   - **Functionality**: Create a recursive mutex.

## Semaphore Giving
5. **`xSemaphoreGive`**
   - **Functionality**: Release a semaphore.

6. **`xSemaphoreGiveFromISR`**
   - **Functionality**: Release a semaphore from ISR.

7. **`xSemaphoreGiveRecursive`**
   - **Functionality**: Release a recursive mutex.

## Semaphore Taking
8. **`xSemaphoreTake`**
   - **Functionality**: Acquire a semaphore.

9. **`xSemaphoreTakeRecursive`**
   - **Functionality**: Acquire a recursive mutex.

## Semaphore State
10. **`uxSemaphoreGetCount`**
    - **Functionality**: Get the current count of a counting semaphore.

## Macro-Based APIs
11. **`pdTRUE` / `pdFALSE`**
    - **Functionality**: Boolean values used for semaphore operations.

12. **`configUSE_COUNTING_SEMAPHORES`**
    - **Functionality**: Enable or disable counting semaphores.
