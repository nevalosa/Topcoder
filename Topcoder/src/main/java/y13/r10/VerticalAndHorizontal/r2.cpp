#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;

enum ComponentType { XTYPE, YTYPE, BOTH };

void addConnections(vector<pair<int, int> >& connections, vector<pair<int, int> >& ind, bool isx)
{
	sort(ind.begin(), ind.end());
	int n = connections.size();
	for (int i = 1, u, v; i < n; )
	{
		if (ind[i-1].first == ind[i].first)
		{			
			u = ind[i-1].second, v = ind[i].second;
			if (isx)
				connections[u].first = v, connections[v].first = u;
			else
				connections[u].second = v, connections[v].second = u;			
			i += 2;
		}
		else
			++i;
	}
}

bool findConnections(vector<pair<int, int> >&a, vector<pair<int, int> >& connections)
{	
	int n = a.size();
	connections.resize(n);
	for (int i = 0; i < n; ++i) 
		connections[i].first = -1, connections[i].second = -1;
	vector<pair<int, int> > ind(n);
	for (int i = 0; i < n; ++i) // x
		ind[i].first = a[i].first, ind[i].second = i;	
	addConnections(connections, ind, true);
	for (int i = 0; i < n; ++i) // y
		ind[i].first = a[i].second, ind[i].second = i;	
	addConnections(connections, ind, false);	
	for (int i = 0; i < n; ++i)
		if (connections[i].first == -1 && connections[i].second == -1) // outlier
			return false;
	return true;
}

int traverseComponent(vector<pair<int, int> >& connections, vector<bool>& seen, vector<int>& component, int start)
{
	seen[start] = true;
	int t = start;	
	while (1)
	{
		component.push_back(t);
		int next = connections[t].first;
		if (next == -1 || seen[next])
		{
			next = connections[t].second;
			if (next == -1 || seen[next])
				return t;
		}
		seen[next] = true;
		t = next;
	}
}

vector<int> component;
bool findComponents(vector<pair<int, int> >& connections, vector<int>& v2c, vector<int>& compType)
{
	int n = connections.size();
	v2c.resize(n);
	compType.clear();
	vector<bool> seen(n, false);	
	for (int i = 0, nc = 0; i < n; ++i) // DFS
	{
		if (seen[i])
			continue;
		seen[i] = true;
		component.clear();
		component.push_back(i);
		if (connections[i].first >= 0)
			traverseComponent(connections, seen, component, connections[i].first);
		if (connections[i].second >= 0 && seen[connections[i].second]) // circle
			compType.push_back(BOTH);
		else // path
		{
			int start;
			if (connections[i].second >= 0)
				start = traverseComponent(connections, seen, component, connections[i].second);			
			else
				start = i;
			if (connections[start].first >= 0)
				compType.push_back(XTYPE);
			else
				compType.push_back(YTYPE);
		}
		if (component.size()&1)
				return false;
		for (int i = 0; i < component.size(); ++i)
			v2c[component[i]] = nc;
		++nc;
	}
	return true;
}

bool findComponentConnections(vector<pair<int, int> >&a, vector<pair<int, int> >& connections, vector<int>& v2c, vector<int>& compType, vector<vector<pair<int, int> > >& compConn)
{
	vector<pair<int, int > > X;
	vector<pair<int, int > > Y;
	compConn.clear();
	int n = a.size();
	compConn.resize(compType.size());
	for (int i = 0; i < n; ++i)
	{
		int u = connections[i].first;
		if (u > i)
			X.push_back(make_pair(a[i].first, i));
		u = connections[i].second;
		if (u > i)
			Y.push_back(make_pair(a[i].second, i));		
	}
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());

	for (int i = 0; i < n; ++i)
	{
		if (connections[i].first >= 0)
		{
			int u = connections[i].first;
			int nci = v2c[i];
			if (compType[nci] == YTYPE)
				continue; // this edge will not be in match anyway
			int x = a[i].first;
			int y1 = a[i].second, y2 = a[u].second;
			if (y1 > y2)
				swap(y1, y2);
			vector<pair<int, int> >::iterator beg = lower_bound(Y.begin(), Y.end(), make_pair(y1+1, -500000)), end = lower_bound(Y.begin(), Y.end(), make_pair(y2, -500000));
			if (beg >= end)
				continue;
			for (vector<pair<int, int> >::iterator it = beg; it != end; ++it)
			{
				int s = it->second;
				int t = connections[s].second;
				int nc = v2c[s];	
				if (compType[nc] == XTYPE)
					continue; // this edge will not be in match anyway
				int x1 = a[s].first, x2 = a[t].first;
				if (x1 > x2)
					swap(x1, x2);
				if (x > x1 && x < x2) // intersection
				{
					if (compType[nci] == XTYPE && compType[nc] == YTYPE)
						return false;
					compConn[nci].push_back(make_pair(nc, XTYPE));
					compConn[nc].push_back(make_pair(nc, YTYPE));
				}
			}
		}
	}
	return true;
}


vector<pair<int, int> > connections;
vector<int> v2c;
vector<int> compType;
vector<vector<pair<int, int> > > compConn;
bool matchExist(vector<pair<int, int> >&a)
{
	if (!findConnections(a, connections))
		return false;
	if (!findComponents(connections, v2c, compType))
		return false;
	if (!findComponentConnections(a, connections, v2c, compType, compConn))
		return false;
	return true;
}

int main()
{
	int N;
	cin>>N;		
	string s;
	vector<pair<int, int> >a;
	a.reserve(3000);
	for (int z = 0, M; z < N; ++z)
	{
		cin>>M;
		a.resize(M);
		for (int i = 0; i < M; ++i)
			cin>>a[i].first>>a[i].second;
		cout<<"Case #"<<(z+1)<<endl;		
		cout<<(matchExist(a) ? "YES" : "NO")<<endl;
	}
	return 0;
}

