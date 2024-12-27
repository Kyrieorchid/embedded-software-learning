
# FreeRTOS Queue API

## Queue Creation and Deletion
1. **`xQueueCreate`**
   - **Functionality**: Create a new queue.
   - **Parameters**: Queue length, item size.
   - **Returns**: Handle to the created queue.

2. **`xQueueCreateStatic`**
   - **Functionality**: Create a queue using static memory.

3. **`vQueueDelete`**
   - **Functionality**: Delete a queue.

## Queue Sending
4. **`xQueueSend`**
   - **Functionality**: Send an item to the queue.
   - **Parameters**: Queue handle, item, timeout.

5. **`xQueueSendFromISR`**
   - **Functionality**: Send an item from ISR.

6. **`xQueueOverwrite`**
   - **Functionality**: Overwrite the queue’s current value.

## Queue Receiving
7. **`xQueueReceive`**
   - **Functionality**: Receive an item from the queue.
   - **Parameters**: Queue handle, buffer, timeout.

8. **`xQueuePeek`**
   - **Functionality**: Peek at the item in the front of the queue.

9. **`xQueueReceiveFromISR`**
   - **Functionality**: Receive an item from ISR.

## Queue State
10. **`uxQueueMessagesWaiting`**
    - **Functionality**: Get the number of messages in the queue.

11. **`uxQueueSpacesAvailable`**
    - **Functionality**: Get the number of free spaces in the queue.

## Macro-Based APIs
12. **`configUSE_QUEUE_SETS`**
    - **Functionality**: Enable or disable queue sets.

13. **`queueQUEUE_TYPE_BASE`**
    - **Functionality**: Internal macro for base queue types.
