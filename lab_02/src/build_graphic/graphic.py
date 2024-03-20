import csv
import matplotlib.pyplot as plt

def read_file(file_name):
    sizes = []
    time_standard = []
    time_vinograd = []
    time_opt_vinograd = []
    with open(file_name, mode ='r') as f:
        csvFile = csv.reader(f)
        i = 0
        for line in csvFile:
            if i < 2:
                i += 1
                continue
            else:
                sizes.append(int(line[0]))
                time_standard.append(float(line[1]))
                time_vinograd.append(float(line[2]))
                time_opt_vinograd.append(float(line[3]))
    return sizes, time_standard, time_vinograd, time_opt_vinograd

                
def time_graph(sizes, time_standard, time_vinograd, time_opt_vinograd):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, time_standard, label="Стандартный алгоритм", marker="*")
    plot.plot(sizes, time_vinograd, label="Алгоритм Винограда", marker="<")
    plot.plot(sizes, time_opt_vinograd, label="Оптимизированный алгоритм Винограда", marker="h")

    plt.legend()
    plt.grid()
    plt.title("Характеристики времени")
    plt.ylabel("Время (мс)")
    plt.xlabel("Размер матрицы")

    plt.show()


def memory_graph(sizes, time_standard, time_vinograd, time_opt_vinograd):
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, time_standard, label="Стандартный алгоритм", marker="*")
    plot.plot(sizes, time_vinograd, label="Алгоритм Винограда", marker="<")
    plot.plot(sizes, time_opt_vinograd, label="Оптимизированный алгоритм Винограда", marker="h")

    plt.legend()
    plt.grid()
    plt.title("Характеристики по памяти")
    plt.ylabel("Пямяти (кб)")
    plt.xlabel("Размер матрицы")

    plt.show()


sizes, time_standard, time_vinograd, time_opt_vinograd = read_file("../../tex/csv/odd.csv")
time_graph(sizes, time_standard, time_vinograd, time_opt_vinograd)
sizes, time_standard, time_vinograd, time_opt_vinograd = read_file("../../tex/csv/even.csv")
time_graph(sizes, time_standard, time_vinograd, time_opt_vinograd)

sizes, time_standard, time_vinograd, time_opt_vinograd = read_file("../../tex/csv/memory.csv")
memory_graph(sizes, time_standard, time_vinograd, time_opt_vinograd)
