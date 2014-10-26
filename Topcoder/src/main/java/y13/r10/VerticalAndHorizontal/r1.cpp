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

struct Point
{
	int x, y;
	Point():x(0), y(0){}
	Point(int aX, int aY):x(aX),y(aY){}
	~Point(){}
};

void numerate(map<int, int> & cmap)
{
	int i=0; for(map<int,int>::iterator ii=cmap.begin(); ii!=cmap.end(); ++ii)ii->second = i++;
}

Point elate(vector<Point> & a)
{
	map<int, int> xmap, ymap;
	for(int i=0; i<(int)a.size(); ++i) { xmap[a[i].x] = -1; ymap[a[i].y] = -1; }
	Point result(xmap.size(), ymap.size());
	numerate(xmap);	numerate(ymap);
	for(int i=0; i<(int)a.size(); ++i)a[i] = Point(xmap[a[i].x], ymap[a[i].y]);
	return result;
}

bool solve(vector<Point> & a)
{
	Point fieldSize = elate(a);
	vector<vector<int> > vx(fieldSize.x), vy(fieldSize.y);
	for(int i=0; i<(int)a.size(); ++i){ vx[a[i].x].push_back(i); vy[a[i].y].push_back(i); }
	
	vector<int> single;
	vector<int> adj(a.size());
	vector<char> used(a.size());

	for(int i=0; i<(int)vx.size(); ++i)
		if(vx[i].size()==2)
		{
			if(a[vx[i][0]].y>a[vx[i][1]].y)swap(vx[i][0], vx[i][1]);
			++adj[vx[i][0]]; ++adj[vx[i][1]];
		}
		else
		{
			single.push_back(vx[i][0]); vx[i].clear();
		}

	for(int i=0; i<(int)vy.size(); ++i)
		if(vy[i].size()==2)
		{
			if(a[vy[i][0]].x>a[vy[i][1]].x)swap(vy[i][0], vy[i][1]);
			++adj[vy[i][0]]; ++adj[vy[i][1]];
		}
		else
		{
			if(!adj[vy[i][0]])return false;
			single.push_back(vy[i][0]); vy[i].clear();
		}

	////////////////////////////////////////////////////////////////////////////////

	while(!single.empty())
	{
		int from = single.back(); single.pop_back();
		if(used[from])continue;
		used[from] = true;
		--adj[from];

		int x_from = a[from].x, y_from = a[from].y;
		if(vx[x_from].size())
		{
			// use vertical
			int to = vx[x_from][0];
			if(to==from)to=vx[x_from][1];
			used[to] = true;
			--adj[to];
			int y1 = a[from].y, y2 = a[to].y;
			if(y1>y2)swap(y1, y2);
			for(int y=y1+1; y<y2; ++y)
			{
				if(vy[y].size()==2)
				{
					int n1 = vy[y][0], n2 = vy[y][1];
					if(a[n1].x<x_from && a[n2].x>x_from)
					{
						--adj[n1], --adj[n2];
						if(!adj[n1] || !adj[n2])return false;
						single.push_back(n1);
						single.push_back(n2);
						vy[y].clear();
					}
				}
			}

			vx[x_from].clear();

			if(adj[to]==1)
			{
				int to_to = vy[a[to].y][0];
				if(to_to == to)to_to = vy[a[to].y][1];
				--adj[to_to];
				vy[a[to].y].clear();
				if(adj[to_to]==0)return false;
			}
		}
		else
		{
			// use horyzontal
			int to = vy[y_from][0];
			if(to==from)to=vy[y_from][1];
			used[to] = true;
			--adj[to];
			int x1 = a[from].x, x2 = a[to].x;
			if(x1>x2)swap(x1, x2);
			for(int x=x1+1; x<x2; ++x)
			{
				if(vx[x].size()==2)
				{
					int n1 = vx[x][0], n2 = vx[x][1];
					if(a[n1].y<y_from && a[n2].y>y_from)
					{
						--adj[n1], --adj[n2];
						if(!adj[n1] || !adj[n2])return false;
						single.push_back(n1);
						single.push_back(n2);
						vx[x].clear();
					}
				}
			}

			vy[y_from].clear();

			if(adj[to]==1)
			{
				int to_to = vx[a[to].x][0];
				if(to_to == to)to_to = vx[a[to].x][1];
				--adj[to_to];
				vx[a[to].x].clear();
				if(adj[to_to]==0)return false;
			}
		}
	}
	return true;
}


int main()
{
	ios_base::sync_with_stdio(false);

	int TEST_CASES; cin>>TEST_CASES;
	for(int t=1; t<=TEST_CASES; ++t)
	{
		int n; cin>>n;
		vector<Point> a(n);
		for(int i=0; i<n; ++i)cin>>a[i].x>>a[i].y;
	
		cout<<"Case #"<<t<<endl<<(solve(a)?"YES":"NO")<<endl;
	}

	return 0;
}
