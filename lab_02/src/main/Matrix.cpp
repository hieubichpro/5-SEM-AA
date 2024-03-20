#include "Matrix.h"

ostream& operator<<(ostream& out, const Matrix& m)
{
	for (size_t i = 0; i < m.arr.size(); i++)
	{
		for (size_t j = 0; j < m.arr[0].size(); j++)
			out << m.arr[i][j] << " ";
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, Matrix& m)
{
	size_t r, c;
	cout << "Введите количество строк: "; cin >> r;
	cout << "Введите количество столбцов: "; cin >> c;
	m = Matrix(r, c);
	for (size_t i = 0; i < r; i++)
		for (size_t j = 0; j < c; j++)
			cin >> m.arr[i][j];
	return in;
}

Matrix::Matrix()
{
	arr = { {} };
}

Matrix::Matrix(size_t r, size_t c)
{	
	vector<vector<int>> tmp(r, vector<int>(c, 0));
	arr = tmp;
}
Matrix::~Matrix()
{}

Matrix::Matrix(initializer_list<initializer_list<int> > lst)
{
	for (const auto& row : lst)
	{
		arr.emplace_back(row);
	}
}

Matrix& Matrix::operator=(std::initializer_list<initializer_list<int> > lst)
{
	Matrix tmp(lst);
	*this = tmp;
	return *this;
}

void Matrix::randomMatrix()
{
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < arr.size(); i++)
		for (size_t j = 0; j < arr[0].size(); j++)
			arr[i][j] = rand() % 10;
}
Matrix Matrix::standartMul(Matrix& m)
{
	size_t a = arr.size();
	size_t b = arr[0].size();
	size_t c = m.arr[0].size();

	Matrix res(a, c);

	for (size_t i = 0; i < a; i++)
		for (size_t j = 0; j < c; j++)
			for (size_t k = 0; k < b; k++)
				res.arr[i][j] = res.arr[i][j] + arr[i][k] * m.arr[k][j];
	return res;
}

Matrix Matrix::vinogradMul(Matrix& m)
{
	size_t a = arr.size();
	size_t b = arr[0].size();
	size_t c = m.arr[0].size();

	Matrix res(a, c);
	vector<int> mulH(a, 0);
	vector<int> mulV(c, 0);

	size_t d = b / 2;
	for (size_t i = 0; i < a; i++)
		for (size_t j = 0; j < d; j++)
			mulH[i] = mulH[i] + arr[i][2 * j] * arr[i][2 * j + 1];

	for (size_t i = 0; i < c; i++)
		for (size_t j = 0; j < d; j++)
			mulV[i] = mulV[i] + m.arr[2 * j][i] * m.arr[2 * j + 1][i];

	for (size_t i = 0; i < a; i++)
		for (size_t j = 0; j < c; j++)
		{
			res.arr[i][j] = res.arr[i][j] - mulH[i] - mulV[j];
			for (size_t k = 0; k < d; k++)
				res.arr[i][j] = res.arr[i][j] + (arr[i][2 * k] + m.arr[2 * k + 1][j]) * \
				(arr[i][2 * k + 1] + m.arr[2 * k][j]);
		}

	if (b % 2)
	{
		for (size_t i = 0; i < a; i++)
			for (size_t j = 0; j < c; j++)
				res.arr[i][j] = res.arr[i][j] + arr[i][b - 1] * m.arr[b - 1][j];
	}

	return res;
}

Matrix Matrix::optVinogradMul(Matrix& m)
{
	size_t a = arr.size();
	size_t b = arr[0].size();
	size_t c = m.arr[0].size();

	Matrix res(a, c);
	vector<int> mulH(a, 0);
	vector<int> mulV(c, 0);

	size_t d = b / 2;
	int tmp;
	for (size_t i = 0; i < a; i++)
		for (size_t j = 0; j < d; j++)
			mulH[i] += arr[i][j << 1] * arr[i][(j << 1) + 1];

	for (size_t i = 0; i < c; i++)
		for (size_t j = 0; j < d; j++)
			mulV[i] += m.arr[j << 1][i] * m.arr[(j << 1) + 1][i];

	for (size_t i = 0; i < a; i++)
	{
		tmp = mulH[i];
		for (size_t j = 0; j < c; j++)
		{
			res.arr[i][j] -= (tmp + mulV[j]);
			for (size_t k = 0; k < d; k++)
				res.arr[i][j] += (arr[i][k << 1] + m.arr[(k << 1) + 1][j]) * \
				(arr[i][(k << 1) + 1] + m.arr[k << 1][j]);
		}
	}

	if (b % 2)
	{
		for (size_t i = 0; i < a; i++)
		{
			tmp = arr[i][b - 1];
			for (size_t j = 0; j < c; j++)
				res.arr[i][j] += tmp * m.arr[b - 1][j];
		}
	}

	return res;
}