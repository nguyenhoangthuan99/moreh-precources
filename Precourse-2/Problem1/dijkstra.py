import heap
class Node(object):
    def __init__(self, vertex, distance) -> None:
        self.vertex = vertex
        self.distance = distance

    def __str__(self) -> str:
        return f"{self.vertex} - {self.distance}"
    def __lt__(self, other):
        return self.distance < other.distance

    def __le__(self, other):
        return self.distance <= other.distance

    def __gt__(self, other):
        return self.distance > other.distance

    def __ge__(self, other):
        return self.distance >= other.distance

    def __eq__(self, other):
        return self.distance == other.distance

    def __ne__(self, other):
        return self.distance != other.distance
        
def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph}
    priority_queue = heap.MinHeap()
    mark = {node : 0 for node in graph}
    # TODO : FILL IN HERE
    distances[start] = 0
    priority_queue.push(Node(start,0)) 
    while(len(priority_queue.heap) > 0):
        current = priority_queue.heap[0]
        priority_queue.pop()
        if mark[current.vertex] == 1: continue
        mark[current.vertex] = 1
        for v, w in graph[current.vertex].items():
           
            if distances[v] > distances[current.vertex] + w:
                distances[v] = distances[current.vertex] + w
                priority_queue.push(Node(v,distances[v]))

    return distances

if __name__ == "__main__":
    graph = {}
    with open('./input_graph.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip().split()
            node1, node2, weight = line[0], line[1], int(line[2])
            if node1 not in graph:
                graph[node1] = {}
            graph[node1][node2] = weight

    start_node = 'A'
    result = dijkstra(graph, start_node) 
    print(f"Start Node: {start_node}")
    print(f"Shortest distances: {result}")
    # a = Node("A",4)
    # b = Node("B",5)
    # print(a>b)
