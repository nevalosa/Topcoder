#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;


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


int badn;
int badi[N];

int solve(int n, int k)
{
    if (n <= k)
        return 0;

    
    for(int i = 0; i < n; ++i) {
        ix[i] = i;
        iy[i] = i;
    }

    sort(ix, ix + n, xcmp);
    sort(iy, iy + n, ycmp);

    int ans = 1 << 30;
    
    
    for(int c = 0; c < 64; ++c){
        int ixmin = 0, ixmax = n-1, iymin = 0, iymax = n-1;
        badn = 0;
        int code = c;
        for(int j = 0; j < k; ++j)
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

            for(int b = 0; b < badn; ++b)
            {
                if (badi[b] == ix[ixmin])
                    ixmin++;
                if (badi[b] == ix[ixmax])
                    ixmax--;
                if (badi[b] == iy[iymin])
                    iymin++;
                if (badi[b] == iy[iymax])
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
    int k;
    for(int c = 0; c < C; ++c)
    {
        cin >> n;
        cin >> k;

        for(int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        
        if( k > 5000){
            cout << "Case #" << c + 1 << "\n";
            cout << 0 << "\n";
            continue;
        }
        
        int ans = solve(n, k);

        cout << "Case #" << c + 1 << "\n";
        cout << ans << "\n";
    }
    return 0;
}