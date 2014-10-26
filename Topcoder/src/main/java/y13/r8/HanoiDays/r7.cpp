/*
 * grafs.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: a-grigoriev
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <stdio.h>

using namespace std;

int cmp(vector<int> & a, vector<int> & b)
{
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]<b[i]) return 1;
        else if(a[i]>b[i]) return 0;
    }
    return 1;
}

void convert(vector<int> & a, vector<int> & aa)
{
    const int d[3][3] = {{1,3,2}, {3,2,1}, {2,1,3}};
    int left=1, right=2;

    for (int i=0; i<a.size(); i++)
    {
        int x = (a[i]!=left);
        if(x) left=d[left-1][right-1];
        else right=d[left-1][right-1];
        aa[i]=x+1;
    }
}

int answer(vector<int> & a, vector<int> & b)
{
    vector<int> aa(a.size()), bb(a.size());
    if( (a[0]==3) || (b[0]==3) )return 0;
    convert(a, aa);
    convert(b, bb);
    return cmp(aa, bb);
}

int main()
{
    std::ios_base::sync_with_stdio(0);
//    freopen("/home/a-grigoriev/workspace/input.txt", "rt", stdin);

    int testCasesCount;
    cin>>testCasesCount;

    for(int testCase = 1; testCase<=testCasesCount; ++testCase)
    {
        int n; cin>>n;
        vector<int> a(n), b(n);
        for(int i=0; i<n; ++i)cin>>a[i];
        for(int i=0; i<n; ++i)cin>>b[i];
        cout<<"Case #"<<testCase<<endl;
        cout<<answer(a, b)<<endl;
    }

    return 0;
}
