import csv
import matplotlib.pyplot as plt

def read_file(file_name):
    sizes = []
    arr1 = []
    arr2 = []
    arr3 = []
    with open(file_name, mode ='r') as f:
        csvFile = csv.reader(f)
        i = 0
        for line in csvFile:
            if i < 2:
                i += 1
                continue
            else:
                sizes.append(int(line[0]))
                arr1.append(float(line[1]))
                arr2.append(float(line[2]))
                arr3.append(float(line[3]))
    return sizes, arr1, arr2, arr3

                
def time_graph(sizes, time_beadsort, time_radixsort, time_treesort, type_massive):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, time_beadsort, label="Сортировка бусинами", marker="*")
    plot.plot(sizes, time_radixsort, label="Сортировка поразрядная", marker="<")
    plot.plot(sizes, time_treesort, label="Сортировка бинарным деревом", marker="h")

    plt.legend()
    plt.grid()
    tit = "Характеристики времени(" + type_massive + ")"
    plt.title(tit)
    plt.ylabel("Время (мс)")
    plt.xlabel("Размер матрицы")

    plt.show()


def memory_graph(sizes, memory_beadsort, memory_radixsort, memory_treesort):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, memory_beadsort, label="Сортировка бусинами", marker="*")
    plot.plot(sizes, memory_radixsort, label="Сортировка поразрядная", marker="<")
    plot.plot(sizes, memory_treesort, label="Сортировка бинарным деревом", marker="h")

    plt.legend()
    plt.grid()
    plt.title("Характеристики по памяти")
    plt.ylabel("Пямяти (кб)")
    plt.xlabel("Размер матрицы")

    plt.show()

sizes, time_beadsort, time_radixsort, time_treesort = read_file("../../tex/csv/random.csv")
time_graph(sizes, time_beadsort, time_radixsort, time_treesort, "Неотсортированные")

sizes, time_beadsort, time_radixsort, time_treesort = read_file("../../tex/csv/sorted.csv")
time_graph(sizes, time_beadsort, time_radixsort, time_treesort, "Отсортированные по возрастанию")

sizes, time_beadsort, time_radixsort, time_treesort = read_file("../../tex/csv/reverse_sorted.csv")
time_graph(sizes, time_beadsort, time_radixsort, time_treesort, "Отсортированные по убыванию")

sizes, membead, memradix, memtree = read_file("../../tex/csv/memory.csv")
memory_graph(sizes, membead, memradix, memtree)