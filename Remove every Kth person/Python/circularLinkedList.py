# Create a class Node with instance variables 'data' and 'next'
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


# Create a class CircularLinkedList with instance variable 'head'
class CircularLinkedList:
    # Create an empty linked list
    def __init__(self):
        self.head = None

    # Insert a new node at the end of the list
    def append(self, data):
        node = Node(data)
        self.insert_at_end(node)

    # Function that returns the node before the searched one
    def get_prev_node(self, ref_node):
        if self.head is None:
            return None
        current = self.head
        while current.next != ref_node:
            current = current.next
        return current

    # Insert a new node after a known one
    def insert_after(self, ref_node, new_node):
        new_node.next = ref_node.next
        ref_node.next = new_node

    # Insert a new node before a known one
    def insert_before(self, ref_node, new_node):
        prev_node = self.get_prev_node(ref_node)
        self.insert_after(prev_node, new_node)

    # Insert a new node at the end of the list
    def insert_at_end(self, new_node):
        if self.head is None:
            self.head = new_node
            new_node.next = new_node
        else:
            self.insert_before(self.head, new_node)

    def get_node(self, index, start):
        if self.head is None:
            return None
        current = start
        for i in range(index):
            current = current.next
        return current

    # Remove a node from the list
    def remove(self, node):
        if self.head.next == self.head:
            self.head = None
        else:
            prev_node = self.get_prev_node(node)
            prev_node.next = node.next
            if self.head == node:
                self.head = node.next


# Function that returns True if a CircularLinkedList has only one
# node, else false
def has_one_node(circular_list):
    if circular_list.head.next == circular_list.head:
        return True
    else:
        return False


# Function that builds the list which contains the order in which
# the children are removed from the game
def eliminate_children(circular_list, number):
    # Create the empty list
    order = []

    # Store the node from where we start iterating over the CircularLinkedList
    start = circular_list.head

    # Remove the 'number'-th node until the CircularLinkedList has only
    # one node left
    while not has_one_node(circular_list):

        # We get the node 'number - 1' because we consider the head node
        # to represent a child and since we're already in the first node
        # of the list, we need to iterate only over 'number - 1' nodes
        to_remove = circular_list.get_node(number-1, start)

        # Store the number of the eliminated child into the 'order' list
        order.append(to_remove.data)

        # Store the node from where the counting will begin as the node
        # after the one removed
        start = to_remove.next

        # Remove the 'number'-th node from the list
        circular_list.remove(to_remove)

    # Store the number of the last child in the game
    order.append(circular_list.head.data)

    return order
