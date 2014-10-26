#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

#define rep(i,n) for(int i = 0; i < (n); ++i)
#define forr(i,a,b) for(int i = (a); i <= (b); ++i)

typedef long long ll;

const int N = 100111;
int x[N], y[N];
int ix[N], iy[N];

struct Xcmp
{
    bool operator()(int l, int r)
    {
        return x[l] < x[r];
    }
} xcmp;

struct Ycmp
{
    bool operator()(int l, int r)
    {
        return y[l] < y[r];
    }
} ycmp;

int badi[5];
int badn;


int solve(int n)
{
    if (n <= 4)
        return 0;

    rep(i,n) {
        ix[i] = i;
        iy[i] = i;
    }

    sort(ix, ix + n, xcmp);
    sort(iy, iy + n, ycmp);

    int ans = 1 << 30;
    rep(c, 64) {
        int ixmin = 0, ixmax = n-1, iymin = 0, iymax = n-1;
        badn = 0;
        int code = c;
        rep(j, 3)
        {
            switch(code&3)
            {
            case 0: // left
                badi[badn] = ix[ixmin++];
                break;
            case 1: // right
                badi[badn] = ix[ixmax--];
                break;
            case 2: // down
                badi[badn] = iy[iymin++];
                break;
            case 3: // up
                badi[badn] = iy[iymax--];
                break;
            }
            badn++;

            rep(k,badn)
            {
                if (badi[k] == ix[ixmin])
                    ixmin++;
                if (badi[k] == ix[ixmax])
                    ixmax--;
                if (badi[k] == iy[iymin])
                    iymin++;
                if (badi[k] == iy[iymax])
                    iymax--;
            }

            code >>= 2;
        }

        int side = max(x[ix[ixmax]] - x[ix[ixmin]], y[iy[iymax]] - y[iy[iymin]]);
        if (side < ans)
            ans = side;
    }

    return ans;
}

int main()
{
    int C;
    cin >> C;
    int n;
    rep(c, C)
    {
        cin >> n;
        rep(i,n) {
            cin >> x[i] >> y[i];
        }
        
        int ans = solve(n);

        cout << "Case #" << c + 1 << "\n";
        cout << ans << "\n";
    }
    return 0;
}