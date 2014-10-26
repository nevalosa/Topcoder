#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string>
#include <stack>

using namespace std;

int main()
{
	//freopen("e:/input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	for(int t=1; t<=T; ++t)
	{
		int N; cin>>N;

		vector<pair<int, int> > a(N);
		for(int i=0; i<N; ++i)
		{
			cin>>a[i].first>>a[i].second;
		}

		int left = a[0].first, right = a[0].first;
		int top = a[0].second, bottom = a[0].second;

		for(int i=1; i<N; ++i)
		{
			left = min(left, a[i].first);
			right = max(right, a[i].first);
			top = min(top, a[i].second);
			bottom = max(bottom, a[i].second);
		}

		int LM = 0, RM = 0;


		for(int i=0; i<N; ++i)
		{
			int x = a[i].first, y = a[i].second;

			int ld = min(max(x - left, y-top), max(right-x, bottom-y));
			int rd = min(max(right - x, y-top), max(x-left, bottom-y));

			LM = max(LM, ld);
			RM = max(RM, rd);
		}

		cout<<"Case #"<<t<<endl<<min(LM, RM)<<endl;
	}
	

	return 0;
}