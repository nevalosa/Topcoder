#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

bool kuhn(const vector<vector<int> > & a,
		  vector<int> & mt,
		  int v, int happy)
{
	//if(used[v])return false;
	//used[v] = true;
	for(int i=0; i<a[v].size(); ++i)
	{
		int to = a[v][i];
		if(to!=-1)
		{
			if(mt[to]==v)break;

			if(mt[to]==-1 || kuhn(a, mt, mt[to], happy+1) || happy>=1)
			{
				mt[to] = v;
				return true;
			}
		}
	}
	return false;
}

int solve(vector<vector<int> > & a)
{
	vector<int> mt(a.size(), -1);

	for(int k=0; k<100; ++k)
	{
		bool good = true;
		for(int i=0; i<a.size(); ++i)
		{
			if(kuhn(a, mt, i, 0))
			{
				good = false;

						//for(int j=0; j<a.size(); ++j)
						//{
						//	cout<<j<< " <-> " <<mt[j]<<endl;
						//}
						//cout<<endl;
			}
		}

		if(good)return 1;

		//for(int i=0; i<a.size(); ++i)
		//{
		//	cout<<i<< " - " <<mt[i]<<endl;
		//}
		//cout<<endl;
	}

	return 0;
}
























int main()
{
	//freopen("e:/input.txt", "r", stdin);

	std::ios_base::sync_with_stdio(false);
	int T; cin>>T;

	for(int t=1; t<=T; ++t)
	{
		int N; cin>>N;
		vector<vector<int> > a(N);

		for(int i=0; i<N; ++i)
		{
			int K, M; cin>>K>>M; --K;
			for(int j=0; j<M; ++j)
			{
				int x; cin>>x; --x;
				a[K].push_back(x);
			}
			a[K].push_back(-1);
		}

		cout<<"Case #"<<t<<endl<<solve(a)<<endl;
	}

	return 0;
}