#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define forr(i,a,b) for(int i = (a); i <= (b); ++i)

typedef long long ll;

const int N = 100111;
int pos[N];
char snd[N], trd[N];

int other(int a, int b)
{
    return /*1 ^ 2 ^ 3 ^*/ a ^ b;
}

bool number(int n, const int* pos, char *num)
{
    int from = 1, to = 2;
    rep(i,n)
    {
        if (pos[i] == from)
        {
            num[i] = 0;
            to = other(from, to);
        }
        else if (pos[i] == to)
        {
            num[i] = 1;
            from = other(from, to);
        }
        else
            return false;
    }
    return true;
}

bool isless(int n, const char* l, const char* r)
{
    int i = 0;
    while (i < n && l[i] == r[i])
        ++i;
    return l[i] < r[i];
}

int main()
{
    int C;
    cin >> C;
    int n;
    int d;
    rep(c, C)
    {
        cin >> n;
        rep(i,n) {
            cin >> pos[i];
        }
        bool good2nd = number(n, pos, snd);
        rep(i,n) {
            cin >> pos[i];
        }
        bool good3rd = number(n, pos, trd);
        bool less23 = isless(n, snd, trd);

        cout << "Case #" << c + 1 << "\n";
        cout << int(good2nd && good3rd && less23) << "\n";
    }
    return 0;
}