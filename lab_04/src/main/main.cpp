 //main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Algo.h"
#include "Measure.h"
int main()
{
    //string txt = "ABABDABACDABABCABABAABCBCABCBABCBABCBABBABCBABCBABCBABCBBBBCBABCBABCBABCBABABABABAB";
    //string pat = "ABA";
    //string txt = "daymldayaaaymtstadayamkl";
    //string pat = "day";
    //string txt = "abcdabc";
    //string pat = "bc";
    string msg = "Меню: \n \
					0. Выход\n \
					1. Последовательный алгоритм КМП\n\
					2. Параллельный алгоритм КМП\n \
					3. Замер времени\n \
Введите команду: ";
    int choice = -1;
    while (choice != 0)
    {
        cout << msg;
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            vector<int> res;
            string txt, pat;
            int k;
            cout << "Введите строку: ";
            cin >> txt;
            cout << "Введите паттерн: ";
            cin >> pat;
            if (choice == 1)
                res = algoKMP(txt, pat);
            else
            {
                cout << "Введите количесто потоков: ";
                cin >> k;
                res = parallelKMP(txt, pat, k);
            }
            for (int i = 0; i < res.size(); i++)
                cout << res[i] << " ";
            cout << endl;
        }
        else if (choice == 3)
            timeMeasure();
        else
            choice = 0;
    }
    return 0;
}