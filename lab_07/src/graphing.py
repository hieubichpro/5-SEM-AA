import matplotlib.pyplot as plt
import numpy as np

def drawing_graph_AVL(sizes):
    avl_not_found = []
    avl_found_max = []
    for size in sizes:
        size = int(size)
        arr_temp = sample(range(size * 2), size)
        max_el = max(arr_temp)
        avl = AVLTree()
        for k in arr_temp:
            avl.insert_key(k)
        avl_not_found.append(avl.count_comp_in_search_key(size * 5))
        print(avl.search_key(size * 5))
        avl_found_max.append(avl.count_comp_in_search_key(max_el))
        print(avl.search_key(max_el))

    print(avl_not_found, avl_found_max)

    X_axis = np.arange(len(sizes))
    plt.bar(X_axis - 0.1, avl_not_found, color='orange', label = "случай отсутствия элемента", width=0.2)
    plt.bar(X_axis + 0.1, avl_found_max, color='green', alpha=0.5, label='случай элемента в листе на мак_ной высоте дерева', width=0.2)
    plt.xticks(X_axis, sizes)
    plt.xlabel('Количество элементов')
    plt.ylabel('Количества сравнений')
    plt.title('Графика зависимости количеств сравнений от количеств элементов (в сбалансированном дереве)')
    plt.legend()
    plt.show()

def drawing_graph_BST(sizes):
    bst_not_found = []
    bst_found_max = []
    for size in sizes:
        size = int(size)
        arr_temp = sample(range(size * 2), size)
        max_el = max(arr_temp)
        bst = BST()
        for k in arr_temp:
            bst.insert_key(k)
        bst_not_found.append(bst.count_comp_in_search_key(size * 5))
        print(bst.search_key(size * 5))
        bst_found_max.append(bst.count_comp_in_search_key(max_el))
        print(bst.search_key(max_el))

    print(bst_not_found, bst_found_max)

    X_axis = np.arange(len(sizes))
    plt.bar(X_axis - 0.1, bst_not_found, color='orange', label = "случай отсутствия элемента", width=0.2)
    plt.bar(X_axis + 0.1, bst_found_max, color='green', alpha=0.5, label='случай элемента в листе на мак_ной высоте дерева', width=0.2)
    plt.xticks(X_axis, sizes)
    plt.xlabel('Количество элементов')
    plt.ylabel('Количества сравнений')
    plt.title('Графика зависимости количеств сравнений от количеств элементов (в несбалансированном дереве)')
    plt.legend()
    plt.show()
