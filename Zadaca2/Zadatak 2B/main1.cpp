#include <iostream>
#include "bigint.hpp"

int main() {
  bigint a;
  bigint b;
  std::cout<<"Unesi broj a: ";
  std::cin>>a;
  std::cout<<"Unesi broj b: ";
  std::cin>>b;

  std::cout<<"Zbir: "<<a+b<<std::endl;
  std::cout<<"Razlika: "<<a-b<<std::endl;
  std::cout<<"Proizvod: "<<a*b<<std::endl;
  std::cout<<"Kolicnik: "<<a/b<<std::endl;
  std::cout<<"Ostatak pri dijeljenju: "<<a%b<<std::endl;
}
