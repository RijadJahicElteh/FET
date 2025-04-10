#include <vector>
#include <string>
#include <iostream>
#include "MojVektor.hpp"

class bigint {
  private:
    MojVektor<int> cifre;
    bool negative;
  public:
    bigint() : negative{false} {}
    bigint(long int n) {
      if(n<0) {
        negative = true;
        n = -n;
      }
      do {
        cifre.push_back(n%10);
        n /= 10;
      } while(n>0);
    }
    bigint(const std::string& n) {
      int i=0;
      if(n[0] == '-') {
        negative = true;
        i = 1;
      }
      else negative = false;
      for(int j = n.size(); j>i; --j) {
        cifre.push_back(n[j-1] - '0');
      }
    }
    ~bigint() {
      delete cifre;
    }
    bigint(const char* n) : bigint(std::string(n)) {}
    friend bigint operator-(const bigint&);
    friend bigint operator+(const bigint&, const bigint&);
    friend bigint operator-(const bigint&, const bigint&);
    friend bigint operator*(const bigint&, const bigint&);
    friend bigint operator/(const bigint&, const bigint&);
    friend bigint operator%(const bigint&, const bigint&);
    friend std::ostream& operator<<(std::ostream&, const bigint&);
    friend std::istream& operator>>(std::istream&, bigint&);
    friend bool operator<(const bigint&, const bigint&); 
    friend bool operator<=(const bigint&, const bigint&); 
    friend bool operator==(const bigint&, const bigint&);
    friend bool operator>(const bigint&, const bigint&); 
    friend bool operator!=(const bigint&, const bigint&);
    friend bool operator>=(const bigint&, const bigint&);


};

