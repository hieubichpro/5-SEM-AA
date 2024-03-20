#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void print_arr(const vector<int>& src);
void input_arr(vector<int>& src);
void beadSort(vector<int>& src);
void radixSort(vector<int>& src);
void randomArr(vector<int>& src);
class Node {
private:
    int data;
    Node* left;
    Node* right;

public:
    Node();
    Node(int val);
    Node* insert(Node *root, const int& data);
    void inOrder(Node* node, vector<int>& arr);
    friend void binarySort(vector<int>& src);
};

void binarySort(vector<int>& src);