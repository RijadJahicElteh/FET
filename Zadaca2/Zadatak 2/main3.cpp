#include <iostream>
#include "bigint.hpp"

int main() {
  bigint a(30);
  for(int i=29;i>1;--i) {
    a = a*i;
  }
  std::cout<<"30! je: "<<a<<std::endl;
}
