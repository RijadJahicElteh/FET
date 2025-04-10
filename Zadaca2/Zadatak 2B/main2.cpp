#include <iostream>
#include "bigint.hpp"

bigint fib(int n) {
  if(n<=1) return n;
  return fib(n-1)+fib(n-2);
}
int main() {
  int n = 50;
  bigint a;
  a = fib(50);
  std::cout<<a<<std::endl;
}
