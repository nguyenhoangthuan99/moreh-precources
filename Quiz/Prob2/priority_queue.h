#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <queue>

namespace getp
{

  template <class T>
  class priority_queue
  {
  private:
    // IMPLEMENT HERE
    std::vector<T> data;
    bool isLeaf(int);
    void swap(int, int);
    void maxHeapify(std::size_t);

  public:
    priority_queue();
    ~priority_queue();
    void push(const T &value);
    const T &top() const;
    void pop();
    void print();
  };

  template <class T>
  priority_queue<T>::priority_queue()
  {
    // IMPLEMENT HERE
    std::deque<T> data;
  }

  template <class T>
  priority_queue<T>::~priority_queue()
  {
    // IMPLEMENT HERE
    this->data.clear();
  }

  template <class T>
  void priority_queue<T>::push(const T &value)
  {
    // IMPLEMENT HERE
    this->data.push_back(value);
    std::size_t size_ = this->data.size();
    if (size_ ==1 ){
      return;
    }
    std::size_t current = size_-1;
    
    while (this->data[current] > this->data[(current-1)/2] && current>0)
    {
      this->swap((int)current, (int) (current-1)/2);
      current = (current-1)/2;
    }
    
  }

  template <class T>
  const T &priority_queue<T>::top() const
  {
    // IMPLEMENT HERE
    return this->data.front();
  }

  template <class T>
  void priority_queue<T>::pop()
  {
    // IMPLEMENT HERE
    // this->data.pop_front();
    
    this->swap(0,this->data.size()-1);
    // this->data.erase(this->data.end());
    this->data.pop_back();
    this->maxHeapify(0);
  }

  template <class T>
  bool priority_queue<T>::isLeaf(int pos)
  {
    // IMPLEMENT HERE
    if (pos >= (this->data.size() / 2) && pos <= this->data.size())
      return true;
    return false;
  }

  template <class T>
  void priority_queue<T>::swap(int i, int j)
  {
    // IMPLEMENT HERE
    T temp = this->data.at(i);
    this->data[i] = this->data[j];
    this->data[j] = temp;
  }

  template <class T>
  void priority_queue<T>::maxHeapify(std::size_t pos)
  {
    // IMPLEMENT HERE
    // if (!this->isLeaf(pos))
    // {
    //   if (this->data[pos] < this->data[2 * pos] || this->data[pos] < this->data[2 * pos + 1])
    //   {
    //     if (this->data[2 * pos] > this->data[2 * pos+1]){
    //       this->swap(pos,2*pos);
    //       this->maxHeapify(2*pos);
    //     }
    //     else{
    //       this->swap(pos,2*pos+1);
    //       this->maxHeapify(2*pos+1);
    //     }
    //   }
    // }
    std::size_t temp = pos, left = 2*pos +1, right = 2*pos+2 , n = this->data.size();
    if (n==0){
      return;
    }
    if (left<n && this->data[left]>this->data[temp]){
      temp = left;
    }
    if (right<n && this->data[right]>this->data[temp]){
      temp = right;
    }
    if (temp!= pos){
      this->swap(temp,pos);
      this->maxHeapify(temp);
    }

  }
template <class T>
  void priority_queue<T>::print()
  {
    // IMPLEMENT HERE
    std::vector<int>::iterator it;
    for (it = this->data.begin(); it != this->data.end(); ++it)
        std::cout << *it<<"\t";
    std::cout << '\n';
  }
} // namespace getp
