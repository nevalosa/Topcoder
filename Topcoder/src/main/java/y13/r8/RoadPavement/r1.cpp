#include <iostream>
//#include <algorithm>
#include <cstdlib>

using namespace std;

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define forr(i,a,b) for(int i = (a); i <= (b); ++i)

typedef long long ll;

struct road_
{
    int a,b,c;

    /*bool operator<(const road_& r)
    {
        return c < r.c;
    }*/
};

int compare(const void* l, const void* r)
{
    return ( ((road_*)l)->c - ((road_*)r)->c );
}

struct road_Cmp
{
    bool operator()(const road_& l, const road_& r)
    {
        return l.c < r.c;
    }
} roadCmp;

const int N = 355;
const int MAX_M = N * N / 2;
road_ roads[MAX_M];

int prnt[N];
int rnk[N];
int cc;

int _find(int a)
{
    if (prnt[a] == a)
        return a;

    int pa = _find(prnt[a]);
    prnt[a] = pa;
    return pa;
}

void _union(int a, int b)
{
    int pa = _find(a);
    int pb = _find(b);
    if (pa != pb)
    {
        --cc;
        if (rnk[pa] < rnk[pb])
            prnt[pa] = pb;
        else if (rnk[pa] > rnk[pb])
            prnt[pb] = pa;
        else {
            prnt[pa] = pb;
            rnk[pb]++;
        }
    }
}

void _reset(int n)
{
    forr(i,1,n)
    {
        prnt[i] = i;
        rnk[i] = 0;
    }
    cc = n;
}

void _add(int i)
{
    _union(roads[i].a, roads[i].b);
}

int solve(int n, int m)
{
    //sort(roads, roads + m, roadCmp);
    qsort(roads, m, sizeof(road_), compare);
    _reset(n);
    int mi = m - 1;
    do {
        _add(mi);
    } while (cc > 1 && --mi >= 0);

    int ans = roads[m - 1].c - roads[mi].c;

    for (int i = 0; i <= mi; )
    {
        _reset(n);
        int j = i;
        do {
            _add(j++);
        } while (cc > 1);
        --j;

        if (ans > roads[j].c - roads[i].c)
            ans = roads[j].c - roads[i].c;

        _reset(n);
        int ii = j;
        do {
            _add(ii--);
        } while (cc > 1);
        ++ii;

        if (ans > roads[j].c - roads[ii].c)
            ans = roads[j].c - roads[ii].c;

        if (ii <= i)
            ++i;
        else
            i = ii;
    }

    return ans;
}

int main()
{
    int C;
    cin >> C;
    int n,m;
    int d;
    rep(c, C)
    {
        cin >> n >> m;
        rep(i,m) {
            cin >> roads[i].a >> roads[i].b >> roads[i].c;
        }

        int ans = 0;

   //     if (m < 10000)
            ans = solve(n, m);

        cout << "Case #" << c + 1 << "\n";
        cout << ans << "\n";
    }
    return 0;
}