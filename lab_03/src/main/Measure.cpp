#include "Measure.h"

double getProcessTime(void (*algo)(vector<int>& m), vector<int>& arr)
{
    double time = 0;
    clock_t beg, end;
    for (int i = 0; i < TIMES; i++)
    {
        beg = clock();
        algo(arr);
        end = clock();
        time += (end - beg);
    }
    time /= TIMES;
    time /= (CLOCKS_PER_SEC);
    return 1000 * time;
}

void timeTest()
{
    //../../tex/csv/odd.csv
    ofstream file1 = ofstream("../../tex/csv/random.csv");
    ofstream file2 = ofstream("../../tex/csv/sorted.csv");
    ofstream file3 = ofstream("../../tex/csv/reverse_sorted.csv");
    vector<size_t> n;
    for (size_t i = 0; i < END_RANGE + 2; i += STEP)
        n.push_back(i);
    n[0]++;
    file1 << "size," << "beadsort," << "radixsort," << "binarysort" << endl;
    file1 << "\n";
    file2 << "size," << "beadsort," << "radixsort," << "binarysort" << endl;
    file2 << "\n";
    file3 << "size," << "beadsort," << "radixsort," << "binarysort" << endl;
    file3 << "\n";
    for (size_t i = 0; i < n.size(); i++)
    {
        vector<int> test1(n[i], 0), test2(n[i], 0), test3(n[i], 0);
        randomArr(test1);
        test2 = test1; test3 = test1;
        double t1 = getProcessTime(&beadSort, test1);
        double t2 = getProcessTime(&radixSort, test2);
        double t3 = getProcessTime(&binarySort, test3);
        cout << "Неотсортированные массивы" << endl;
        cout << "N = " << n[i] << endl;
        cout << "Сортировка бусинами: \n" << t1 << endl;
        cout << "Сортировка поразрядная: \n" << t2 << endl;
        cout << "Сортировка бинарным деревом: \n" << t3 << endl;
        file1 << n[i] << "," << t1 << "," << t2 << "," << t3 << endl;

        vector<int> test4 = test1;
        sort(test4.begin(), test4.end());
        double t4 = getProcessTime(&beadSort, test4);
        double t5 = getProcessTime(&radixSort, test4);
        double t6 = getProcessTime(&binarySort, test4);
        cout << "\nОтсортированные массивы по возрастанию: " << endl;
        cout << "Сортировка бусинами: \n" << t4 << endl;
        cout << "Сортировка поразрядная: \n" << t5 << endl;
        cout << "Сортировка бинарным деревом: \n" << t6 << endl;
        file2 << n[i] << "," << t4 << "," << t5 << "," << t6 << endl;

        vector<int> test5 = test1;
        sort(test5.begin(), test5.end(), greater<int>());
        vector<int> test6 = test5;
        vector<int> test7 = test5;
        double t7 = getProcessTime(&beadSort, test5);
        double t8 = getProcessTime(&radixSort, test6);
        double t9 = getProcessTime(&binarySort, test7);
        cout << "\nОтсортированные массивы по убыванию: " << endl;
        cout << "Сортировка бусинами: \n" << t7 << endl;
        cout << "Сортировка поразрядная: \n" << t8 << endl;
        cout << "Сортировка бинарным деревом: \n" << t9 << endl;
        file3 << n[i] << "," << t7 << "," << t8 << "," << t9 << endl;
    }
    file1.close();
    file2.close();
    file3.close();
}

size_t getMemoryBeadSort(vector<int> &arr)
{
    size_t helper = 1 * sizeof(size_t) + 3 * sizeof(int);
    size_t size_arr = arr.size() * sizeof(int) + *max_element(arr.begin(), arr.end()) * sizeof(int);
    return helper + size_arr;
}

size_t getMemoryRadixSort(vector<int>& arr)
{
    size_t helper = 1 * sizeof(size_t) + 2 * sizeof(int);
    size_t size_arr = arr.size() * sizeof(int) + 10 * sizeof(int);
    return helper + size_arr;
}

size_t getMemoryBinarySort(vector<int>& arr)
{
    size_t helper = 1 * sizeof(size_t);
    size_t node_size = log2(arr.size()) * sizeof(Node);
    size_t size_arr = arr.size() * sizeof(int);
    return helper + node_size + size_arr;
}

void memoryTest()
{
    vector<size_t> n;
    for (size_t i = 0; i < END_RANGE + 2; i += STEP)
        n.push_back(i);
    n[0]++;
    ofstream file = ofstream("../../tex/csv/memory.csv");
    file << "size," << "beadsort," << "radixsort," << "binarysort" << endl;
    for (size_t i = 0; i < n.size(); i++)
    {
        vector<int> arr(n[i], 0);
        randomArr(arr);
        double m1 = getMemoryBeadSort(arr);
        double m2 = getMemoryRadixSort(arr);
        double m3 = getMemoryBinarySort(arr);
        cout << "N = : " << n[i] << endl;
        cout << "Сортировка бусинами:\n " << m1 << endl;
        cout << "Сортировка поразрядная:\n " << m2 << endl;
        cout << "Сортировка бинарным деревом:\n " << m3 << endl;
        file << n[i] << "," << m1 / 1000 << "," << m2 / 1000 << "," << m3 / 1000 << endl;
    }
    file.close();
}