#include "Matrix.h"
#include "Measure.h"

int main(void)
{
    string menu = "Меню:\n \
                  0) Выйти\n \
                  1) Посчитать стандартным алгоритмом\n \
                  2) Посчитать алгоритмом Винограда\n \
                  3) Посчитать оптимизированным алгоритмом Винограда\n \
                  4) Сравнить алгоритмы по времени\n \
                  5) Сравнить алгоритмы по памяти";
    int choice = -1;
    while (choice != 0)
    {
        cout << menu << endl;
        cout << "Введите команду: ";
        cin >> choice;
        
        if (choice >= 1 and choice <= 3)
        {
            Matrix m1, m2;
            cout << "Введите первую матрицу" << endl; cin >> m1;
            cout << "Введите вторую матрицу" << endl; cin >> m2;
            cout << "\nРезультат:" << endl;
            if (choice == 1)
                cout << m1.standartMul(m2);
            else if (choice == 2)
                cout << m1.vinogradMul(m2);
            else
                cout << m1.optVinogradMul(m2);
        }
        else if (choice == 4)
        {
            timeTest(true);
            timeTest(false);
        }
        else if (choice == 5)
            memoryTest();
        else if (choice != 0)
            cout << "Повторите" << endl;
    }

	return 0;
}

