#include<stdio.h>
#include<string.h>

#define Max 1000009

int C, result[Max];
char st[Max];

int main(){
	int i, Case, N, sum;
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &C);
	for (Case=1; Case<=C; Case++){
		scanf("%s", st);
		N=strlen(st);
		memset(result, 0, Max*sizeof(int));
		if (N==1){
			result[0]=1;
			N++;
		}else if (st[1]=='0'){
			for (i=2; i<N; i++)
				result[N-i-1]=st[i]-'0';
			result[N-2]=1;
			result[N-1]=0;
			result[0]++;
		}else{
			for (i=1; i<N; i++)
				result[N-i-1]=1;
			result[0]++;
		}
		sum=0;
		for (i=0; i<N-2; i++){
			sum+=st[i]-'0';
			result[N-i-3]+=sum;
			if (st[i+1]=='0' && st[i+2]=='0')
				result[0]--;
		}
		/*for (i=0; i<N-1; i++)
			result[i]=1;
		if (st[1]=='0'){
			for (i=2; i<N; i++)
				result[N-i]+=st[i]-'0';
		}
		i=1;
		while(i<N-2){
			result[N-i-2]+=st[i]-'0';
			i++;
		}*/
		N--;
		sum=0;
		for (i=0; i<N; i++){
			sum+=result[i];
			result[i]=sum%2;
			sum=sum/2;
		}
		while(sum){
			result[i]=sum%2;
			sum=sum/2;
			N++;
		}
		printf("Case #%d\n", Case);
		//for (i=0; i<N; i++)
		while(!result[N-1])
			N--;
		for (i=N-1; i>=0; i--)
			printf("%d", result[i]);
		printf("\n");
	}
	return 0;
}
