class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, root, key):
        if root is None:
            return Node(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
        return root

    def insert_key(self, key):
        self.root = self.insert(self.root, key)

    def search(self, root, key):
        if root is None or root.key == key:
            return root
        if key < root.key:
            return self.search(root.left, key)
        else:
            return self.search(root.right, key)

    def search_key(self, key):
        return self.search(self.root, key)
    
    def count_comp_in_search(self, root, key, count):
        if root is None or root.key == key:
            return count + 1
        if key < root.key:
            return self.count_comp_in_search(root.left, key, count + 1)
        else:
            return self.count_comp_in_search(root.right, key, count + 1)
        
    def count_comp_in_search_key(self, key):
        return self.count_comp_in_search(self.root, key, 0)
