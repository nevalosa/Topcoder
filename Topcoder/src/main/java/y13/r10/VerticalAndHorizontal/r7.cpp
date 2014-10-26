#include<stdio.h>
#include<stdlib.h>

#define Max 200003
#define Add 100000

int C, N, x[Max], y[Max], valid;

int main(){
	int i, Case, a, b, sum1, sum2;
	//freopen("input.txt", "r", stdin);
	scanf("%d", &C);
	for (Case=1; Case<=C; Case++){
		scanf("%d", &N);
		memset(x, 0, sizeof(int)*Max);
		memset(y, 0, sizeof(int)*Max);
		sum1=sum2=0;
		for (i=0; i<N; i++){
			scanf("%d %d", &a, &b);
			a+=Add;
			b+=Add;
			x[a]=!x[a];
			y[b]=!y[b];
			if (x[a])
				sum1++;
			else
				sum1--;
			if (y[b])
				sum2++;
			else
				sum2--;
		}
		printf("Case #%d\n", Case);
		//printf("%d %d\n", sum1, sum2);
		if (!sum1 || !sum2)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
