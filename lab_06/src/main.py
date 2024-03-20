from parametrization import parametrization
from compare import compareTime
from algo import solveAntAlgo, solveBruteForce

MSG = "\nМеню\n"\
      "1. Полный перебор \n"\
      "2. Муравьиный алгоритм \n"\
      "3. Параметризация \n"\
      "4. Замеры времени \n"\
      "0. Выход \n\n"\
      "Введите команду:"
choice = -1

while choice != 0:
    choice = int(input(MSG))
    if choice == 1:
        solveBruteForce()

    elif choice == 2:
        solveAntAlgo()

    elif choice == 3:
        parametrization(True)

    elif choice == 4:
        compareTime()
        
    else:
        choice = 0
