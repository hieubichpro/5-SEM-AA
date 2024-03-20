#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
void computeLPSArray(string pattern, vector<int>& lps);
vector<int> algoKMP(string text, string pattern);
void kmpSearch(int start, int end, string& pattern, string& text, vector<int>& res, vector<int>& lps);
vector<int> parallelKMP(string text, string pattern, int k);