import heap

def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph}
    # TODO : FILL IN HERE

    return distances

if __name__ == "__main__":
    graph = {}
    with open('input_graph.txt', 'r') as file:
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
