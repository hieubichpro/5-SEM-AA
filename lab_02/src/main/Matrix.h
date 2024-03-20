#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Matrix
{
private:
	vector<vector<int>> arr;
public:
	Matrix();
	Matrix(size_t r, size_t c);
	~Matrix();
	Matrix(initializer_list<initializer_list<int> > lst);
	Matrix& operator=(std::initializer_list<initializer_list<int> > lst);
	friend ostream& operator<<(ostream& out, const Matrix& m);
	friend istream& operator>>(istream& in, Matrix& m);
	void randomMatrix();

	Matrix standartMul(Matrix& m);
	Matrix vinogradMul(Matrix& m);
	Matrix optVinogradMul(Matrix& m);
};

ostream& operator<<(ostream& out, const Matrix& m);
istream& operator>>(istream& in, Matrix& m);