#ifndef __HEAP_H__
#define __HEAP_H__
/** 
 * @brief Built a Binary Heap container data type 
 * 
 * @author Author Ben Velt (ben.velt@gmail.com)
 */ 

#include "vector.h"
#include "ADTDefs.h"		/* ADTErr */

typedef struct Heap Heap;

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Build ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief build a new Heap 
 * @param[in] _heap - 
 * @return Heap* - on success / NULL on fail. The Heap will be sorted by MAX ORDER. 
 *
 * @warning if _vec not exist will return NULL.
 * @warning if allocation of Heap failed will return NULL.
 */
Heap* HeapBuild(Vector* _vec);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Destroy ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Deallocate a previously allocated _heap.
 * @param[in] _heap - Heap to be deallocated.
 * @return void
 */
void HeapDestroy(Heap* _heap);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Insert ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapInsert(Heap* _heap, int _data);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Max ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapMax(Heap* _heap, int* _data);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Extract Max ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/*~~~~~~~~~~~~~~~~~~~ Heap Items Number ~~~~~~~~~~~~~~~~~~~~~~*/
int HeapItemsNum(Heap* _heap);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Print ~~~~~~~~~~~~~~~~~~~~~~*/
void HeapPrint(Heap* _heap);


#endif /*__HEAP_H__*/
