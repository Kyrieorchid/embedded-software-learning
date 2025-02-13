
# FreeRTOS Timer API

## Timer Creation and Deletion
1. **`xTimerCreate`**
   - **Functionality**: Create a new software timer.
   - **Parameters**: Name, period, auto-reload, ID, callback function.

2. **`xTimerCreateStatic`**
   - **Functionality**: Create a timer using static memory.

3. **`xTimerDelete`**
   - **Functionality**: Delete a software timer.

## Timer Control
4. **`xTimerStart`**
   - **Functionality**: Start a timer.

5. **`xTimerStop`**
   - **Functionality**: Stop a timer.

6. **`xTimerReset`**
   - **Functionality**: Reset a timer.

7. **`xTimerChangePeriod`**
   - **Functionality**: Change a timer’s period.

8. **`xTimerStartFromISR`**
   - **Functionality**: Start a timer from ISR.

9. **`xTimerStopFromISR`**
   - **Functionality**: Stop a timer from ISR.

## Timer State
10. **`xTimerIsTimerActive`**
    - **Functionality**: Check if a timer is active.

11. **`pvTimerGetTimerID`**
    - **Functionality**: Get the ID of a timer.

## Macro-Based APIs
12. **`pdTRUE` / `pdFALSE`**
    - **Functionality**: Boolean values used for timer operations.

13. **`configUSE_TIMERS`**
    - **Functionality**: Enable or disable software timers.
