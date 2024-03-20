from random import sample
from avl import AVLTree
from bst import BST
from graphing import drawing_graph_AVL, drawing_graph_BST
from menu import menu

sizes = ['128', '256', '512', '1024', '2048']

def main():
    menu()
    option = int(input("\tВвести выбор: "))
    if (option == 1):
        bst = BST()
        N = int(input("\tКоличество элементов N: "))
        for _ in range(N):
            bst.insert_key(int(input("\t")))
        number = int(input("\tКлючевое число: "))
        print("\t", bst.search_key(number))
    elif (option == 2):
        avl = AVLTree()
        N = int(input("\tКоличество элементов N: "))
        for _ in range(N):
            avl.insert_key(int(input("\t")))
        number = int(input("\tКлючевое число: "))
        print("\t", avl.search_key(number))
    else:
        drawing_graph_AVL(sizes)
        drawing_graph_BST(sizes)

if __name__ == "__main__":
    main()
