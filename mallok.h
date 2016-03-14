/**
 * mallok
 * Gabriel Houle
 */

#include <stdio.h>
#include <stdlib.h>

struct blockTag {
  void *myLoc;
  int mySize;
  int free;
  struct blockTag *next;
};

typedef struct blockTag Block;

void create_pool(int);
void *my_malloc(int);
void my_free(void *);
void free_pool();
void printBlock(Block *);
void printList(Block *);
void freeList(Block *);

#ifndef MK
#define MK
#include "mallok.c"
#endif