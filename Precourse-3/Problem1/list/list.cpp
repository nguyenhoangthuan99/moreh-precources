#include "list.h"

// Explicit instantiation
template class getp::list<int>;
template class getp::list<float>;
template class getp::list<double>;

namespace getp {

// Node implementation
template <class T>
list<T>::Node::Node(const T &value) {
  // TODO : FILL IN HERE
  data = value;
  next = nullptr;
  prev = nullptr;
}

// iterator implementation
template <class T> list<T>::iterator::iterator(Node *node) {
  // TODO : FILL IN HERE
  this->current = node;
}

template <class T> T &list<T>::iterator::operator*() const {
  // TODO : FILL IN HERE
  return this->current->data;
}

template <class T> typename list<T>::iterator &list<T>::iterator::operator++() {
  // TODO : FILL IN HERE
  current = current->next;
  return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
  // TODO : FILL IN HERE
  // current = current->next;
  auto temp = iterator (current);
  current = current->next;
  return temp;
   //
  
}

template <class T>
bool list<T>::iterator::operator!=(const iterator &other) const {
  // TODO : FILL IN HERE
  return this->current != other.current;
}

// Rest of the list class implementation
template <class T> list<T>::list(){
  // TODO : FILL IN HERE
  this->head = nullptr;
  this->tail = nullptr;
  this->size_ = 0;
}

template <class T>
list<T>::list(const list &other) {
  // TODO : FILL IN HERE
  new (this) list();
  this->size_ = 0;
  for(iterator it = other.cbegin(); it != other.cend() ; ++it){
    this->push_back(*it);
  }
}

template <class T>
list<T>::list(std::initializer_list<T> initList){
  // TODO : FILL IN HERE
  this->size_ = 0;
  new (this) list();
  for (auto it = initList.begin();it!=initList.end(); ++it){
    this->push_back(*it);
  }
}

template <class T> list<T>::~list() {
  // TODO : FILL IN HERE
  this->clear();
  this->size_ = 0;
}

template <class T> list<T> &list<T>::operator=(const list &other) {
  // TODO : FILL IN HERE
  this->clear();
  this->size_ = 0;
  for(iterator it = other.cbegin(); it != other.cend() ; it++){
    this->push_back(*it);
  }
  return *this;
}

template <class T> void list<T>::push_back(const T &value) {
  // TODO : FILL IN HERE
  Node* temp = new Node(value);
  if (this->size_ == 0){
    this->head = temp;
    this->tail = temp;
  }
  else{
    temp->prev = this->tail;
    this->tail->next = temp;

  }
  this->tail=temp;
  this->size_ += 1;

}

template <class T> void list<T>::push_front(const T &value) {
  // TODO : FILL IN HERE
  Node* temp = new Node(value);
  if (this->size_ ==0){
    this->head = temp;
    this->tail = temp;
  }
  else{
    temp->next = this->head;
    this->head->prev = temp;
  }
  this->head=temp;
  this->size_ += 1;
}

template <class T> void list<T>::pop_back() {
  // TODO : FILL IN HERE
  if (this->size_ >0){
    if (this->size_==1){
      delete this->head;
      this->head = nullptr;
      this->tail = nullptr;
      this->size_ --;
    }
    else{
      Node * second_last = this->tail->prev;
      delete second_last->next;
      this->tail = second_last;
      second_last->next = nullptr;
      this->size_ --;
    }
  }
}

template <class T> void list<T>::pop_front() {
  // TODO : FILL IN HERE
  if(this->size_ >0){
    if(this->size_ == 1){
      delete this->head;
      this->head = nullptr;
      this->tail = nullptr;
      this->size_ --;
    }
    else{
      Node * second = this->head->next;
      delete second->prev;
      this->head = second;
      second->prev = nullptr;
      this->size_ --;

    }
  }
}

template <class T> void list<T>::emplace_back(T &&value) {
  // TODO : FILL IN HERE
  this->push_back(value);
  
}

template <class T> void list<T>::emplace_front(T &&value) {
  // TODO : FILL IN HERE
  this->push_front(value);
}

template <class T> std::size_t list<T>::size() const {
  // TODO : FILL IN HERE
  return this->size_;
}


template <class T> void list<T>::print() const {
  // TODO : FILL IN HERE
  for(iterator it = this->cbegin(); it != this->cend() ; it++){
    std::cout << *it << " ";
  }
  
}

template <class T> void list<T>::clear() {
  // TODO : FILL IN HERE
  while(this->head){
    this->pop_front();
  }
  this->size_ = 0;
}

template <class T> typename list<T>::iterator list<T>::begin() {
  // TODO : FILL IN HERE
  return iterator(this->head);
}

template <class T> typename list<T>::iterator list<T>::end() {
  // TODO : FILL IN HERE
  return iterator(nullptr);
}

template <class T> typename list<T>::iterator list<T>::cbegin() const {
  // TODO : FILL IN HERE
  auto temp = iterator(this->head)
  return temp;
}

template <class T> typename list<T>::iterator list<T>::cend() const {
  // TODO : FILL IN HERE
  return iterator(nullptr);
}

template <class T> typename list<T>::iterator list<T>::rbegin() {
  // TODO : FILL IN HERE
  return iterator(nullptr);
}

template <class T> typename list<T>::iterator list<T>::rend() {
  // TODO : FILL IN HERE
  return iterator(this->head);
}

template <class T> typename list<T>::iterator list<T>::crbegin() const {
  // TODO : FILL IN HERE
  return iterator(nullptr);
}

template <class T> typename list<T>::iterator list<T>::crend() const {
  // TODO : FILL IN HERE
  return iterator(this->head);
}

} // namespace getp
