class Node:
    def __init__(self, val_=0):
        self.val = val_
        self.left = None
        self.right = None

# to insert a value into a tree:
def insert(root, value):
    if root == None:
        return Node(value)
    if value < root.val:
        root.left = insert(root.left, value)
    elif value > root.val:
        root.right = insert(root.right, value)
    return root

def print_tree(root):
    # first find the depth of the tree and the width of the tree
    print("function started.")
    stack = [[root, 0, 0]]
    const_stack = [[root, 0, 0]]

    max_depth, max_width, min_width = float('-inf'), float('-inf'), float('inf')
    while stack:
        curr = stack[0]
        stack = stack[1:]

        max_depth = max(max_depth, curr[1])
        max_width = max(max_width, curr[2])
        min_width = min(min_width, curr[2])

        if curr[0].left:
            stack.append([curr[0].left, curr[1]+1, curr[2]-1])
            const_stack.append([curr[0].left, curr[1]+1, curr[2]-1])

        if curr[0].right:
            stack.append([curr[0].right, curr[1]+1, curr[2]+1])
            const_stack.append([curr[0].right, curr[1]+1, curr[2]+1])
    # weve got the max depth and max width
    print(f"breadth first search finished: {0}", const_stack)
    width = abs(min_width) + max_width
    depth = max_depth
    # the width of the array will be 2(number of elements on the bottom) + 1
    # and also the gap for each row starts from width then to width-1 on the bottom one and then width-2 below that etc.
    # so we can use the elements from the const_stack and iterate through them
    gap = depth
    #arr = [["" /* * 2*width+1*/] for _ in range(depth+1)]
    arr = [[] for _ in range(depth+1)]
    prev = const_stack[0][1]+1
    for i in const_stack:
        # arr[i[1]].append(" " * gap)
        # arr[i[1]].append(str(i[0].val))
        arr[i[1]].append(" " * (i[2] - min_width))
        arr[i[1]].append(str(i[0].val))
        if i[1] < prev:
            gap -= 1
            prev = i[1]
    print(f"array appending stuff finished, {0}.", arr)
    # now weve got the array and now we need to print it
    for i in arr:
        #print("outer loop")
        #for j in i:
        #print("inner loop")
        print(''.join(i))
    print("function finished.")

def main():
    # do something
    root = Node(0)
    for i in [6, 3, 8, 2, 5, 7, 9, 1, 4, 10]:
        root = insert(root, i)
    stack = [root]
    while stack:
        curr = stack[0]
        print(curr.val)
        stack = stack[1:]
        if curr.left:
            stack.append(curr.left)
        #if curr.right:
        #    stack.append(curr.right)
    # this shows that creating the stack is just going fine.
    
    print_tree(root)

node_1 = Node(1)
node_2 = Node(2)
node_3 = Node(3)
node_4 = Node(4)
node_5 = Node(5)
node_6 = Node(6)
node_7 = Node(7)
node_8 = Node(8)
node_9 = Node(9)
node_10 = Node(10)
node_6.left = node_3
node_6.right = node_8
node_3.left = node_2
node_3.right = node_5
node_8.left = node_7
node_8.right = node_9
node_2.left = node_1
node_5.left = node_4
node_9.right = node_10
root = node_6

print_tree(root)
   
main()
