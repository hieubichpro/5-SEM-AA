#pragma once
#include "Algo.h"
#include <fstream>
#define END_RANGE 2500
#define STEP 250
#define TIMES 30
double getProcessTime(void (*algo)(vector<int>& m), vector<int>& arr);
void timeTest();
size_t getMemory();
size_t getMemoryBeadSort(vector<int>& arr);
size_t getMemoryRadixSort(vector<int>& arr);
size_t getMemoryBinarySort(vector<int>& arr);
void memoryTest();