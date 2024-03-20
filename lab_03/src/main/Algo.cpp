#include "Algo.h"

void print_arr(const vector<int>& src)
{
	for (int num : src)
		cout << num << " ";
	cout << endl;
}

void input_arr(vector<int>& src)
{
	size_t n;
	cout << "Введите количесто элементов массива: "; cin >> n;
	cout << "Введите массив из " << n << " элементов: ";
	int elem;
	for (size_t i = 0; i < n; i++)
	{
		cin >> elem;
		src.push_back(elem);
	}
}

void randomArr(vector<int>& src)
{
	for (size_t i = 0; i < src.size(); i++)
		src[i] = rand() % 5000;
}

void beadSort(vector<int>& src)
{
	size_t n = src.size();
	vector<int> res;
	int max_elem = *max_element(src.begin(), src.end());
	vector<int> transposedArr(max_elem, 0);

	for (size_t i = 0; i < n; i++)
		for (int j = 0; j < src[i]; j++)
			transposedArr[j]++;

	for (size_t i = n; i > 0; i--)
	{
		int tmp = 0;
		for (int j : transposedArr)
			tmp += (j >= static_cast<int>(i));
		res.push_back(tmp);
	}
	src = res;
}

void radixSort(vector<int>& src)
{
	size_t n = src.size();
	int max_elem = *max_element(src.begin(), src.end());
	vector<int> res(n, 0);

	for (int place = 1; max_elem / place > 0; place *= 10)
	{
		vector<int> cnt(10, 0);
		for (int num : src)
			cnt[(num / place) % 10]++;

		for (size_t i = 1; i < 10; i++)
			cnt[i] += cnt[i - 1];

		for (int i = n - 1; i >= 0; i--)
		{
			res[cnt[(src[i] / place) % 10] - 1] = src[i];
			cnt[(src[i] / place) % 10]--;
		}
		src = res;
	}
}

Node::Node()
{
	data = 0;
	left = nullptr;
	right = nullptr;
}

Node::Node(int val)
{
	data = val;
	left = nullptr;
	right = nullptr;
}

Node* Node::insert(Node* root, const int& data)
{
	if (!root)
		return new Node(data);
	if (data > root->data)
		root->right = insert(root->right, data);
	else if (data < root->data)
		root->left = insert(root->left, data);
	return root;
}

void Node::inOrder(Node* root, vector<int>& arr)
{
	if (!root)
		return;
	inOrder(root->left, arr);
	arr.push_back(root->data);
	inOrder(root->right, arr);
}

void binarySort(vector<int>& src)
{
	size_t n = src.size();
	vector<int> res;
	Node tree;
	Node* root = nullptr;
	root = tree.insert(root, src[0]);
	for (size_t i = 1; i < n; i++)
		tree.insert(root, src[i]);
	tree.inOrder(root, res);
	src = res;
}