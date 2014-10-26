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

struct Edge
{
    int a, b, c;
    Edge() {}
    Edge(int aA, int aB, int aC):a(aA), b(aB), c(aC) {}
    ~Edge() {}
    bool operator < (const Edge & other) const { return c<other.c; }
};

class TreeGraph
{
    vector<vector<pair<int, int> > > data; // first - length, second - where to
    int linkedVertexes;
public:
    TreeGraph(int aSize): data(aSize), linkedVertexes(1) {}
    ~TreeGraph(){}

//    void print() const
//    {
//        cout<<"----------------------\n";
//        cout<<linkedVertexes<<endl;
//        for(int i=0; i<data.size(); ++i)
//        {
//            for(int k=0; k<data[i].size(); ++k)
//            {
//                if(data[i][k].second<i)
//                    cout<<i<<" -- "<<data[i][k].second<<" == "<<data[i][k].first<<endl;
//            }
//        }
//        cout<<"[[----------------------]]\n";
//    }
//
    int getDifference() const
    {
        int dMax = -1, dMin = 1000000000;
        for(int i=0; i<data.size(); ++i)
        {
            for(int k=0; k<data[i].size(); ++k)
            {
                int xx = data[i][k].first;
                if(dMax<xx)dMax = xx;
                if(dMin>xx)dMin = xx;
            }
        }
        return dMax - dMin;
    }
    bool isTree() const {return linkedVertexes==data.size();}

    bool hasCycle(int startEdge, int curEdge, int prevEdge, Edge & best)
    {
        for(int i=0; i<data[curEdge].size(); ++i)
        {
            const pair<int, int> & s = data[curEdge][i];
            if(s.second!=prevEdge)
            {
                if((s.second == startEdge) || hasCycle(startEdge, s.second, curEdge, best))
                {
                    Edge cycleEdge(curEdge, s.second, s.first);
                    if(cycleEdge<best)best = cycleEdge;
                    return true;
                }
            }
        }
        return false;
    }

    void del(int from, const pair<int, int> & what)
    {
        for(int i=0; i<data[from].size(); ++i)
        {
            if(data[from][i]==what)
            {
                swap(data[from][i], data[from].back());
                data[from].pop_back();
                return;
            }
        }
    }

    void eraseEdge(const Edge & edge)
    {
        del(edge.a, make_pair(edge.c, edge.b));
        del(edge.b, make_pair(edge.c, edge.a));
    }

    void add(const Edge & edge)
    {
        data[edge.a].push_back(make_pair(edge.c, edge.b));
        data[edge.b].push_back(make_pair(edge.c, edge.a));

        // find cycle from a-b
        Edge best = edge;
        if(hasCycle(edge.a, edge.b, edge.a, best))
        {
            eraseEdge(best);
            // delete best
        }
        else
        {
            ++linkedVertexes;
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(0);
//    freopen("/home/a-grigoriev/workspace/input.txt", "rt", stdin);

    int testCasesCount;
    cin>>testCasesCount;

    for(int testCase = 1; testCase<=testCasesCount; ++testCase)
    {
        int n, m; cin >> n >> m;
        vector<Edge> graph; graph.reserve(m);

        for(int i=0; i<m; ++i)
        {
            int a, b, c;
            cin>>a>>b>>c;
            --a; --b;
            graph.push_back(Edge(a, b, c));
        }

        sort(graph.begin(), graph.end());
        TreeGraph tg(n);

        int edgeIndex = 0;
//        tg.print();
        for(; !tg.isTree(); ++edgeIndex)
        {
            tg.add(graph[edgeIndex]);
//            tg.print();
        }
        int best = tg.getDifference();
        for(; edgeIndex<graph.size(); ++edgeIndex)
        {
//            cout<<"here\n";
            tg.add(graph[edgeIndex]);
//            tg.print();
            int newDif = tg.getDifference();
            if(newDif<best)best = newDif;
        }
        cout<<"Case #"<<testCase<<endl;
        cout<<best<<endl;
    }

    return 0;
}
