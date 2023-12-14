# Precourse 2

## Problem 1

### 1. Min Heap

Min heap is a complete binary tree, that for any given node C and its parent P, the key of P is always less or equal key of C.

A heap data structure can be represented as an array in which, for each node ```i```, its left and right child will be at ```2*i +1``` and ```2*i+2``` position.

In this exercise, we need to implement three functions of heap data structure to ensure the heap's property after each operation.

#### push

The ```push()``` function is used to push a new element to a heap while still ensuring heap's property. The procedure of ```push()``` is described as follow:

```
1. append new value to the end of array
2. start at the end of the array, compare current node with its parents
3. if the parent is greater than current node then swap it
4. repeat step #2 and #3 until the heap property is satisfied or the root node has been swapped.
```

![1702540668800](images/README/1702540668800.png)

With this procedure, we start from the end of array and the index will be divided by 2 each step, so the time complexity of algorithm is O(log n) with n is the size of array.

#### _heapify() a node

This is an common function which will be used in ```pop()``` and ```heapify``` function. This function will compare the current node with its children and swap until it less than its children.

![1702542092969](images/README/1702542092969.png)

The time complexity of this function is O(log n) with n is the size of heap, because the index will be multiplied by 2 at each step until it out of array.

#### pop

The ```pop()``` is used to delete the smallest element of an array. The procedure to pop is described as follow:

```
1. get the smallest value of the heap
2. replace the first element by the last element of the heap
3. remove the last element
4. do the _heapify() on the first element
```

![1702544734246](images/README/1702544734246.png)

The time complexity is equal to the _heapify() - O(log n).

#### heapify

This function is used to transform an array to heap structure. This task can be done by apply ```_heapify()``` on all none-leaf node in bottom-up order.

```
