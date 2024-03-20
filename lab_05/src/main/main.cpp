#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex> 
#include <queue>
#include <cstdio>
#include <thread>
using namespace std;

class Matrix
{
private:
    vector<vector<int>> arr;
public:
    Matrix(size_t r, size_t c)
    {
        vector<vector<int>> tmp(r, vector<int>(c, 0));
        this->arr = tmp;
    }
    ~Matrix() {}
    void randomMatrix()
    {
        srand((unsigned)time(NULL));
        for (int i = 0; i < arr.size(); i++)
            for (int j = 0; j < arr[0].size(); j++)
                arr[i][j] = rand() % 10;
    }
    Matrix transposeMatrix()
    {
        int r = this->arr[0].size();
        int c = this->arr.size();
        Matrix res(r, c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                res.arr[i][j] = this->arr[j][i];
        return res;
    }
    Matrix sumMatrix(Matrix& m)
    {
        int r = this->arr.size();
        int c = this->arr[0].size();
        Matrix res(r, c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                res.arr[i][j] = this->arr[i][j] + m.arr[i][j];
        return res;
    }
    Matrix mulMatrix(Matrix& m)
    {
        int r = this->arr.size();
        int c = this->arr[0].size();
        Matrix res(r, c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                for (int k = 0; k < r; k++)
                    res.arr[i][j] += (arr[i][k] * m.arr[k][j]);
        return res;
    }
};

struct strings_state
{
    bool stage_1;
    bool stage_2;
    bool stage_3;
};

using strings_state_t = struct strings_state;

struct result_time
{
    int task;
    int tape;

    double beg;
    double end;

    chrono::time_point<chrono::system_clock> time_begin;
};

using res_time_t = struct result_time;


vector<int> algoS(string text, string pattern)
{
    int n = text.size(), m = pattern.size();
    vector<int> res;

    int flag = 0;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == pattern[0])
            flag = 1;
        if (flag)
        {
            j = i + 1;
            for (int k = 1; flag && k < m && j < n; j++, k++)
                if (text[j] != pattern[k])
                {
                    flag = 0;
                }
        }
        if (flag && j - i == m)
            res.push_back(i);
        flag = 0;
    }
    return res;
}

void init_time_result_arr(vector<res_time_t>& time_result_arr,
    chrono::time_point<chrono::system_clock> time_begin,
    int cnt_matr, int cnt_threads)
{
    int len = cnt_matr * cnt_threads;
    time_result_arr.resize(len);

    for (int i = 0; i < len; i++)
    {
        res_time_t time_res;
        time_res.time_begin = time_begin;

        time_result_arr[i] = time_res;
    }

}

void print_res_time(vector<res_time_t>& time_result_arr, int size_arr)
{
    printf("--------------------------------------------------------"
        "\n    Матрица    |     Шаг     |    Начало   |    Конец \n"
        "--------------------------------------------------------\n");

    for (int i = 0; i < size_arr; i++)
    {
        printf("    %3d      |     %2d     |   %.6f   |   %.6f   \n",
            time_result_arr[i].task,
            time_result_arr[i].tape,
            time_result_arr[i].beg,
            time_result_arr[i].end);

        if ((i + 1) % 3 == 0)
        {
            printf("--------------------------------------------------------\n");
        }
    }
}

void save_result(vector<res_time_t>& time_result_arr,
    chrono::time_point<chrono::system_clock> time_start,
    chrono::time_point<chrono::system_clock> time_end,
    chrono::time_point<chrono::system_clock> time_begin,
    int task_num, int numb_stage)
{
    double beg_time = (chrono::duration_cast<chrono::nanoseconds>
        (time_start - time_begin).count()) / 1e9;

    double end_time = (chrono::duration_cast<chrono::nanoseconds>
        (time_end - time_begin).count()) / 1e9;

    int index = (task_num - 1) * 3 + numb_stage - 1;

    time_result_arr[index].task = task_num;
    time_result_arr[index].tape = numb_stage;
    time_result_arr[index].beg = beg_time;
    time_result_arr[index].end = end_time;
}

void task1(mutex& m1, queue<Matrix>& qA1, queue<Matrix>& qA2)
{
    m1.lock();
    auto A = qA1.front();
    m1.unlock();
    auto A_transpose = A.transposeMatrix();
    auto B = A.sumMatrix(A_transpose);
    m1.lock();
    qA2.push(B);
    m1.unlock();

    qA1.pop();
}

void task2(mutex& m1, mutex& m2, queue<Matrix>& qA2, queue<Matrix>& qA3)
{

    m1.lock();
    auto B = qA2.front();
    m1.unlock();
    auto B_transpose = B.transposeMatrix();
    auto C = B.sumMatrix(B_transpose);

    m2.lock();
    qA3.push(C);
    m2.unlock();

    m1.lock();
    qA2.pop();
    m1.unlock();
}

void task3(mutex& m2, queue<Matrix>& qA3)
{
    m2.lock();
    auto C = qA3.front();
    m2.unlock();
    auto A = C;

    Matrix C_new = C.mulMatrix(A);

    m2.lock();
    qA3.pop();
    m2.unlock();
}

void liner(int cnt, bool is_count)
{
    queue<Matrix> qA1;
    queue<Matrix> qA2;
    queue<Matrix> qA3;
    mutex m1;
    mutex m2;

    chrono::time_point<chrono::system_clock> time_start, time_end,
        time_begin = chrono::system_clock::now();

    vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);

    for (int i = 0; i < cnt; i++)
    {
        Matrix m(100, 100);
        m.randomMatrix();
        qA1.push(m);
    }

    for (int i = 0; i < cnt; i++)
    {
        time_start = chrono::system_clock::now();
        task1(ref(m1), ref(qA1), ref(qA2));
        time_end = chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 1);

        time_start = chrono::system_clock::now();
        task2(ref(m1), ref(m2), ref(qA2), ref(qA3));
        time_end = chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 2);

        time_start = chrono::system_clock::now();
        task3(ref(m2), ref(qA3));
        time_end = chrono::system_clock::now();

        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, i + 1, 3);
    }

    if (is_count)
    {
        printf("|     %4d      |   %.6f  \n",
            cnt, time_result_arr[cnt - 1].end);
    }
    else
    {
        print_res_time(time_result_arr, cnt * 3);
    }
}

void parallel_stage_1(mutex& time_mutex, mutex& m1, queue<Matrix>& qA1, queue<Matrix>& qA2, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool& qA1_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (!qA1.empty())
    {
        time_start = chrono::system_clock::now();
        task1(m1, qA1, qA2);
        time_end = chrono::system_clock::now();
        time_mutex.lock();
        save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 1);
        time_mutex.unlock();
        state[task_num - 1].stage_1 = true;
        task_num++;
    }
    qA1_is_empty = true;
}

void parallel_stage_2(mutex& time_mutex, mutex& m1, mutex& m2, queue<Matrix>& qA2, queue<Matrix>& qA3, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool& qA1_is_empty, bool& qA2_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (1)
    {
        if (qA2.empty() == false)
        {
            if (state[task_num - 1].stage_1 == true)
            {
                time_start = chrono::system_clock::now();
                task2(m1, m2, qA2, qA3);
                time_end = chrono::system_clock::now();
                time_mutex.lock();
                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 2);
                time_mutex.unlock();
                state[task_num - 1].stage_2 = true;
                task_num++;
            }
        }
        else if (qA1_is_empty)
            break;
    }
    qA2_is_empty = true;
}

void parallel_stage_3(mutex& time_mutex, mutex& m2, queue<Matrix>& qA3, vector<strings_state_t>& state, vector<res_time_t>& time_result_arr, bool& qA2_is_empty)
{
    chrono::time_point<chrono::system_clock> time_start, time_end;
    int task_num = 1;
    while (1)
    {
        if (qA3.empty() == false)
        {
            if (state[task_num - 1].stage_2 == true && state[task_num - 1].stage_1 == true)
            {
                time_start = chrono::system_clock::now();
                task3(m2, qA3);
                time_end = chrono::system_clock::now();
                time_mutex.lock();
                save_result(time_result_arr, time_start, time_end, time_result_arr[0].time_begin, task_num, 3);
                time_mutex.unlock();
                state[task_num - 1].stage_3 = true;
                task_num++;
            }
        }
        else if (qA2_is_empty)
            break;
    }
}

void parallel(int cnt, bool is_count)
{
    queue<Matrix> qA1;
    queue<Matrix> qA2;
    queue<Matrix> qA3;

    bool qA1_is_empty = false;
    bool qA2_is_empty = false;
    mutex m1;
    mutex m2;
    mutex time_mutex;

    for (int i = 0; i < cnt; i++)
    {
        Matrix m(100, 100);
        m.randomMatrix();
        qA1.push(m);
    }

    vector<strings_state_t> state(cnt);
    for (int i = 0; i < cnt; i++)
    {
        strings_state_t tmp_state;
        tmp_state.stage_1 = false;
        tmp_state.stage_2 = false;
        tmp_state.stage_3 = false;
        state[i] = tmp_state;
    }
    chrono::time_point<chrono::system_clock> time_begin = chrono::system_clock::now();
    vector<res_time_t> time_result_arr;
    init_time_result_arr(time_result_arr, time_begin, cnt, 3);
    thread threads[3];
    threads[0] = thread(parallel_stage_1, ref(time_mutex), ref(m1), ref(qA1), ref(qA2), ref(state), ref(time_result_arr), ref(qA1_is_empty));
    threads[1] = thread(parallel_stage_2, ref(time_mutex), ref(m1), ref(m2), ref(qA2), ref(qA3), ref(state), ref(time_result_arr), ref(qA1_is_empty), ref(qA2_is_empty));
    threads[2] = thread(parallel_stage_3, ref(time_mutex), ref(m2), ref(qA3), ref(state), ref(time_result_arr), ref(qA2_is_empty));

    for (int i = 0; i < 3; i++)
        threads[i].join();
    if (is_count)
        printf("|     %4d      |   %.6f  \n",
            cnt, time_result_arr[cnt - 1].end);
    else
        print_res_time(time_result_arr, cnt * 3);
}

int get_choice()
{
    cout <<
        "\n\tМеню\n\n"
        "\t1. Линейная реализация\n"
        "\t2. Конвейерная реализация\n"
        "\t3. Сравнить по времени\n"
        "\t0. Выход \n\n"
        "\tВведите команду: ";

    int r;
    cin >> r;
    return r;
}

void compare_time()
{
    cout << "Конвейерная реализация\n";
    printf("| Количество заявок |  Конец  \n"
        "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        parallel(i, true);
    }
    cout << "Линейная реализация\n";
    printf("| Количество заявок |  Конец  \n"
        "-----------------------------------------------\n");
    for (int i = 50; i < 2000; i *= 2)
    {
        liner(i, true);
    }
}

int main()
{
    srand(time(nullptr));
    int choice = -1;

    while (choice)
    {
        int choice = get_choice();
        if (choice < 0 || choice > 3)
        {
            cout << "Введите еще раз!\n";
            continue;
        }
        if (choice == 1)
        {
            int cnt;
            cout << "\tВведите количество заявок: "; cin >> cnt;
            liner(cnt, false);
        }
        else if (choice == 2)
        {
            int cnt;
            cout << "\tВведите количество заявок: "; cin >> cnt;
            parallel(cnt, false);
        }
        else if (choice == 3)
        {
            compare_time();
        }
        break;
    }
    return 0;
}
