/*
 * repairman3.cpp
 *
 *  Created on: 2014��2��22��
 *      Author: Calvin
 */
#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

const int MAXN = 1002;
int L[MAXN];
int W[MAXN];
int N;

typedef long long LLong;
LLong MWD[MAXN][MAXN];  //MWD[s][b]��ʾ��ǰ��s��,����һ��δ�����ı߽��Ϊb(��bΪ0 or N+1)ʱ���������ƶ�����СȨ�ؾ���
LLong Weight[MAXN][MAXN]; ///Weight[s][b]��ʾ��ǰ��s��,����һ��δ�����ı߽��Ϊb(��bΪ0 or N+1)ʱ��δ���������е��Ȩ�غ�
LLong Answer;

inline LLong MIN(const LLong &x, const LLong &y) {
	return (x <= y) ? x : y;
}
void input_case();
void run_case();
int main(void) {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		input_case();
		run_case();
		cout << "Case #" << i << endl;
		cout << Answer << endl;
	}
	return 0;
}

/*Accept one input case*/
void input_case() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> L[i];
	}
	for (int i = 1; i <= N; i++) {
		cin >> W[i];
	}
}

/*���� ��ǰ��s��,����һ��δ�����ı߽��Ϊb(��bΪ0 or N+1)ʱ���������ƶ�����СȨ�ؾ���*/
void set_mwd(int s, int b) {
	if (s < 1 || s > N)
		return;
	LLong ml = LLONG_MAX, mr = LLONG_MAX;
	if (s < b) {
		//---s ---b---
		if (s > 1) {
			//can go left
			Weight[s][b] = Weight[s - 1][b] + W[s - 1];
			ml = MWD[s - 1][b] + Weight[s][b] * (L[s] - L[s - 1]);
		}
		if (b <= N) {
			//can go right
			Weight[s][b] = Weight[s][b + 1] + W[b];
			mr = MWD[b][s - 1] + Weight[s][b] * (L[b] - L[s]);
		}
	} else {
		//---b--s---
		if (b >= 1) {
			// if can go left
			Weight[s][b] = Weight[s][b - 1] + W[b];
			ml = MWD[b][s + 1] + +Weight[s][b] * (L[s] - L[b]);
		}
		if (s < N) {
			// if can go right
			Weight[s][b] = Weight[s + 1][b] + W[s + 1];
			mr = MWD[s + 1][b] + Weight[s][b] * (L[s + 1] - L[s]);
		}
	}
	MWD[s][b] = MIN(ml, mr);
}

/*run one case*/
void run_case() {
	//memset(MWD, 0, MAXN * MAXN * sizeof(LLong));
	//memset(Weight, 0, MAXN * MAXN * sizeof(LLong));
	int d, s;
	MWD[N][0] = MWD[1][N+1] = 0;
	Weight[N][0] = Weight[1][N+1]=0;
	for (d = N - 1; d >= 1; d--) { //d is the gap between start and next_bound point
		for (s = 0; s + d <= N + 1; s++) {
			set_mwd(s, s + d);
			set_mwd(s + d, s);
		}
	}
	Answer = MWD[1][2];
	for (s = 2; s <= N; s++) {
		if (MWD[s][s - 1] < Answer) {
			Answer = MWD[s][s - 1];
		}
	}
}
