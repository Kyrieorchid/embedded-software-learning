#include "list.h"

void vListInitialiseItem(ListItem_t * const pxItem)
{
	pxItem->pvContainer = NULL;
}

void vListInitilise(List_t * pxList)
{
	pxList->pxIndex = (ListItem_t *)&(pxList->xListEnd);
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	pxList->xListEnd.pxNext = (ListItem_t *)&(pxList->xListEnd);
	pxList->xListEnd.pxPrevious = (ListItem_t *)&(pxList->xListEnd);
	pxList->uxNumberOfItems = (UBaseType_t)0U;
}

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem_t)
{
	/*As index pointer ususally point to the ending mini node, so this equals to insert new node before index node.*/
	ListItem_t * const pxIndex = pxList->pxIndex;
	
	pxNewListItem_t->pxNext = pxIndex;
	pxNewListItem_t->pxPrevious = pxIndex->pxPrevious;
	pxIndex->pxPrevious->pxNext = pxNewListItem_t;
	pxIndex->pxPrevious = pxNewListItem_t;
	
	pxNewListItem_t->pvContainer = pxList;
	(pxList->uxNumberOfItems)++;
}

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
	/*Insert new item with ItemValue ascending.*/
	ListItem_t * pxIterator;
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	
	/*Traversing to look for the insert position, at last pxIterator will point to the previos node of the new one.*/
	if(xValueOfInsertion == portMAX_DELAY)
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for(pxIterator = (ListItem_t *)(&pxList->xListEnd);
				pxIterator->pxNext->xItemValue <= xValueOfInsertion;
				pxIterator = pxIterator->pxNext)
		{
			/*Doing nothing, just for iterating*/
		}
	}
	
	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;
	
	pxNewListItem->pvContainer = (void *)pxList;
	(pxList->uxNumberOfItems)++;
}

UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove)
{
	List_t * const pxList = pxItemToRemove->pvContainer;
	
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	
	if(pxList->pxIndex == pxItemToRemove)
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}
	
	pxItemToRemove->pvContainer = NULL;

	return --(pxList->uxNumberOfItems);
}
