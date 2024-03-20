#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> arr, int n, int x)
{
    int res = -1;
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
        {
            res = i;
            break;
        }
    return res;
}

int main()
{
    vector<int> arr;
    int x, n;
    cout << "Введите количество элементов массива: "; cin >> n;
    cout << "Введите массив из " << n << " элементов: ";
    int elem;
    for (int i = 0; i < n; i++)
    {
        cin >> elem;
        arr.push_back(elem);
    }
    cout << "Введите элемент, который вы ищете в массиве: "; cin >> x;

    int res = solution(arr, arr.size(), x);
    if (res == -1)
        cout << "В массиве нет такого элеиента" << endl;
    else
        cout << "Элемент найден в позиции " << res << endl;
    return 0;
}