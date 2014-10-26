#include <stack>
#include <vector>
#include <iostream>

using namespace std;

stack<pair<int, int> > s;

void calcRN(vector<int>&a, vector<int>& res)
{
	res.resize(a.size());
	int M = a.size();
	for (int i = 0; i < M; ++i)
	{
		int t = a[i];
		while (!s.empty() && s.top().first < t)
		{
			res[s.top().second] = i;
			s.pop();
		}
		s.push(make_pair(a[i], i));
	}
	while (!s.empty())
	{
		res[s.top().second] = 2*M;
		s.pop();
	}
}

void calcLN(vector<int>&a, vector<int>& res)
{
	res.resize(a.size());
	int M = a.size();
	for (int i = M-1; i >= 0; --i)
	{
		int t = a[i];
		while (!s.empty() && s.top().first < t)
		{
			res[s.top().second] = i;
			s.pop();
		}
		s.push(make_pair(a[i], i));
	}
	while (!s.empty())
	{
		res[s.top().second] = -M;
		s.pop();
	}
}


void nln(vector<int>&a, vector<int>& res, vector<int>& ln, vector<int>& rn)
{
	res.resize(a.size());
	calcRN(a, rn);
	calcLN(a, ln);
	int M = a.size();
	for (int i = 0; i < M; ++i)
	{
		int l = i - ln[i], r = rn[i] - i;
		res[i] = l <= r ? ln[i] : rn[i];
	}
}

int main()
{
	int N;
	cin>>N;
	vector<int> a, res, ln, rn;
	a.reserve(100000);
	res.reserve(100000);
	ln.reserve(100000);
	rn.reserve(100000);
	for (int z = 0, M; z < N; ++z)
	{
		cin>>M;
		a.resize(M);
		for (int i = 0; i < M; ++i)
			cin>>a[i];		
		nln(a, res, ln, rn);
		cout<<"Case #"<<(z+1)<<endl;
		for (int i = 0; i < M; ++i)
			cout<<(i > 0? " ": "" )<<res[i];
		cout<<endl;
	}
	return 0;
}


