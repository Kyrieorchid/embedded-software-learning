
# FreeRTOS Event Groups API

## Event Group Creation and Deletion
1. **`xEventGroupCreate`**
   - **Functionality**: Create a new event group.
   - **Returns**: Handle to the created event group; `NULL` if creation fails.

2. **`vEventGroupDelete`**
   - **Functionality**: Delete an event group.
   - **Parameters**: Handle to the event group.

## Event Group Synchronization
3. **`xEventGroupSync`**
   - **Functionality**: Synchronize tasks using event bits.
   - **Parameters**: Event group handle, bits to set, bits to wait for, timeout.

## Event Bits Management
4. **`xEventGroupSetBits`**
   - **Functionality**: Set event bits in the event group.
   - **Parameters**: Event group handle, bits to set.
   - **Returns**: Previous event group value.

5. **`xEventGroupClearBits`**
   - **Functionality**: Clear event bits in the event group.
   - **Parameters**: Event group handle, bits to clear.

6. **`xEventGroupWaitBits`**
   - **Functionality**: Wait for specific bits to be set.
   - **Parameters**: Event group handle, bits to wait for, clear on exit, wait all, timeout.

7. **`xEventGroupGetBits`**
   - **Functionality**: Get the current value of the event bits.
   - **Parameters**: Event group handle.

8. **`xEventGroupGetBitsFromISR`**
   - **Functionality**: Get event bits value from ISR context.
   - **Parameters**: Event group handle.

## Macro-Based APIs
9. **`pdTRUE` / `pdFALSE`**
   - **Functionality**: Boolean values used for event group checks.

10. **`portMAX_DELAY`**
    - **Functionality**: Used as the maximum delay value for waiting on event bits.
