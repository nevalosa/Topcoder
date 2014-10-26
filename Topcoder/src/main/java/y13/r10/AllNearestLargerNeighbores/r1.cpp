#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

void solve(const vector<int> & a, vector<int> & answer)
{
	int N = (int)a.size();
	int LEFT_INF = -N, RIGHT_INF = 2*N;
	
	vector<int> left(N);
	vector<int> right(N);

	vector<int> s;
	for(int i=0; i<N; ++i)
	{
		while(s.size() && a[s.back()]<a[i])
		{
			right[s.back()]=i;
			s.pop_back();
		}
		s.push_back(i);
	}
	while(s.size())
	{
		right[s.back()] = RIGHT_INF;
		s.pop_back();
	}

	for(int i=N-1; i>=0; --i)
	{
		while(s.size() && a[s.back()]<a[i])
		{
			left[s.back()]=i;
			s.pop_back();
		}
		s.push_back(i);
	}
	while(s.size())
	{
		left[s.back()] = LEFT_INF;
		s.pop_back();
	}

	for(int i=0; i<N; ++i)
	{
		int toLeft = i-left[i], toRight = right[i]-i;
		answer.push_back( ((toLeft>toRight)?right[i]:left[i]) );
	}
}

int main()
{
	ios_base::sync_with_stdio(false);

	int TEST_COUNT; cin>>TEST_COUNT;

	for(int t=1; t<=TEST_COUNT; ++t)
	{
		int N; cin>>N; vector<int> a(N), b;
		for(int i=0; i<N; ++i)cin>>a[i];

		solve(a, b);

		cout<<"Case #"<<t<<endl;
		for(int i=0; i<N; ++i)
			cout<<b[i]<<" ";
		cout<<endl;
	}

	return 0;
}
