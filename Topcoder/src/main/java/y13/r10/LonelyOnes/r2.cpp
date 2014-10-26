#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;

void substract(vector<short>& x, int s)
{
	short p = 0;
	int i = 0;
	while (s || p )
	{
		int t = s&1;
		x[i] -= t+p;
		if (x[i] < 0)
		{
			x[i] += 2;
			p = 1;
		}
		else
			p = 0;
		s >>=1;
		++i;
	}
}

int number01(string &s)
{
	int res = 1;
	for (int i = 1; i < s.size(); ++i)
		if (s[i] == '1' && s[i-1] == '0')
			++res;
	return res;
}

void calcLonelyOnes(string& s, vector<short> &res)
{
	if (s == "1")
	{
		res.resize(1);
		res[0] = 1;
		return;
	}
	int n = s.size();
	int sub = n - number01(s);
	res.resize(n);
	for (int i = 0; i < n-1; ++i)
		res[i] = s[n-2-i] - '0';
	if (s[1] == '1')
		res[n-1] = 1;	
	else
	{		
		--sub;
		s[1] = '1';
		short p = 0;
		for (int i = 0; i < n-1; ++i)
		{
			res[i] += s[n-1-i] - '0' + p;
			if (res[i] > 1)
			{
				p = 1;
				res[i] -= 2;
			}
			else
				p = 0;
			res[n-1] = p;
		}
	}
	substract(res, sub);
}

void print(vector<short>& a)
{
	int n = a.size() - 1;
	while (a[n] == 0)
		--n;
	for (int i = n; i >= 0; --i)
		printf("%d", a[i]);
	printf("\n");
}

int main()
{
	int N;
	cin>>N;		
	string s;
	vector<short> res;
	s.reserve(1000000);
	res.reserve(1000001);
	for (int z = 0, M; z < N; ++z)
	{
		cin>>s;		
		calcLonelyOnes(s, res);
		cout<<"Case #"<<(z+1)<<endl;		
		print(res);
	}
	return 0;
}

