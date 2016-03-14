/**
 * mallok
 * Gabriel Houle
 */

#include "mallok.h"
#include <stdio.h>

//prototypes
void scenarioOne();
void scenarioTwo();
void scenarioThree();
void scenarioFour();
void scenarioFive();

/**
 * Runs various test scenarios.
 */
int main() {
  
  scenarioOne();
  scenarioTwo();
  scenarioThree();
  scenarioFour();
  scenarioFive();

  return 0;
}//exit main

/**
 * This function will test how many times my_malloc will give me blocks
 * of 10 from heap size of 1000.
 */
void scenarioOne() {
  create_pool(1000);
  void *test = my_malloc(10);
  int count = 0;
  
  while (test) {
    test = my_malloc(10);
    count++;
  }

  printf("TEST 1\n");
  printf("How many times can I allocate 10 block chucks from\n");
  printf("heap size 1000? \n%d Times\n\n", count);
  free_pool();
}

/**
 * This function will test if blocks can be allocated and then freed
 * and then allocated again.
 */
void scenarioTwo() {
  create_pool(1000);
  int i;
  int j;
  void *one;
  void *two;
  void *three;
  void *four;
  void *five;

  printf("TEST 2\n");
  printf("This program will now allocate blocks of 200 five times\n");
  printf("on a heap of size 1000. Then the program will free\n");
  printf("the memory and will repeat this process five times.\n");
  for (i = 1; i < 6; i++) {
    one = my_malloc(200);
    two = my_malloc(200);
    three = my_malloc(200);
    four = my_malloc(200);
    five = my_malloc(200);

    my_free(one);
    my_free(two);
    my_free(three);
    my_free(four);
    my_free(five);

    if (one && two && three && four && five) {
      printf("Cycle %d working\n", i);
    }
  }
  free_pool();
  printf("Process Complete\n");
}

/**
 * This function will request blocks of 200 and then free one of them
 * and then continue to request varying sizes of blocks to test correct
 * functionality.
 */
void scenarioThree() {
  printf("\nTEST 3\n");
  create_pool(1000);
  void *one = my_malloc(200);
  void *two = my_malloc(200);
  void *three = my_malloc(200);
  void *four = my_malloc(200);
  void *five = my_malloc(200);
  void *six;

  printf("Now allocating five blocks of 200 from size 1000 heap\n");
  printf("Now freeing middle block of size 200, and then\n");
  printf("requesting a block of 210\n");
  my_free(three);
  three = my_malloc(210);
  if (!three) {
    printf("Still NULL! (Success)\n");
  }

  printf("Now requesting size 150 block (should work)\n");

  three = my_malloc(150);

  if (three) {
    printf("Success!\n");
  }

  printf("Now requesting size 60 block (should fail)\n");

  six = my_malloc(60);

  if (!six) {
    printf("Still NULL! (Success)\n");
  }

  printf("Now requesting size 50 block (should work)\n");

  six = my_malloc(50);

  if (six) {
    printf("Success!\n");
  }

  my_free(one);
  my_free(two);
  my_free(three);
  my_free(four);
  my_free(five);
  my_free(six);
  free_pool();
}

/**
 * This function will create five blocks of 200 and then fill the first
 * two blocks with 'A' and 'B'.
 */
void scenarioFour() {
  create_pool(1000);
  char *test[5];
  int success = 0;
  int i;

  printf("\nTEST 4\n");
  printf("Allocating five blocks of 200 and then filling the first\n");
  printf("block to contain 'A' and the second 'B'\n");

  for (i = 0; i < 5; i++) {
    test[i] = my_malloc(200);
  }

  for (i = 0; i < 200; i++) {
    *(test[0] + i) = 'A';
  }

  for (i = 0; i < 200; i++) {
    *(test[1] + i) = 'B';
  }

  for (i = 0; i < 200; i++) {
    if (!i && *(test[0] + i) == 'A') {
      success = 1;
    } else if (*(test[0] + i) == 'A') {
      success = success & success;
    } else {
      success = 0;
    }
  }
  if (success) {
    success = 0;
    printf("A allocated correctly.\n");
  }

  for (i = 0; i < 200; i++) {
    if (!i && *(test[1] + i) == 'B') {
      success = 1;
    } else if (*(test[1] + i) == 'B') {
      success = success & success;
    } else {
      success = 0;
    }
  }
  if (success) {
    success = 0;
    printf("B allocated correctly.\n");
  }

  for (i = 0; i < 5; i++) {
    my_free(test[i]);
  }
  free_pool();
}

/**
 * This function will request a block of 1000 and then free it.
 * Then requests 4 blocks of 250 and frees them.
 * Lastly, it will requests 10 blocks of size 100 and free them.
 */
void scenarioFive() {
  create_pool(1000);
  void *test[10];
  int success = 0;
  int i;

  printf("\nTEST 5\n");
  printf("Requesting block of size 1000 and then returning it.\n");
  test[0] = my_malloc(1000);
  if (test[0]) {
    success = 1;
  }
  my_free(test[0]);
  if (list->free && success) {
    printf("Success!\n");
    success = 0;
  }

  printf("Requesting 4 blocks of size 250 and then returning them.\n");
  for (i = 0; i < 4; i++) {
    test[i] = my_malloc(250);
  }
  if (test[0] && test[1] && test[2] && test[3]) {
    success = 1;
  }
  for (i = 0; i < 4; i++) {
    my_free(test[i]);
  }
  if (list->mySize == 1000 && list->free && success) {
    printf("Success!\n");
  }

  printf("Requesting 10 blocks of size 100 and then returning them.\n");

  for (i = 0; i < 10; i++) {
    test[i] = my_malloc(100);
  }
  for (i = 0; i < 10; i++) {
    if (!i && test[i]) {
      success = 1;
    } else if (test[i]) {
      success = success & success;
    } else {
      success = 0;
    }
  }
  for (i = 0; i < 10; i++) {
    my_free(test[i]);
  }
  if (list->mySize == 1000 && list->free && success) {
    printf("Success!\n");
  }
  free_pool();
}