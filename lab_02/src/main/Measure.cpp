#include "Measure.h"

double getProcessTime(Matrix(Matrix::* mul)(Matrix& m), size_t n)
{
    double time = 0;
    clock_t t;
    Matrix a(n, n), b(n, n);
    a.randomMatrix(); b.randomMatrix();
    clock_t beg, end;
    for (int i = 0; i < TIMES; i++)
    {
        beg = clock();
        (a.*mul)(b);
        end = clock();
        time += (end - beg);
    }
    time /= TIMES;
    time /= (CLOCKS_PER_SEC);
    return 1000 * time;
}

size_t getMemory(size_t r, size_t c, string algo)
{
    if (algo == "standart")
    {
        size_t helper = 3 * sizeof(size_t);
        size_t matrix = r * c * sizeof(int);
        return helper + matrix;
    }

    else if (algo == "vinograd")
    {
        size_t helper = 4 * sizeof(size_t);
        size_t temp = (r + c) * sizeof(size_t);
        size_t matrix = r * c * sizeof(int);
        return helper + matrix + temp;
    }

    else if (algo == "opt_vinograd")
    {
        size_t helper = 4 * sizeof(size_t) + sizeof(int);
        size_t temp = (r + c) * sizeof(size_t);
        size_t matrix = r * c * sizeof(int);
        return helper + matrix + temp;
    }
}

void timeTest(bool isEven)
{
    ofstream file = ofstream("../../tex/csv/odd.csv");
    vector<size_t> n;
    for (size_t i = 1; i < END_RANGE + 2; i += STEP)
        n.push_back(i);
    if (isEven)
    {
        file = ofstream("../../tex/csv/even.csv");
        for (size_t i = 1; i < n.size(); i++)
            n[i] -= 1;
    }
    file << "size," << "standard," << "vinograd," << "opt_vinograd" << endl;
    file << "\n";
    for (size_t i = 0; i < n.size(); i++)
    {
        double t1 = getProcessTime(&Matrix::standartMul, n[i]);
        double t2 = getProcessTime(&Matrix::vinogradMul, n[i]);
        double t3 = getProcessTime(&Matrix::optVinogradMul, n[i]);
        cout << "N = " << n[i] << endl;
        cout << "Стандартный алгоритм: \n" << t1 << endl;
        cout << "Алгоритм Виноград: \n" << t2 << endl;
        cout << "Оптимизированный алгоритм Виноград: \n" << t3 << endl;
        file << n[i] << "," << t1 << "," << t2 << "," << t3 << endl;
    }
    file.close();
}

void memoryTest()
{
    ofstream file = ofstream("../../tex/csv/memory.csv");
    vector<size_t> n;
    for (size_t i = 1; i < END_RANGE + 2; i += STEP)
        n.push_back(i - 1);
    n[0] = 1;

    file << "size," << "standard," << "vinograd," << "opt_vinograd" << endl;
    file << "\n";
    for (size_t i = 0; i < n.size(); i++)
    {
        double m1 = getMemory(n[i], n[i], "standart");
        double m2 = getMemory(n[i], n[i], "vinograd");
        double m3 = getMemory(n[i], n[i], "opt_vinograd");
        cout << "N = " << n[i] << endl;
        cout << "Стандартный алгоритм: \n" << m1 << endl;
        cout << "Алгоритм Виноград: \n" << m2 << endl;
        cout << "Оптимизированный алгоритм Виноград: \n" << m3 << endl;
        file << n[i] << "," << m1 / 1000 << "," << m2 / 1000 << "," << m3 / 1000 << endl;
    }
    file.close();
}