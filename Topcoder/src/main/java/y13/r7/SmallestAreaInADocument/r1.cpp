#include <algorithm>
#include <stdio.h>

using namespace std;

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions,
but main function call "solution" function only. */

};

using namespace std;


int at_least[2000], cur_cnt[2000];
int sol, sat; 
int leftmost; // sat = satistified words
int T, N, K;
int b[5000000], x[5000000];

void algorithm::solution(char *input, char *output)
{
	freopen(input, "rt", stdin);
	freopen(output, "wt", stdout);

	scanf("%d", &T);

	for(int i = 0; i < T; i++)
	{
		scanf("%d %d", &N, &K);

		sol = (1 << 30);
		sat = 0;
		for(int i = 0; i < K; i++)
		{
			scanf("%d", &at_least[i]);
			cur_cnt[i] = 0;
			if(!at_least[i]) sat++;
		}


		for(int i = 0; i < N; i++)
		{
			scanf("%d %d", &b[i], &x[i]);		
			b[i]--;
		}
		
		leftmost = 0;

		for(int i = 0; i < N; i++)
		{
			cur_cnt[b[i]]++;
			if(cur_cnt[b[i]] == at_least[b[i]]) sat++;
			while(sat >= K)
			{
				sol = min(sol, x[i] - x[leftmost] + 1);
				if(cur_cnt[b[leftmost]] <= at_least[b[leftmost]]) break;
				cur_cnt[b[leftmost]]--;
				leftmost++;
			}
		}

		printf("Case# %d\n",i +1);
		if(sol < (1 << 30))
			printf("%d\n", sol);
		else
			printf("-1\n");
	}
}