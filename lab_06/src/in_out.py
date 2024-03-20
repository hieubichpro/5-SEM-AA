from os import system
import numpy as np


MATRIX_SELECTION = False
KOEFS_INPUT      = False
DAYS_INPUT       = True

DEFAULT_MATRIX = 2
DEFAULT_ALPHA = 0.6
DEFAULT_EVAPORATION = 0.6
DEFAULT_DAYS = 20


def list_files():
    system("ls ../data > files.txt")

    f = open("files.txt", "r")
    files = f.read().split()
    f.close()

    if MATRIX_SELECTION:
        print("\nДоступные файлы: \n")

        for i in range(len(files)):
            print("    %2d. %s" % (i + 1, files[i]))

    system("rm files.txt")

    return files


def read_file_matrix(file_name):
    f = open(file_name, "r")
    size = len(f.readline().split())
    f.seek(0)

    matrix = np.zeros((size, size), dtype = int)
    
    i = 0
    for line in f.readlines():
        j = 0

        for num in line.split():
            matrix[i][j] = int(num)
            j += 1

        i += 1

    f.close()

    return matrix


def read_matrix():

    matrix = read_file_matrix('data.csv')

    return matrix


def print_matrix(matrix):

    print()
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):

            print("%4d" % (matrix[i][j]), end = "")

        print()


def getCoefs():
    
    if KOEFS_INPUT:
        alpha       = float(input("\nВведите коэффициент alpha:"))
        beta        = beta = 1 - alpha
        evaporation = float(input("Введите коэффициент evaporation:"))
    else:
        alpha       = DEFAULT_ALPHA
        beta        = 1 - DEFAULT_ALPHA
        evaporation = DEFAULT_EVAPORATION

        print("\nКоэффициент alpha = ", alpha)
        print("Коэффициент beta  = ", beta)
        print("Коэффициент evaporation = ", evaporation)

    if DAYS_INPUT:
        days = int(input("\nВведите кол-во дней: "))
    else:
        days = DEFAULT_DAYS
        print("\nКол-во дней = ", days)

    return alpha, beta, evaporation, days
