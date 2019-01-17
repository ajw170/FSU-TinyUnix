#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "header.h"
#include "global.h"
int g1 = 400;

void test(FPTR fn, Node *n) {
  fn(n);
  return;
}


int main(int argc, char *argv[]) {
  Node mynode;
  mynode.elem = 10;
#ifdef GOO
  test(goo, &mynode);
  test(goo, &mynode);
#else
  test(foo, &mynode);
  test(foo, &mynode);
#endif
  printf("Mynode elem = %d\n", mynode.elem);
  printf("g1 value = %d\n", g1);
  return 0;
} /* End of main. */
