#include <stdio.h>

#define Max 100001

int N, T, a[Max], left[Max], right[Max];

int fillLeft(int c, int i){
	if (i<0)
		return -N;
	if (a[i]>a[c])
		return i;
	return fillLeft(c, left[i]);
}

int fillRight(int c, int i){
	if (i>=N)
		return 2*N;
	if (a[i]>a[c])
		return i;
	return fillRight(c, right[i]);
}

int main(void)
{
	int test_case, i;
	//freopen("input.txt", "r", stdin);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		scanf("%d", &N);		
		for (i=0; i<N; i++){
			scanf("%d", &a[i]);
		}
		/*for (i=0; i<N; i++)
			printf("%ld ",a[i]);
		printf("\n");*/
		left[0]=-N;
		for (i=1; i<N; i++)
			left[i]=fillLeft(i, i-1);
		/*for (i=0; i<N; i++)
			printf("%ld ",left[i]);
		printf("\n");*/

		right[N-1]=2*N;
		for (i=N-2; i>=0; i--)
			right[i]=fillRight(i, i+1);
		/*for (i=0; i<N; i++)
			printf("%ld ", right[i]);
		printf("\n");*/

		printf("Case #%d\n", test_case+1);
		for (i=0; i<N; i++){
			if (i-left[i]<=right[i]-i)
				printf("%d ", left[i]);
			else
				printf("%d ", right[i]);
		}
		//printf("%d\n", Answer);
		printf("\n");
	}

	return 0;
}
