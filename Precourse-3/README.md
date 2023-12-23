# Precourse 3

## Problem 1

### List

#### Node

The `Node` class need to implement contructor:

```
data = value;
next = nullptr;
prev = nullptr;
```

The `nullptr` has type std::nullptr_t, which can implicitly converted to any pointer type, we shouldn't assign `next = NULL` or `prev = NULL` because it will cause ambiguity in overloaded function in this case:

```
f(int);
f(foo *);
```

#### Iterator

`iterator(Node *node)` :
This function will assign the attribute `current` to the node by

```
this->current = node;
``````

`iterator::operator*()`:
This function return the data in the current node of iterator, implement this by

```
return this->current->data;
```

`iterator::operator++()`:
This function overrides prefix increment of iterator, coressponding to `++x`, which means increase value of `x` then assign it to other variable.

```
current = current->next;
return *this;
```

`iterator::operator++(int)`:
This function overrides postfix increment of iterator, coresponding to `x++`, which means assign value of `x` first, then increases `x`.

```
auto temp = iterator (current);
current = current->next;
return temp;
```

`operator!=(const iterator &other)`:
This function will compare 2 iterator to decide whether it point to the same node:

```
return this->current != other.current;
```

#### list member function

`list()`:

This is an empty constructor of list, need to point head, tail to `nullptr` and set `size_ = 0`.

```
this->head = nullptr;
this->tail = nullptr;
this->size_ = 0;
```

`list(const list &other)`:
This is constructor from another list, firstly need to init empty list, then for each element of input list, use `push_back` to append value to new list.

```
new (this) list();
this->size_ = 0;
for(iterator it = other.cbegin(); it != other.cend() ; ++it){
this->push_back(*it);
}
```

`list(std::initializer_list<T> initList)`:
This is constructor from an array or a object has datatype that can implicitly convert to type `std::initializer_list`.

```
this->size_ = 0;
  new (this) list();
  for (auto it = initList.begin();it!=initList.end(); ++it){
    this->push_back(*it);
  }
```

`~list()`:
This is destructor of a list, just simply call `clear()` and set `size_ = 0`.

```
this->clear();
this->size_ = 0;
```

`operator=(const list &other)`:
This is implementation of operator `=`, the logic will be the same with constructor from another list, but need to return pointer to current list

```
this->clear();
this->size_ = 0;
for(iterator it = other.cbegin(); it != other.cend() ; it++){
this->push_back(*it);
}
return *this;
```

`push_back(const T &value)`:
Append value to the end of a list, this process requires create new Node, chain the new node to the end of list and point the `tail` to new node. Don't forget to increase the size by 1.

```
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
```

`push_front(const T &value)`:
This is the same logic with `push_back` unless it insert to the head of list.

`pop_back()`:

Remove the last element of a list, this function only executes when list is not empty. If the size of list is 1, need to point both `head` and `tail` to `nullptr`. Else, delete the last node and modify the second last point to `nullptr` and point `tail` to second last.

```
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
```

`pop_front()`:
The logic will be the same with `pop_back`.

`emplace_back(T &&value)`:

This function will use the `push_back`.

```
this->push_back(value);
```

`emplace_front(T &&value)`:

This function will use the `push_front`.

```
this->push_front(value);
```

`size() `:
This function will return the size of list

```
return this->size_
```

`print()`:
This function will print all value of a list from head to tail.

```
for(iterator it = this->cbegin(); it != this->cend() ; it++){
std::cout << *it << " ";
}
```

`clear()`:
The logic of this function is: while the head still point to an not null pointer, do the `pop_front`.

```
while(this->head){
    this->pop_front();
}
this->size_ = 0;
```

`begin()`:
This function return iterator point to head of a list.

```
return iterator(this->head);
```

`end()`:
This function return iterator point to tail of a list - always a null pointer.

```
return iterator(nullptr);
```

`cbegin()`:
This function return a constant iterator point to head of a list. A constant iterator won't allow to modify the data.

```
const auto temp = iterator(this->head)
return temp;
```

`cend()`:
This function return a constant iterator point to tail of a list. Because tail alway null pointer so it will like the end().

```
return iterator(nullptr);
```

After finish implementation, the result output in terminal.

![1703320924186](images/README/1703320924186.png)


---
### vector

`vector()`:

`~vector()`:

`vector(const vector &other)`:

`vector(vector &&other)`:

`operator=(const vector &other)`:

`operator=(vector &&other)`:

`at(size_t index)`:

`operator[](size_t index)`:

`front()`:

`back()`:

`data()`:

`getSize()`:

`push_back(const T &value)`:

`emplace_back(Args &&... args)`:

`append_range(InputIt first, InputIt last)`:

`pop_back()`:

`reserve(size_t newCapacity)`:

`begin()`:

`cbegin()`:

`end()`:

`cend()`:

`rbegin()`:

`crbegin()`:

`rend()`:

`crend()`:
