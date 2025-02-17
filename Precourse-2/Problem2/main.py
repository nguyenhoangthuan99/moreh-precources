from sys import stdin
from timeit import Timer

class Node(object):
    def __init__(self, value) -> None:
        self.parent = None
        self.value = value
        self.left = None
        self.right = None
        # self.column = None
        # self.level = None

class Tree(object):
    def __init__(self,root: Node):
        self.root : Node = root

def width_of_binary_tree(args):
    '''
    Calculate the widest level and the width of that level
    =================================================================================================
    Arguments:
        + args: something containing information about the input binary tree
    Outputs:
        + widest_level: widest level of given binary tree
        + max_width: widht of the widest level of given binary tree
    '''

    ### TODO: fill in here ###
    nodes = args["nodes"]
    levels = {}
    col = {"value":1}

    def find_root(node):
        if node.parent is None: 
            return node.value
        else:
            return find_root(node.parent)
    
    def travel(node, level=1, col = col):
        global Numnode
        if node is None: return
        # print(node.value)
        # node.level = level
        travel(node.left, level=level+1, col=col)
        
        # node.column = col["value"] 
        a = levels.get(level,[])
        a.append(col["value"] )
        levels[level] = a
        col["value"] +=1
        travel(node.right, level=level+1, col=col)

    widest_level =1
    max_width = 1

    root = find_root(nodes[1])

    travel(nodes[root])

    for level, info in levels.items():
        for i in range(1,len(info)):
            if max_width < info[i] - info[i-1] +1:
                max_width = info[i] - info[i-1] + 1
                widest_level = level

    # levels = {}
    # col = {"value":1}

    ##########################
    # print("num node",Numnode)
    return widest_level, max_width

def main():

    ### TODO: You are free to define the input value of the function as you wish. ###
    with open("./input_gen_hard_4_5516.txt","r") as f:
        lines = f.readlines()
    lines = [x.strip().replace("\n","") for x in lines]
    n = int(lines[0])
    nodes = {}
    for i in range(1,len(lines)):
        val, left, right = [int(x) for x in lines[i].split(" ")]
        current = nodes.get(val)
        if current is None:
            nodes[val] = Node(val)
        if left > -1:
            if left not in nodes: 
                nodes[left] = Node(left)
            nodes[val].left = nodes[left]
            nodes[left].parent = nodes[val]
        if right > -1:
            if right not in nodes: 
                nodes[right] = Node(right)
            nodes[val].right = nodes[right]
            nodes[right].parent = nodes[val]
    # print(len(nodes))

    args = {"nodes":nodes}

    output = width_of_binary_tree(args)
    print(output)
    
    # t = Timer(lambda: width_of_binary_tree(args))
    # base_inf_time = t.timeit(number=1000)
    # print("total time run 1000 times algorithm:",base_inf_time,"s")

    with open("output.txt", "w") as f:
        f.write(f"{output[0]} {output[1]}\n")

if __name__ == "__main__":
    main()
