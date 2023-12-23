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

#### list

`list()`:

`list(const list &other)`:

`list(std::initializer_list<T> initList)`:

`~list()`:

`operator=(const list &other)`:

`push_back(const T &value)`:

`push_front(const T &value)`:

`pop_back()`:

`pop_front()`:

`emplace_back(T &&value)`:

`emplace_front(T &&value)`:

`size() `:

`print()`:

`clear()`:

`begin()`:

`end()`:

`cbegin()`:

`cend()`: