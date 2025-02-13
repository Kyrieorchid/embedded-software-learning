
# FreeRTOS list.h 接口和宏定义

## **列表初始化**
1. **`void vListInitialise( List_t * const pxList );`**  
   **说明**：初始化一个列表。

2. **`void vListInitialiseItem( ListItem_t * const pxItem );`**  
   **说明**：初始化一个列表项。

## **列表操作**
3. **`void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );`**  
   **说明**：将一个列表项插入到指定列表中 (按升序排列)。

4. **`void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );`**  
   **说明**：将列表项插入到列表的末尾。

5. **`UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );`**  
   **说明**：从列表中移除一个列表项。

## **宏定义接口**
6. **`listSET_LIST_ITEM_OWNER( pxListItem, owner );`**  
   **说明**：设置列表项的所有者。

7. **`listGET_LIST_ITEM_OWNER( pxListItem );`**  
   **说明**：获取列表项的所有者。

8. **`listSET_LIST_ITEM_VALUE( pxListItem, xValue );`**  
   **说明**：设置列表项的值。

9. **`listGET_LIST_ITEM_VALUE( pxListItem );`**  
   **说明**：获取列表项的值。

10. **`listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList );`**  
    **说明**：获取列表中头项的值。

11. **`listGET_HEAD_ENTRY( pxList );`**  
    **说明**：获取列表的头项。

12. **`listGET_NEXT( pxListItem );`**  
    **说明**：获取当前列表项的下一个列表项。

13. **`listGET_END_MARKER( pxList );`**  
    **说明**：获取列表的结束标记。

14. **`listLIST_IS_EMPTY( pxList );`**  
    **说明**：检查列表是否为空。

15. **`listCURRENT_LIST_LENGTH( pxList );`**  
    **说明**：获取列表当前的长度。

16. **`listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList );`**  
    **说明**：获取列表中下一个项的所有者。

## **特殊操作**
17. **`UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );`**  
    **说明**：从列表中移除一个列表项，并返回当前列表长度。
