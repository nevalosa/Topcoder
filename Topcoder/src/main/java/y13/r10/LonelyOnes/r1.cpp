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

void solve(const string & in)
{
	int len = in.length();
	vector<int> a(len + 20); a[0] = len;
	for(int i=1; i<len-2; ++i) a[i] = len-i-2;
	for(int i=1; i<len; ++i) if(in[i]=='0' && in[i+1]=='1')++a[0];
	for(int i=len-2, j=0; i>0; --i, ++j) a[j] += (in[i]=='1');

	if(len>2)
		if(in[1]=='0') for(int i=len-1, j=0; i>0; --i, ++j)a[j]+=(in[i]=='1');
		else ++a[len-2], --a[0];

	for(int i=0; i<(int)a.size()-1; ++i){int c = a[i]>>1; a[i]&=1; a[i+1]+=c;}
	while(a.back()==0)a.pop_back();
	for(int i=a.size()-1; i>=0; --i)cout<<a[i];
	cout<<endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int TEST_COUNT; cin>>TEST_COUNT;

	for(int t=1; t<=TEST_COUNT; ++t)
	{
		string s; cin>>s;
		cout<<"Case #"<<t<<endl; solve(s);
	}

	return 0;
}
