class MinHeap:
    def __init__(self):
        self.heap = []

    def push(self, value):
        # TODO : FILL IN HERE
        try:
            self.heap.append(value)
            index = len(self.heap ) -1
            parent = (index - 1)//2
            while self.heap[parent] > self.heap[index] and index > 0:
                tmp = self.heap[index]
                self.heap[index] = self.heap[parent]
                self.heap[parent] = tmp

                index = parent
                parent = (index-1)//2
        except Exception as e:
            print(e)

    def _heapify(self,index):
        temp = index
        left = 2*index +1
        right = 2*index+2
        n = len(self.heap)
        if n ==0 : return

        
        if left < n and self.heap[left] < self.heap[temp]:
            temp = left
        if right < n and self.heap[right] < self.heap[temp]:
            temp = right

        if temp != index:
            temp_value = self.heap[temp]
            self.heap[temp] = self.heap[index]
            self.heap[index] = temp_value
            self._heapify(temp)


    def pop(self):
        try:
        # TODO : FILL IN HERE
            if len(self.heap) == 0: 
                raise Exception("Heap is empty")
            value = self.heap[0]
            self.heap[0] = self.heap[len(self.heap)-1]
            self.heap.pop()
            self._heapify(0)
            
            return value
        except Exception as e:
            print(e)

    def heapify(self):
        # TODO : FILL IN HERE

        try:
            for i in reversed(range(0, len(self.heap) //2)):
                self._heapify(i)
                
        except Exception as e:
            print(e)

if __name__ == "__main__":
    min_heap = MinHeap()

    with open('input_heap.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            value = int(line.strip())
            min_heap.push(value)
        # min_heap.pop()
        array = [int(x.strip()) for x in lines]
    

    print("Min heap : ", min_heap.heap)
    print("-"*20)
    min_heap.heap = array.copy()
    print("compare result with heapq standard python library")
    print("heapify function:")
    min_heap.heapify()
    print("Result of my algorithm:", min_heap.heap)
    import heapq
    heapq.heapify(array)
    print("Result of heapq:       ",array)
    print("-"*20)
    print("pop function: ")
    min_heap.pop()
    heapq.heappop(array)
    
    print("Result of my algorithm:",min_heap.heap)
    print("Result of heapq:       ",array)
