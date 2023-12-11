class MinHeap:
    def __init__(self):
        self.heap = []

    def push(self, value):
        # TODO : FILL IN HERE
        self.heap.append(value)
        index = len(self.heap ) -1
        parent = (index - 1)//2
        while self.heap[parent] > self.heap[index] and index > 0:
            tmp = self.heap[index]
            self.heap[index] = self.heap[parent]
            self.heap[parent] = tmp

            index = parent
            parent = (index-1)//2


    def pop(self):
        # TODO : FILL IN HERE
        self.heap[0] = self.heap[len(self.heap)-1]
        self.heap.pop()
        self.heapify()

    def heapify(self):
        # TODO : FILL IN HERE
        index = 0
        temp = index
        left = 2*index +1
        right = 2*index+2
        n = len(self.heap)

        while (True):
            if left < n and self.heap[left] < self.heap[temp]:
                temp = left
            if right < n and self.heap[right] < self.heap[temp]:
                temp = right

            if temp != index:
                temp_value = self.heap[temp]
                self.heap[temp] = self.heap[index]
                self.heap[index] = temp_value
                index = temp
            else:
                break

if __name__ == "__main__":
    min_heap = MinHeap()

    with open('input_heap.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            value = int(line.strip())
            min_heap.push(value)

    print("Min heap : ", min_heap.heap)
