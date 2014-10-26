#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
typedef map<int, int> mii;
typedef set<int> si;

class algorithm
{
public:
	bool test(vi &A, vi &B, ll v)
	{
		bool res = true;
		ll maxV = -1;
		ll s1 = 0, s2 = 0;
		ll cnt = 0;
		ll can = 0;
		for (int i = 0; i < A.size(); i++)
		{
			s1 = A[i] + s1;
			s2 = B[i] + s2;
			if (s1 > v)
			{
				int d = s1 - v;
				if (d > can)
				{
					return false;
				}
				else
				{
					can -= d;
					s1 -= d;
				}
			}

			if (s2 > v)
			{
				int d = s2 - v;
				if (d > can)
				{
					return false;
				}
				else
				{
					can -= d;
					s2 -= d;
				}
			}

			if ((s1 > 0)&&(s2==0))
			{
				s1 -= 1;
				if (s1 < 0)
					s1 = 0;
			}
			else if ((s2 > 0)&&(s1==0))
			{
				s2 -= 1;
				if (s2 < 0)
					s2 = 0;
			}
			else if ((s1>0)&&(s2>0))
			{
				can++;
			}

			ll mv = s1;

			if (mv > s2)
				mv = s2;

			if (can>mv)
			{
				if (mv == s1)
				{
					s2 = s2 - can + s1;
					can = s1;
					
					if (s2 < 0)
						s2 = 0;
				}
				else
				{
					s1 = s1 - can + s2;
					can = s2;
					if (s1 < 0) 
						s1 = 0;
				}
			}

			mv = s1;
			if (mv > s2)
				mv = s2;

			if (can>mv)
			{
				if (mv == s1)
				{
					s2 = s2 - can + s1;
					can = s1;
					if (s2 < 0)
						s2 = 0;
				}
				else
				{
					s1 = s1 - can + s2;
					can = s2;
					if (s1 < 0) 
						s1 = 0;
				}
			}


		}

		return true;
	}

	void solution(char *input, char *output)
	{
		ifstream fi(input);
		ofstream fo;
		fo.open(output);
	
		int tt;
		fi >> tt;
		for (int t=0;t<tt;t++)
		{
			ll lo = -1;
			ll hi = 0;
			ll s1 = 0;
			ll s2 = 0;
			int n;
			fi >> n;

			vi A(n, 0);
			vi B(n, 0);
			for (int i = 0; i < n; i++)
			{
				fi >> A[i];
				fi >> B[i];
				s1 += A[i];
				hi += B[i];
			}

			hi = max(hi, s1);

			ll maxV = -1;

			while (1)
			{
				ll mid = (lo + hi)/2;
				//int mid = 4;

				if (lo +1 >= hi)
				{
					break;
				}

				bool b = test(A, B, mid);

				if (b)
				{
					hi = mid;
				}
				else
				{
					lo = mid;
				}


			}


			fo << "Case# " << t+1 << "\n";
			fo << hi << "\n";
		}
		fo.close();
	}
};

