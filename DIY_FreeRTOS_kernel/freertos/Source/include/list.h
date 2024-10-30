#ifndef LIST_H
#define LIST_H
/*Bidirectional circular linked list*/
#include "FreeRTOS.h"

#define listSET_LIST_ITEM_OWNER(pxListItem, pxOwner) \
				((pxListItem)->pvOwner = (void *)(pxOwner))
					
#define listGET_LIST_ITEM_OWNER(pxListItem) \
				((pxListItem)->pvOwner)

#define listSET_LIST_ITEM_VALUE(pxListItem, xValue) \
				((pxListItem)->xItemValue = xValue)

#define listGET_LIST_ITEM_VALUE( pxListItem ) \
				(( pxListItem )->xItemValue)

#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList) \
				(((pxList)->xListEnd).pxNext->xItemValue)
				
#define listGET_OWNER_OF_HEAD_ENTRY(pxList) \
				((pxList)->xListEnd.pxNext->pvOwner)
				
#define listLIST_IS_EMPTY(pxList) \
					(UBaseType_t)((pxList)->uxNumberOfItems == (UBaseType_t)0)
				
#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList) \
				{ \
					List_t * const pxConstList = (pxList); \
					pxConstList->pxIndex = pxConstList->pxIndex->pxNext; \
					/*Skip end_item, but it's meaningless when pxList is empty.*/ \
					if((void *)pxConstList->pxIndex == (void *)&(pxConstList->xListEnd)) \
					{ \
						pxConstList->pxIndex = pxConstList->pxIndex->pxNext; \
					} \
					(pxTCB) = pxConstList->pxIndex->pvOwner; \
				}
				
#define listCURRENT_LIST_LENGTH(pxList) \
				((pxList)->uxNumberOfItems)
/*To be continued...*/
				
typedef struct xLIST_ITEM
{
	TickType_t xItemValue; //Help sort nodes.
	struct xLIST_ITEM * pxNext;
	struct xLIST_ITEM * pxPrevious;
	void * pvOwner; //Point to a each-to-each kernel OBJ who owns this node, ususally TCB.
	void * pvContainer; //Point to the list that contains this node.
}ListItem_t;

typedef struct xMINI_LIST_ITEM
{
	TickType_t xItemValue; //Help sort nodes.
	struct xLIST_ITEM * pxNext;
	struct xLIST_ITEM * pxPrevious;
}MiniListItem_t;

typedef struct xLIST
{
	UBaseType_t uxNumberOfItems;
	ListItem_t * pxIndex; //Index pointer which usually points to THE END MINI NODE of a list.
	MiniListItem_t xListEnd;
}List_t;

void vListInitialiseItem(ListItem_t * const pxItem);
void vListInitilise(List_t * pxList);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem_t);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem_t);
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif /*LIST_H*/
