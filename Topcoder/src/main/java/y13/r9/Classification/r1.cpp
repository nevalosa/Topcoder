#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

void normalyze(double & a, double & b, double & c)
{
	double MX = max(max(a, b), c)*1.2;
	a/=MX; b/=MX; c/=MX;
}

inline double net(double w0, double w1, double w2, int x, int y)
{
	return w0 + w1*x + w2*y;
}

inline double ls(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

inline double H(double w0, double w1, double w2, int x, int y)
{
	return ls(net(w0, w1, w2, x, y));
}

inline int color(double w0, double w1, double w2, int x, int y)
{
	return H(w0, w1, w2, x, y)>=0.5;
}

int tryLine(double w0, double w1, double w2, const vector<int> & X, const vector<int> & Y, const vector<int> & C)
{
	int sum = 0;
	for(int i=0; i<X.size(); ++i)
	{
		if(color(w0, w1, w2, X[i], Y[i])==C[i])
			++sum;
	}
	return sum;
}

void grad(double & w0, double & w1, double & w2, const vector<int> & X, const vector<int> & Y, const vector<int> & C)
{
	const int TRESHOLD = 1000000;
	const double STEPMUL = 0.5;
	const double MOVE_TRESHOLD = 0.0000001;

	double step = 0.02;

	for(int iter=0; iter<TRESHOLD; ++iter)
	{
		double e0 = 0.0, e1 = 0.0, e2 = 0.0;
		for(int i=0; i<X.size(); ++i)
		{
			double hi = H(w0, w1, w2, X[i], Y[i]);
			double chi = (C[i] - hi)*hi*(hi-1.0);
			e0 += chi;
			e1 += chi*X[i];
			e2 += chi*Y[i];
		}

		double new_w0 = w0 - step*e0;
		double new_w1 = w1 - step*e1;
		double new_w2 = w2 - step*e2;

		double move = fabs(new_w0-w0) + fabs(new_w1-w1) + fabs(new_w2-w2);
		//cout<<move<<endl;
		if(move<MOVE_TRESHOLD)
			break;

		w0 = new_w0;
		w1 = new_w1;
		w2 = new_w2;

		if(step>0.002)
		{
			step*=STEPMUL;
			if(step<0.002)step=0.002;
		}
	}
}


int main()
{
	//freopen("e:/input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(false);
	int T;
	cin>>T;
	for(int t=1; t<=T; ++t)
	{
		int N; cin>>N;
		vector<int> X(N);
		vector<int> Y(N);
		vector<int> C(N);

		for(int i=0; i<N; ++i)
		{
			cin>>X[i]>>Y[i]>>C[i];
		}

		double xc = 0.0, yc = 0.0;
		for(int i=0; i<N; ++i)
		{
			xc+=X[i]; yc+=Y[i];
		}

		xc/=N; yc/=N;
		double w_0 = xc-yc, w0 = -(xc+yc);
		double w_1 = -1.0, w1 = 1.0;
		double w_2 = 1.0, w2 = 1.0;

		normalyze(w_0, w_1, w_2);
		normalyze(w0, w1, w2);

		if(tryLine(w_0, w_1, w_2, X, Y, C)>tryLine(w0, w1, w2, X, Y, C))
		{
			w0 = w_0;
			w1 = w_1;
			w2 = w_2;
		}

		grad(w0, w1, w2, X, Y, C);

		cout<<w0<<" "<<w1<<" "<<w2<<endl;
	}
	

	return 0;
}