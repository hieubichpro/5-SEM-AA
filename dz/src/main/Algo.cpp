#include "Algo.h"
mutex m_lps, m_res;

void computeLPSArray(string pattern, vector<int>& lps)
{
	int n = lps.size(); //1
	int len = 0; //2
	int i = 1; //3
	cout << "start cycle" << endl; //4
	while (i < n) //5
	{
		if (pattern[i] == pattern[len]) //6
		{
			len++; //7
			lps[i] = len; //8
			i++; //9
		}
		else //10
		{
			if (len != 0) //11
				len = lps[len - 1]; //12
			else //13
			{
				lps[i] = len; //14
				i++; //15
			}
		}
	}
}

vector<int> algoKMP(string text, string pattern)
{
	int n = text.size(), m = pattern.size();
	vector<int> lps(m, 0);
	int i = 0, j = 0;
	computeLPSArray(pattern, lps);
	vector<int> res;
	while ((n - i) >= (m - j))
	{
		if (pattern[j] == text[i])
		{
			i++;
			j++;
		}
		if (j == m)
		{
			res.push_back(i - j);
			j = lps[j - 1];
		}
		else if (i < n && pattern[j] != text[i])
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i += 1;
		}
	}
	return res;
}

void kmpSearch(int start, int end, string& pattern, string& text, vector<int>& res, vector<int> &lps)
{
	int n = end, m = pattern.size();
	int i = start, j = 0;

	while ((n - i) >= (m - j))
	{
		if (pattern[j] == text[i])
		{
			i++;
			j++;
		}
		if (j == m)
		{
			m_res.lock();
			res.push_back(i - j);
			m_res.unlock();

			m_lps.lock();
			j = lps[j - 1];
			m_lps.unlock();
		}
		else if (i < n && pattern[j] != text[i])
		{
			if (j != 0)
			{
				m_lps.lock();
				j = lps[j - 1];
				m_lps.unlock();
			}
			else
				i += 1;
		}
	}
}

vector<int> parallelKMP(string text, string pattern, int k)
{
	vector<int> res;
	int n = text.size(), m = pattern.size();
	vector<int> lps(m, 0);
	computeLPSArray(pattern, lps);
	vector<thread> threads_1;
	int segmentSize = n / k;
	int start, end;
	for (int i = 0; i < k; i++)
	{
		start = i * segmentSize;
		end = (i == k - 1) ? n : (i + 1) * segmentSize;
		threads_1.emplace_back(kmpSearch, start, end, ref(pattern), ref(text), ref(res), ref(lps));
	}
	for (auto& th : threads_1)
		th.join();
	vector<thread> threads_2;
	for (int i = 1; i <= k - 1; i++)
	{
		start = i * segmentSize - (m - 1);
		end = i * segmentSize + (m - 1);
		threads_2.emplace_back(kmpSearch, start, end, ref(pattern), ref(text), ref(res), ref(lps));
	}
	for (auto& th : threads_2)
		th.join();
	return res;
}
