/**
 * mallok
 * Gabriel Houle
 */

#ifndef MK
#define MK
#include "mallok.h"
#endif

//Static global variables
static void *heap;
static Block *list;

/**
 * This function will create a simulated heap of the given size.
 */
void create_pool(int size) {
  heap = malloc(size);
  list = malloc(sizeof(Block));
  list->myLoc = heap;
  list->mySize = size;
  list->next = NULL;
  list->free = 1;
}

/**
 * This function will return a void pointer to a location in the
 * simualted heap. If the given size is not free then returns NULL.
 */
void *my_malloc(int size) {
  Block *temp = list;
  Block *newBlock = NULL;
  
  while (temp && (!temp->free || temp->mySize < size)) {
    temp = temp->next;
  }
  
  if (temp && temp->free && temp->mySize >= size) {
    
    newBlock = malloc(sizeof(Block));

    newBlock->mySize = temp->mySize - size;
    newBlock->free = 1;
    newBlock->myLoc = temp->myLoc + size;
    newBlock->next = temp->next;
    temp->free = 0;
    temp->mySize = size;
    if (newBlock->mySize > 0) {
      temp->next = newBlock;
    } else {
      free(newBlock);
    }
  }
  return newBlock == NULL ? NULL : temp->myLoc;
}

/**
 * Frees the given pointer giving the memory back to the heap.
 */
void my_free(void *block) {
  Block *scanner = list;
  Block *back = NULL;
  Block *next = NULL;

  while (scanner != NULL && scanner->myLoc != block) {
    back = scanner;
    scanner = scanner->next;
  }
  
  if (scanner != NULL) {
    if (scanner->next != NULL) {
      next = scanner->next;
      if (next->free) {
        scanner->mySize = scanner->mySize + next->mySize;
        scanner->next = next->next;
        free(next);
        next = NULL;
      }
    }
    if (back && back->free) {
      back->mySize = back->mySize + scanner->mySize;
      back->next = scanner->next;
      free(scanner);
      scanner = NULL;
    }
    if (scanner != NULL) {
      scanner->free = 1;
    }
  }
}

/**
 * Frees all memory from heap.
 */
void free_pool() {
  freeList(list);
  free(heap);
  heap = NULL;
  list = NULL;
}

/**
 * This function will print a single block.
 * Used for testing.
 */
void printBlock(Block *theBlock) {
  if (theBlock) {
    printf("Size: %d, free: %d, Loc: %X, ",
            theBlock->mySize, theBlock->free, theBlock->myLoc);
  }
}
 
/**
 * This function will print the linked list of memory blocks.
 * Used for testing.
 */
void printList(Block *theBlock) {
  if (theBlock) {
    printBlock(theBlock);
    printList(theBlock->next);
  } else {
    printf("\n");
  }
}

/**
 * Frees the linked list.
 * Not sure if this function is neccessary.
 */
void freeList(Block *theList) {
  if (theList) {
    freeList(theList->next);
    free(theList);
  }
}