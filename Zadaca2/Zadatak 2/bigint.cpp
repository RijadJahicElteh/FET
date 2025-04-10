#include "bigint.hpp"

bigint operator+(const bigint& a, const bigint& b) {
  if(a.negative && !b.negative) return b - (-a);
  if(!a.negative && b.negative) return a - (-b);
  bigint rezultat;
  rezultat.negative = a.negative;
  int carry = 0;
  int max_size = std::max(a.cifre.size(), b.cifre.size());

  for(int i=0;i<max_size || carry; ++i) {
    int cifraA = (i<a.cifre.size()) ? a.cifre[i] : 0;
    int cifraB = (i<b.cifre.size()) ? b.cifre[i] : 0;
    int suma = cifraA+cifraB+carry;
    rezultat.cifre.push_back(suma%10);
    carry = suma/10;
  }
  return rezultat;

}
bigint operator-(const bigint& a) {
  bigint rezultat;
  for(int i=0;i<a.cifre.size();++i)
    rezultat.cifre.push_back(a.cifre[i]);
  if(!(a.cifre.size() == 1 && a.cifre[0] == 0)) {
      rezultat.negative = !a.negative;
  }
  return rezultat;
}
bigint operator-(const bigint& a, const bigint& b) {
  if(a.negative && b.negative) return (-b) - (-a);
  if(a.negative) return -(-a+b);
  if(b.negative) return a+(-b);

  if(a<b) return -(b-a);

  bigint rezultat;
  rezultat.cifre.resize(a.cifre.size());

  int carry = 0;
  for(int i=0;i<a.cifre.size();++i) {
    int cifraA = a.cifre[i];
    int cifraB = (i<b.cifre.size()) ? b.cifre[i] : 0;
    int razlika = cifraA-cifraB-carry;
    if(razlika<0) {
      razlika+=10;
      carry = 1;
    } else {
      carry = 0;
    }
    rezultat.cifre[i] = razlika;
  }
  while(rezultat.cifre.size() > 1 && rezultat.cifre.back() == 0) {
    rezultat.cifre.pop_back();
  }
  return rezultat;

}
bool operator==(const bigint& a, const bigint& b) {
  if(a.negative != b.negative) return false;
  if(a.cifre.size() != b.cifre.size()) return false;
  for(int i=0;i<a.cifre.size();++i) {
    if(a.cifre[i] != b.cifre[i]) return false;
  }
  return true;
}
bool operator<(const bigint& a, const bigint& b) {
  if (a.negative != b.negative) return a.negative;
  if(a.cifre.size() != b.cifre.size()) 
    return (a.cifre.size() < b.cifre.size()) ^ a.negative;
  for(int i=a.cifre.size() -1; i>=0; --i) {
    if(a.cifre[i] != b.cifre[i])
      return (a.cifre[i] < b.cifre[i]) ^ a.negative;
  }
  return false;
}
bool operator<=(const bigint& a, const bigint& b) {
  if (a==b) return true;
  return a<b;
}
bool operator>(const bigint& a, const bigint& b) {
  if(a<=b) return false;
  return true;
}
bool operator>=(const bigint& a, const bigint& b) {
  if(a<b) return false;
  return true;
}
bigint operator*(const bigint& a, const bigint& b) {
  bigint rezultat;
  rezultat.cifre.resize(a.cifre.size() + b.cifre.size(), 0);
  for(int i=0; i< a.cifre.size(); ++i) {
    int carry = 0;
    for(int j = 0; j<b.cifre.size() || carry; ++j) {
      int proizvod = a.cifre[i] * (j<b.cifre.size() ? b.cifre[j] : 0) + rezultat.cifre[i+j] + carry;
      rezultat.cifre[i+j] = proizvod%10;
      carry=proizvod/10;
    }
  }
  while(rezultat.cifre.size() > 1 && rezultat.cifre.back() == 0) {
    rezultat.cifre.pop_back();
  }
  rezultat.negative = a.negative ^ b.negative;
  return rezultat;
}
bigint operator/(const bigint& a, const bigint& b) {
  if(b.cifre[0] == '0') throw std::runtime_error("Dijeljenje nulom!");

  bigint rezultat, ostatak;
  rezultat.negative = a.negative ^ b.negative;
  rezultat.cifre.resize(a.cifre.size());

  bigint djelilac = b;
  djelilac.negative = false;

  for(int i = a.cifre.size() - 1; i>=0; --i) {
    ostatak = ostatak * 10 + a.cifre[i];
    int cifra = 0;
    while(ostatak >= djelilac) {
      ostatak = ostatak - djelilac;
      cifra++;
    }
    rezultat.cifre[i] = cifra;
  }
    while(rezultat.cifre.size() > 1 && rezultat.cifre.back() == 0) {
      rezultat.cifre.pop_back();
    }
    return rezultat;
}
bigint operator%(const bigint& a, const bigint& b) {
  bigint ostatak("0");
  bigint trenutni("0");
  for(int i=a.cifre.size() -1; i>=0; --i) {
    trenutni.cifre.insert(trenutni.cifre.begin(), a.cifre[i]);
    while(!trenutni.cifre.empty() && trenutni.cifre.back() == 0) {
      trenutni.cifre.pop_back();
    }
    int cifra_kolicnika = 0;
    while(trenutni>=b) {
      trenutni = trenutni - b;
      cifra_kolicnika++;
    }
  }
  return trenutni;
}
bool operator!=(const bigint&a, const bigint& b) {
  return !(a==b);
}
std::ostream& operator<<(std::ostream& out, const bigint& a) {
  if(a.negative) out<<'-';
  if(a.cifre.empty()) out<<'0';
  else {
    for(int i=a.cifre.size()-1; i>=0; --i) {
      out<<a.cifre[i];
    }
  }
  return out;
}
std::istream& operator>>(std::istream& in, bigint& a) {
  std::string s;
  in >> s;
  a.cifre.clear();
  a.negative = false;
  int start = 0;
  if(s[0] == '-') {
    a.negative = true;
    start = 1;
  }
  for(int i=s.size() -1; i>=start; --i)
    a.cifre.push_back(s[i]-'0');
  return in;
}
