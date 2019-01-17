#include <stdio.h>
#include "header.h"
#include "global.h"

void foo(Node *n ){
  printf("foo:g1 = %d\n", g1);
  n->elem = 100;
  return;
}

void goo(Node *n) {
  static int lg = 10;
  lg = lg*100;
  printf("goo:g1 = %d, lg = %d\n", g1, lg);
  n->elem = 200;
  return;
}
