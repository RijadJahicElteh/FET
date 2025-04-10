#include <iostream>
#include "bigint.hpp"

int main() {
  std::cout<<"Ovdje sam 1\n";
  bigint a(30);
  std::cout<<"Ovdje sam 2\n";
  for(int i=29;i>1;--i) {
    std::cout<<"Ovdje sam 3\n";
    a = a*i;
  }
  std::cout<<"30! je: "<<a<<std::endl;
}
