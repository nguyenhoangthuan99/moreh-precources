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
    std::deque<T> data;
    bool isLeaf(int);
    void swap(int, int);
    void maxHeapify(int);

  public:
    priority_queue();
    ~priority_queue();
    void push(const T &value);
    const T &top() const;
    void pop();
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
    std::size_t current = size_;
    while (this->data[current] > this->data[(current-1)/2] && current>0)
    {
      this->swap((int)current, (int) (current-1)/2);
      current = (current-1)/2
    }
    
  }

  template <class T>
  const T &priority_queue<T>::top() const
  {
    // IMPLEMENT HERE
    T element = this->data.front();
    return element;
  }

  template <class T>
  void priority_queue<T>::pop()
  {
    // IMPLEMENT HERE
    this->data.pop_front();
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
  void priority_queue<T>::maxHeapify(int pos)
  {
    // IMPLEMENT HERE
    if (!this->isLeaf(pos))
    {
      if (this->data[pos] < this->data[2 * pos] || this->data[pos] < this->data[2 * pos + 1])
      {
        if (this->data[2 * pos] > this->data[2 * pos+1]){
          this->swap(pos,2*pos);
          this->maxHeapify(2*pos);
        }
        else{
          this->swap(pos,2*pos+1);
          this->maxHeapify(2*pos+1);
        }
      }
    }
  }
} // namespace getp
