
#include <cstdio>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

template<typename T>
class MojVektor {
  private:
    T* elementi;
    size_t capacity_;
    size_t size_;
  public:
    size_t size() const {
      return size_;
    }
    bool empty() const {
      if (size_ == 0) return true;
      return false;
    }
    size_t capacity() const {
      return capacity_;
    }
    MojVektor();
    MojVektor(const std::initializer_list<T>&);
    MojVektor(const MojVektor&);
    MojVektor& operator=(const MojVektor&);
    MojVektor(MojVektor&&);
    MojVektor& operator=(MojVektor&&);
    ~MojVektor();
    void operator delete(void*);

    MojVektor& push_back(const T&);
    MojVektor& push_back(T&&);
    MojVektor& push_front(const T&);
    MojVektor& push_front(T&&);
    MojVektor& pop_back();
    MojVektor& pop_front();

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;

    T& at(size_t);
    const T& at(size_t) const;
    T& operator[](size_t);
    const T& operator[](size_t) const;

    bool operator==(const MojVektor&) const;
    bool operator!=(const MojVektor&) const;
    bool full() const;
    
    void clear();
    void resize(size_t, const T&);
    void rotate();

    template<typename Fn>
    void for_each(Fn fn);
    template<typename Pred>
    void remove_if(Pred pred);

    class Iterator {
      public:
        Iterator(T* ptr) : current(ptr) {}

        T& operator*() { return *current; }
        T* operator->() { return current; }
        Iterator& operator++() { ++current; return *this; }
        Iterator& operator--() {
          --current;
          return *this;
        }
        Iterator operator--(int) {
          Iterator temp = *this;
          --current;
          return temp;
        }
        Iterator operator+(size_t n) {
          Iterator temp = *this;
          temp.current += n;
          return temp;
        }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        
      private:
        T* current;
    };
    Iterator begin() const;
    Iterator end() const;
    Iterator find(const T&) const;
    Iterator erase(Iterator);
    Iterator erase(Iterator, Iterator);
    Iterator insert(Iterator, const T&);
    
};
template<typename T>
MojVektor<T>::MojVektor() : capacity_(10), size_(0) {
  elementi = new T[capacity_];
}
template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& lista) : capacity_(lista.size() * 2),
  size_(lista.size()) {
    elementi = new T[capacity_];
    std::copy(lista.begin(), lista.end(), elementi);
}
template<typename T>
MojVektor<T>::~MojVektor() {
  delete[] elementi;
  elementi = nullptr;
}
template<typename T>
MojVektor<T>::MojVektor(const MojVektor& drugi) : capacity_(drugi.capacity_), size_(drugi.size_) {
  elementi = new T[capacity_];
  std::copy(drugi.elementi, drugi.elementi + size_, elementi);
}
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& drugi) {
  if (this != &drugi) {
    delete[] elementi;
    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    elementi = new T[capacity_];
    std::copy(drugi.elementi, drugi.elementi + size_, elementi);
  }
  return *this;
}
template<typename T>
MojVektor<T>::MojVektor(MojVektor&& drugi) : elementi(drugi.elementi),
                              capacity_(drugi.capacity_), size_(drugi.size) {
  drugi.elementi = nullptr;
  drugi.capacity_ = 0;
  drugi.size_ = 0;
}
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& drugi) {
  if(this!=&drugi) {
    delete[] elementi;
    elementi = drugi.elementi;
    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    drugi.elementi = nullptr;
    drugi.capacity_ = 0;
    drugi.size_ = 0;
  }
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    T* noviElementi = new T[capacity_];
    std::copy(elementi, elementi + size_, noviElementi);
    delete[] elementi;
    elementi = noviElementi;
  }
  elementi[size_++] = element;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element) {
  if(size_ == capacity_) {
    capacity_ *= 2;
    T* noviElementi = new T[capacity_];
    std::move(elementi, elementi + size_, noviElementi);
    delete[] elementi;
    elementi = noviElementi;
  }
  elementi[size_++] = std::move(element);
  return *this;
}
template<typename T>
T& MojVektor<T>::at(size_t index) {
  if(index >= size_) 
    throw std::out_of_range("Indeks je van granica.");
  return elementi[index];
}
template<typename T>
const T& MojVektor<T>::at(size_t index) const {
  if(index >= size_) 
    throw std::out_of_range("Indeks je van granica.");
  return elementi[index];
}
template<typename T>
T& MojVektor<T>::operator[](size_t index) {
  return elementi[index];
}
template<typename T>
const T& MojVektor<T>::operator[](size_t index) const {
  return elementi[index];
}
template<typename T>
void MojVektor<T>::clear() {
  size_ = 0;
}
template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& value) {
  if(newSize < size_) {
    size_ = newSize;
  }
  else if (newSize > size_) {
    if (newSize > capacity_) capacity_ *= 2;
    for(int i=size_; i<newSize; ++i) {
      elementi[i] = value;
    }
    size_ = newSize;
  }
}
template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if(size_ == 0) throw std::out_of_range("Kontejner je prazan");
  size_--;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
  if(size_ == 0) throw std::out_of_range("Kontejner je prazan");
  ++elementi;
  --size_;
  return *this;
}
template<typename T>
T& MojVektor<T>::front() {
  if (size_ == 0) throw std::out_of_range("Kontejner je prazan");
  return elementi[0];
}
template<typename T>
T& MojVektor<T>::back() {
  if(size_ == 0) throw std::out_of_range("Kontejner je prazan");
  return elementi[size_-1];
}
template<typename T>
const T& MojVektor<T>::front() const {
  if (size_ == 0) throw std::out_of_range("Kontejner je prazan");
  return elementi[0];
}
template<typename T>
const T& MojVektor<T>::back() const {
  if(size_ == 0) throw std::out_of_range("Kontejner je prazan");
  return elementi[size_-1];
}
template<typename T>
bool MojVektor<T>::operator==(const MojVektor& drugi) const { // Nije potrebno porediti capacity_. Interesuju nas samo elementi koji idu do size_.
  if (size_ != drugi.size_) return false;
  for (int i=0; i<size_; ++i) {
    if (elementi[i] != drugi.elementi[i]) return false;
  }
  return true;
}
template<typename T>
bool MojVektor<T>::operator!=(const MojVektor& drugi) const {
  return !(*this == drugi);
}
template<typename T>
bool MojVektor<T>::full() const {
  if(size_ == capacity_) return true;
  return false;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const {
  return Iterator(elementi);
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const {
  return Iterator(elementi + size_);
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const {
  for(Iterator it = begin(); it != end(); ++it) {
    if (*it == value) {
      return it;
    }
  }
  return end();
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos) {
  if (pos == end()) {
    return end();
  }
  Iterator it = pos;
  for(Iterator next = it; ++next != end(); ++it) {
    *it = *next;
  }
  --size_;
  return it;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
  if (beginIt == endIt) {
    return beginIt;
  }
  Iterator it = beginIt;
  for(Iterator next = endIt; next != end(); ++next, ++it) {
    *it = *next;
  }
  size_ -= std::distance(beginIt, endIt);
  return it;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& value) {
  if(size_ == capacity_) {
    capacity_ *= 2;
  }
  Iterator it = end();
  while (it != pos) {
    --it;
    *(it+1) = *it;
  }
  *pos = value;
  ++size_;
  return pos;
}
template<typename T>
void MojVektor<T>::rotate() {
  if (size_ <= 1) return;
  T last = std::move(elementi[size_-1]);
  for(int i = size_-1; i>0; --i) {
    elementi[i] = std::move(elementi[i-1]);
  }
  elementi[0] = std::move(last);
}
template<typename T>
template<typename Fn> 
void MojVektor<T>::for_each(Fn fn) {
  for (int i=0;i < size_; ++i) {
    fn(elementi[i]);
  }
}
template<typename T>
template<typename Pred>
void MojVektor<T>::remove_if(Pred pred) {
  size_t new_size = 0;
  for (int i=0;i<size_;++i) {
    if(!pred(elementi[i])) {
      elementi[new_size++] = std::move(elementi[i]);
    }
  }
  size_ = new_size;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& value) {
  if(size_ == capacity_) {
    capacity_ *= 2;
  }
  for (int i=size_;i > 0; --i) {
    elementi[i] = elementi[i-1];
  }
  elementi[0] = value;
  ++size_;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& value) {
  if(size_ == capacity_) {
    capacity_ *= 2;
  }
  for(int i=size_; i>0; --i) {
    elementi[i] = std::move(elementi[i-1]);
  }
  elementi[0] = std::move(value);
  ++size_;
  return *this;
}
template<typename T>
void MojVektor<T>::operator delete(void *p) {
  ~MojVektor(); 
}
