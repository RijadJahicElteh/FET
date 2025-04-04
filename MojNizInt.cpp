#include <iostream>
#include <initializer_list>
#include <stdexcept>

struct MojNizInt {
	int *pocetak = nullptr;
	int size_ = 0;
	public:
		MojNizInt() = default;
		MojNizInt(int a,int b){
			pocetak = new int[2];
			pocetak[0] = a;
			pocetak[1] = b;
			size_ = 2;
		}
		MojNizInt(std::initializer_list<int> lista) {
			size_ = lista.size();
			pocetak = new int[size_];
			int i=0;
			for(int elem:lista) {
				pocetak[i++] = elem;
			}
		}
		MojNizInt& operator=(const MojNizInt& o) {
			std::cout<<"Pozvan copy operator."<<std::endl;
			if(this != &o) delete[] pocetak;
			size_ = o.size_;
			pocetak = new int[size_];
			for(int i=0;i<size_;i++)
				pocetak[i] = o.pocetak[i];
			return *this;
		}
		MojNizInt& operator=(MojNizInt&& o) {
			std::cout<<"Pozvan move operator."<<std::endl;
			if(this != &o) delete[] pocetak;
			pocetak = o.pocetak;
			size_ = o.size_;
			o.pocetak = nullptr;
			o.size_ = 0;
			return *this;
		}
		MojNizInt(const MojNizInt& o) {
			size_ = o.size_;
			pocetak = new int[size_];
			for(int i=0;i<size_;i++)
				pocetak[i] = o.pocetak[i];
		} 
		MojNizInt(MojNizInt&& o) {
			std::cout<<"Pozvan move."<<std::endl;
			pocetak = o.pocetak;
			size_ = o.size_;
			o.pocetak = nullptr;
			o.size_ = 0;
		}
		int& operator[](int indeks) {
			return *(this->pocetak+indeks);
		} 
		MojNizInt operator*(int skalar) {
			std::cout<<"Pozvan skalar"<<std::endl;
			MojNizInt rezultat;
			rezultat.size_ = this->size_;
			rezultat.pocetak = new int[size_];
			for(int i=0;i<this->size_;++i)
				rezultat.pocetak[i] = this->pocetak[i]*skalar;
			return rezultat;
		}
		MojNizInt operator+(MojNizInt &drugi) {
			std::cout<<"Pozvan operator+"<<std::endl;
			MojNizInt rezultat;
			rezultat.size_ = this->size_;
			rezultat.pocetak = new int[rezultat.size_];
			if(rezultat.size_ != drugi.size_) throw 2;
			for(int i=0;i<this->size_;i++) {
				rezultat.pocetak[i] = this->pocetak[i] + drugi.pocetak[i];
			}
			return rezultat;
		}
		MojNizInt operator++(int) {
			std::cout<<"Pozvan sufix++"<<std::endl;
			MojNizInt temp(*this);
			for(int i=0;i<size_;i++) {
				pocetak[i]++;
			}
			return temp;
		}
		~MojNizInt() {
			std::cout<<"DESTRUTKR HAHAHAHA."<<std::endl;
			delete[] pocetak;
		}
		int size() {
			return size_;
		}
		int &at(int indeks) {
			if(indeks<0 || indeks >=size_) throw "Ne moze.";
			return *(this->pocetak+indeks);
		}
};

std::ostream& operator<<(std::ostream& stream, MojNizInt& niz) {
	for(int i=0;i<niz.size();i++) {
		stream << niz.pocetak[i];
	}
	return stream;
}

int main() {
	MojNizInt mojniz{2,3,4,5};
	mojniz++;
	std::cout<<mojniz<<std::endl;
	
}