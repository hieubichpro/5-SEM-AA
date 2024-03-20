from compare import compareAlgorithms, abc
from algorithms import *

EXIT = 0
LEV = 1
DAM = 2
DAM_REC = 3
DAM_REC_CACHE = 4
TEST =  5

MENU = "\n\nМеню \n\n \
1. Нерекурсивный Левенштейн \n \
2. Нерекурсивный Дамерау-Левенштейн \n \
3. Рекурсивный Дамерау-Левенштейн \n \
4. Рекурсивный Дамерау-Левенштейн с кешем \n \
5. Измерить время \n \
0. Выход \n\n \
\
Выбор: \
"

def InputStrings():
    str1 = input("\nВведите 1-ую строку:\t")
    str2 = input("Введите 2-ую строку:\t")
    return str1, str2

option = -1

while (option != EXIT):
    try:
        option = int(input(MENU))
    except:
        option = -1

    if (option == LEV):
        str1, str2 = InputStrings()
        print("\nРезультат: ", levenshteinDistance(str1, str2))
    elif (option == DAM):
        str1, str2 = InputStrings()
        print("\nРезультат: ", damerauLevenshteinDistance(str1, str2))

    elif (option == DAM_REC):
        str1, str2 = InputStrings()
        print("\nРезультат: ", damerauLevenshteinDistanceRecursive(str1, str2))

    elif (option == DAM_REC_CACHE):
        str1, str2 = InputStrings()
        print("\nРезультат: ", damerauLevenshteinDistanceRecurciveCache(str1, str2))

    elif (option == TEST):
        compareAlgorithms()
    elif (option == 6):
        abc()
    elif (option == EXIT):
        break

    else:
        print("\nПовторите ввод\n")