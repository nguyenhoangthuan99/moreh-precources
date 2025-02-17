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

![1702545175109](images/README/1702545175109.png)

In this function, the ```_heapify()``` is called n//2 times. So the total time complexity upper bound of heapify is O(n log(n))

### Experiment result

![1702619441057](images/README/1702619441057.png)

In this problem, it ouput to terminal the result of push operation.

Then I compare results of pop and heapify function with a python standard library *heapq*. Both of outputs are the same.

### 2. Dijkstra with min heap

Firstly, we will define some variables:

- distances[i] is shortest path from source node to node *i*
- mark[i] let us know node *i* is visited or not.
- graph[i][j] is the edge of graph, the distance from node *i* to node *j*.

The dijkstra algorithm can be describe as follow:

1. Mark all node are unvisited and the distances[i] is 0 if *i* is source node else *infinity*.
2. For current node *i*, find all of its unvisited neighbors. For each unvisited neighbor *j* if distances[j] > distances[i] + graph[i][j] then update distances[j] = distances[i] + graph[i][j].
3. When we are done consider all unvisited neighbors, set mark[i] = True so current node *i* is marked visited. This node will never be considered again.
4. If all node of graph is visited the algorithm has finished.
5. Otherwise, select in the unvisited nodes that has the smallest distance from source and set it as current node, then repeat from step #2.

The time complexity of above algorithm is O(V^2) with V is number of vertex or node of graph. This is because we need to do 2 loops, the first loop is find the unvisited node that has smallest distance from source, then the second loop, we need to for all of its neighbors.

The step #5 can be optimized using priority queue - min heap instead of using a for loop to find unvisited node has smallest distance from source. The dijkstra algorithm with min-heap can be describe as follow:

1. Mark all node are unvisited and the distances[i] is 0 if *i* is source node else *infinity*.
2. Create a min heap, each element in heap is a set of 2 value (vertex, distance), vertex is name of node, distance is the distance from source to that node. The distance will be used to compare in heap structure.
3. Push the source element to heap with distance = 0.
4. pop() the heap until get the unvisited node, this step can result in unvisited node has smallest distance from source node. This node is set as current node *i*.
5. for all neighbor *j* of current node *i*, if distances[j] > distances[i] + graph[i][j] then update distances[j] = distances[i] + graph[i][j] and push (j, distance [j]) even if *j* is already in heap.
6. repeat from step 4 until the heap is empty, the algorithm is finished.

To use the previous heap implementation, need to create a node data structure that contains vertex and distance attributes and override compare method. The Node class is implemented as follow:

![1702611964935](images/README/1702611964935.png)

With this Node implementation, when compare each element in heap, it will compare the distance.

The python implementation of Dijkstra:

![1702612775692](images/README/1702612775692.png)

The time complexity of push and pop element in heap is O(log(V)), and we need to do this process E times with E is number of edge in graph, so the time comlexity of this algorithm is O(E log(V)).

(*) The maximum number of edge in a graph is V^2, so the min heap is only better if the graph is sparse.

The run result is shortest path from source to every node

![1702619940342](images/README/1702619940342.png)

## Problem 2

The idea of this problem is, the index of column in grid is the index of node in tree when apply in order traversal. To solve this problem we will travel the tree inorder  then save the level and column number for each node, and use that infomation to calculate the widest level.

Let's define some data structures:

#### Node

A node structure has the following attribute:

- left: point to left children
- right: point to right children
- value: the name of node
- parent: point to parent node, the parent attribute is used to find the root node when in hard test, we don't know what is root.

### Levels

A python dictionary map the level and list of index column in that level.

levels = map< Level , List< ColumnIndex> >

### Algorithm

To make algorithm more generic, we need to find the root node in case the root is not the node 1. The algorithm has 3 parts: find root node, do in-order traversal, find the widest_level and max_width.

#### 1. Find root node

This part can start at any node *i*, if parent[i] is None -> *i* is root node, else we continue do the same procedure with parent[i]. Python implementation is described as follow:

![1702633809713](images/README/1702633809713.png)

The worst case of this algorithm is O(n) with n is number of node in tree.

#### 2. In-order traversal

This part, we need to do travel the left child, the current node and the last is right child. At each step we need to append the column index to levels map. The python implementation is as followed

![1702634360401](images/README/1702634360401.png)

At each node, we do a constant number of operation, and we need to travel all nodes, so the time complexity of this algorithm is O(n) with n is total number of node in tree.

#### 3. Find result

Through the tree traversal process, a list column index of a level is in incresing number automatically, so we don't need to order this list again. The process is:

- set max_width = 1, widest_level = 1
- for each level *i* in levels:
  - for each column *col* in levels[i]:
    - if max_width < dist(col) : max_width = dist(col); widest_level = i; with dist(col) is the distance of 2 consecutive column start at *col*

![1702639414224](images/README/1702639414224.png)

For this step, every node of graph corresponding to a col will be considered once, so the time comlexity is O(n).

So the total complexity of algorithm is O(n).

![1702639550523](images/README/1702639550523.png)

The experiment result run on hard test (the root node is not 1) shows that the algorithm runs 1000 times in 3.86s -> with a tree has 10000 nodes, my algorithm can run in average 4ms.

## Problem 3

### Optimize inference time

The key to optimize inference time is broadcasting. The original code using for loop and consider each image and explixit broadcast mean to a matrix has the same shape with image.

Here is my solution:

- The array A has shape (n,h,w) -> reshape to (n, h*w)
- calculate mean = np.mean(A, axis =1, keep dims = True), this operation will calculate the mean of each image in *n* images, while keeping the last axis. For that reason, the *mean* array has shape (n,1)
- call np.subtract(A,mean, out=A), this operation will internal broadcasting the axis 1 of mean to axis 1 of A, and then save to result to A. This operation corresponding to subtract each image with its mean value.
- The last operation is do matrix multiply which is the same with original code

### Optimize memory

The key to optimize memory is the order of element in array in the memory level. The array *A* is an fortran array - index the elements in column-major, while the default order of numpy is always  "C" style - rows major.  For this reason, when call A.reshape, it will allocate new memory with "C" order for array A.

To optimize this, just add the option order="F" for reshape function of numpy.

![1702706529049](images/README/1702706529049.png)

And this code can pass 2 tests

![1702642521568](images/README/1702642521568.png)

## Problem 4

In this problem, in order to improve inference time, I need to do filter on all images at the same time using numpy broadcasting.

![1702709050800](images/README/1702709050800.png)

- Firstly, we need to pad the image with zero padding and normalize image by devide by 255
- Then, calculate the output shape base on original shape, kernel size and stride.
- for each pixel in output array, apply filter on every image at the same time.

This implementation cost **0.78s** for 1 batch 32 images.

We still can optimize this time by apply numpy einsum

```
output_images[:,i,j] = np.einsum("jk,ijk->i",\
                                  kernel,images[:,ith:ith+kernel_H, \
                                                  jth :jth+kernel_W]) 
```

The einsum operation "jk,ijk->i" will define the sum and multiply operation. "jk,ijk->" mean the kernel has 2 dimensions "jk", the image piece has 3 dimensions "ijk", so "jk,ijk" means the kernel "jk" will be broadcasting to all axis i of image piece and do point-wise multiply. "->i" means the result "ijk" will be sum over the "jk" axis to produce only "i" axis.

The einsum can make the process faster, take **0.56s** for batch 32 images.

When apply only x-filter, the algorithm can recognize the edge in column directions.

![1702709856342](images/README/1702709856342.png)

While y-filter can make algorithm recognize edge in row directions.

![1702709934859](images/README/1702709934859.png)

When combine both result it can show the edge of object

![1702709981799](images/README/1702709981799.png)
