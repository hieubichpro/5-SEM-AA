from time import process_time
import matplotlib.pyplot as plt

from generate import randomMatrix
from algo import antAlgo, bruteForce



def build_graph(sizes_arr, timeBruteForce, timeAntAlgo):

    fig1 = plt.figure(figsize = (10, 7))
    plot = fig1.add_subplot()
    plot.plot(sizes_arr, timeBruteForce, label = "Алгоритм полного перебора")
    plot.plot(sizes_arr, timeAntAlgo, label = "Муравьиный алгоритм")

    plt.legend()
    plt.grid()
    plt.title("Измерение времени")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Размер матрицы (эл)")
    
    plt.show()
    

def printTime(sizes_arr, timeBruteForce, timeAntAlgo):

    print("\n  Размер |  Муравьиный алг. | полный перебор \n" 
            "---------------------------------------------")

    ind = 0

    for num in sizes_arr:
        print("{:6}   |   {:12}   |  {:12} ".format(num, timeAntAlgo[ind], timeBruteForce[ind]))

        ind += 1


def compareTime():
    timeBruteForce = []
    timeAntAlgo = []

    sizes_arr = [2, 3, 4, 5, 6, 7, 8, 9, 10]

    for size in sizes_arr:
        
        matrix = randomMatrix(size, 1, 2)

        beg = process_time()
        bruteForce(matrix, size)
        end = process_time()

        timeBruteForce.append(end - beg)

        beg = process_time()
        antAlgo(matrix, size, 0.5, 0.5, 0.5, 300)
        end = process_time()

        timeAntAlgo.append(end - beg)
    with open("time.csv", "w") as f:
        f.write("size,bruteforce,antalgo\n")
        for i in range(len(timeBruteForce)):
            row = f"{i + 2},{timeBruteForce[i]},{timeAntAlgo[i]}\n"
            f.write(row)
    printTime(sizes_arr, timeBruteForce, timeAntAlgo)
    build_graph(sizes_arr, timeBruteForce, timeAntAlgo)
