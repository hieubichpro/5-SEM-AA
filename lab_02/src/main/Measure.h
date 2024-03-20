#pragma once
#include <fstream>
#include "Matrix.h"
#define TIMES 20
#define END_RANGE 100
#define STEP 10
double getProcessTime(Matrix(Matrix::* mul)(Matrix& m), size_t n);
void timeTest(bool isEven);
size_t getMemory(size_t r, size_t c, string algo);
void memoryTest();