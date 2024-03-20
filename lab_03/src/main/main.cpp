#include "Algo.h"
#include "Measure.h"

int main()
{
	string msg = "Меню: \n \
					0. Выход\n \
					1. Сортировка бусинами\n\
					2. Сортировка поразрядная\n \
					3. Сортировка бинарным деревом\n \
					4. Сравнить алгоритмы по времени\n \
					5. Сравнить алгоритмы по памяти\n \
Введите команду: ";
	int choice = -1;
	while (choice != 0)
	{
		cout << msg;
		cin >> choice;
		if (choice >= 1 && choice <= 3)
		{
			vector<int> arr;
			input_arr(arr);
			if (choice == 1)
				beadSort(arr);
			else if (choice == 2)
				radixSort(arr);
			else
				binarySort(arr);
			cout << "Отсортированный массив: ";
			print_arr(arr);
		}
		else if (choice == 4)
			timeTest();
		else if (choice == 5)
			memoryTest();
		else
			choice = 0;
	}
	return 0;
}