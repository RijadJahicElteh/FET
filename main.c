#include <stdio.h>

extern double foo(int, double);

int main() {
  double r = foo(5,7.41);
  printf("%f\n", r);
  return 0;
}
