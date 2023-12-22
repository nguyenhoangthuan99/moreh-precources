#include "vector.h"

namespace getp {

template <typename T>
vector<T>::vector() {
  // TODO : FILL IN HERE
  this->data_ = new T[1];
  this->size = 0;
  this->capacity = 1;
}

template <typename T> vector<T>::~vector() { 
  // TODO : FILL IN HERE
  delete [] this->data_;
  this->size = 0;
  this->capacity = 1;
}

template <typename T>
vector<T>::vector(const vector &other) {
  // TODO : FILL IN HERE
  new (this) vector();
  this->size = other.getSize();
  this->capacity = other.getCapacity();
  this->data_ = new T[this->capacity];
  for(auto it = other.cbegin(); it != other.cend() ; it++){
    this->push_back(*it);
  }
  // for(unsigned int i=0;i<this->size;i++){
  //   this->data_[i] = other.at(i);
  // }
}

template <typename T>
vector<T>::vector(vector &&other) noexcept { 
  // TODO : FILL IN HERE
  new (this) vector();
  this->size = other.getSize();
  this->capacity = other.getCapacity();
  this->data_ = new T[this->capacity];
  for(auto it = other.cbegin(); it != other.cend() ; it++){
    this->push_back(*it);
  }
  // for(unsigned int i=0;i<this->size;i++){
  //   this->data_[i] = other.at(i);
  // }
}

template <typename T> vector<T> &vector<T>::operator=(const vector &other) {
  // TODO : FILL IN HERE
  delete [] this->data_;
  this->size = other.getSize();
  this->capacity = other.getCapacity();
  this->data_ = new T[this->capacity];
  for(auto it = other.cbegin(); it != other.cend() ; it++){
    this->push_back(*it);
  }
  // for(unsigned int i=0;i<this->size;i++){
  //   this->data_[i] = other.at(i);
  // }

  return *this;
}

template <typename T> vector<T> &vector<T>::operator=(vector &&other) noexcept {
  // TODO : FILL IN HERE
  delete [] this->data_;
  this->size = other.getSize();
  this->capacity = other.getCapacity();
  this->data_ = new T[this->capacity];
  for(auto it = other.cbegin(); it != other.cend() ; it++){
    this->push_back(*it);
  }
  // for(unsigned int i=0;i<this->size;i++){
  //   this->push_back(other[i]);
  // }

  return *this;
}

template <typename T> T &vector<T>::at(size_t index) {
  // TODO : FILL IN HERE
    if(index>= this->size){
      throw std::out_of_range( "Index out of range" );
    }
    return this->data_[index];

}

template <typename T> T &vector<T>::operator[](size_t index) {
  // TODO : FILL IN HERE
  return this->at(index);
}

template <typename T> T &vector<T>::front() {
  // TODO : FILL IN HERE
    return this->data_[0];
}

template <typename T> T &vector<T>::back() {
  // TODO : FILL IN HERE
    return this->data_[this->size-1];
}

template <typename T> T *vector<T>::data() {
  // TODO : FILL IN HERE
  return this->data_;
}

template <typename T> size_t vector<T>::getSize() const {
  // TODO : FILL IN HERE
  return this->size;
}

template <typename T> size_t vector<T>::getCapacity() const {
  // TODO : FILL IN HERE
  return this->capacity;
}

template <typename T> void vector<T>::push_back(const T &value) {
  // TODO : FILL IN HERE
  if (this->size == this->capacity){
    
    T* temp = new T[2*this->capacity];
    for (size_t i = 0; i < this->capacity; i++) {
                temp[i] = this->data_[i];
            }
    temp[this->capacity] = value;
    this->size += 1;
    this->capacity *=2;
    delete [] this->data_;
    this->data_ = temp;

  }
  else{
    this->data_[this->size] = value;
    this->size++;
  }
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&... args) {
  // TODO : FILL IN HERE
  this->push_back(T(std::forward<Args>(args)...));
}

template <typename T>
template <typename InputIt>
void vector<T>::append_range(InputIt first, InputIt last) {
  // TODO : FILL IN HERE
  for(InputIt it=first;it!=last;it++){
    this->push_back(*it);
  }

}

template <typename T> void vector<T>::pop_back() {
  // TODO : FILL IN HERE
  this->size = this->size > 0 ? this->size -1 : 0;
}

template <typename T> void vector<T>::reserve(size_t newCapacity) {
  // TODO : FILL IN HERE
  if (this->size==0){
    this->capacity = 0;
  }
  T* temp = new T[newCapacity];
  unsigned int temp_size = newCapacity<this->size ? newCapacity : this->size;
  for (unsigned int i=0;i<temp_size;i++){
    temp[i] = this->data_[i];
  }
  this->capacity = newCapacity;
  delete [] this->data_;
  this->data_ = temp;
  this->size = temp_size;
}

template <typename T> T *vector<T>::begin() {
  // TODO : FILL IN HERE
  return this->data_;
}

template <typename T> const T *vector<T>::cbegin() const {
  // TODO : FILL IN HERE
  const T* temp = this->data_;
  return temp;
}

template <typename T> T *vector<T>::end() {
  // TODO : FILL IN HERE
  return this->data_ + this->size;
}

template <typename T> const T *vector<T>::cend() const {
  // TODO : FILL IN HERE
  const T* temp = this->data_ + this->size;
  return temp;
}

template <typename T> std::reverse_iterator<T *> vector<T>::rbegin() {
  // TODO : FILL IN HERE
  

  return std::reverse_iterator<T *> (this->end());
}

template <typename T>
std::reverse_iterator<const T *> vector<T>::crbegin() const {
  // TODO : FILL IN HERE
  std::reverse_iterator<const T *> temp = std::reverse_iterator<const T *> (this->cend());
  return temp;
}

template <typename T> std::reverse_iterator<T *> vector<T>::rend() {
  // TODO : FILL IN HERE
  return std::reverse_iterator<T *> (this->begin());
}

template <typename T>
std::reverse_iterator<const T *> vector<T>::crend() const {
  // TODO : FILL IN HERE
  std::reverse_iterator<const T *> temp = std::reverse_iterator<const T *> (this->cbegin());
  return temp;
}

// Explicit instantiation for supported types
template class vector<int>;
template void getp::vector<int>::emplace_back<int>(int &&);

} // namespace getp
