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
//	freopen("e:/input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	for(int t=1; t<=T; ++t)
	{
		long long result = 0;
		long long sum = 0;
		int N, P;
		cin>>N>>P;
		vector<long long> hysto(P);
		hysto[0]=1;
		for(int i=0; i<N; ++i)
		{
			long long x;
			cin>>x;
			sum = (sum + x) % P;
			result += hysto[sum];
			++hysto[sum];
		}

		cout<<"Case #"<<t<<endl<<result<<endl;
	}
	

	return 0;
}