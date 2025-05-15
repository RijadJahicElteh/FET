#include <stdio.h>

extern void foo(float*);

int main() {
  float p = 10.2;
  foo(&p);
  printf("p=%f\n",p);
  return 0;
}
