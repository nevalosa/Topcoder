#include <stdio.h>

#define N 500000
#define P 10000

int arr[N+10], acc[N+10], cnt[P+10];

int main(){
	int t,T,n,p;
	scanf("%d",&T);
	for (t=1;t<=T;++t){
		scanf("%d %d",&n,&p);
		for (int i=0;i<p;++i) cnt[i] = 0;
		for (int i=0;i<n;++i)
			scanf("%d",&arr[i]);
		for (int i=0;i<n;++i){
			acc[i] = (i==0) ? arr[i] : arr[i] + acc[i-1];
			acc[i] = acc[i] % p;
			++cnt[acc[i]];
		}
		long long ans = 0;
		for (int i=0;i<p;++i){
			if (i==0) ans += cnt[i];
			if (cnt[i]>0) ans += ((long long)cnt[i] * (cnt[i]-1))/2;
		}
		printf("Case #%d\n%lld\n",t,ans);
	}
	return 0;
}