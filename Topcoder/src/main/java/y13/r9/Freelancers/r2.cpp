#include<stdio.h>
#include<algorithm>
#include<vector>

#define N 1020

int n,m[N+2],works[N+2][N+2],firstc[N+2],q[40*N+2],c[40*N+2],deg[40*N+2];
std::vector<int> g[3*N+2];

int process(){
	int i,j;
	for(i=0;i<n+n+n;++i){ g[i].clear(); c[i]=1; deg[i]=0; }
	for(i=0;i<n;++i) firstc[i]=0;
	for(i=0;i<n;++i){
		if(m[i]==0) continue;
		firstc[works[i][0]]=1;
	}
	// 0~n-1 : freelancer, n~2n-1 : works, 2n~3n-1 : dummy work
	int ff;
	for(i=0;i<n;++i){
		if(m[i]==0){
			g[i].push_back(n+n+i);
			g[n+n+i].push_back(i);
			deg[i]++; deg[n+n+i]++ ;
			continue;
		}
		g[i].push_back(works[i][0]+n);
		g[works[i][0]+n].push_back(i);
		deg[i]++; deg[works[i][0]+n]++;
		ff=n+n+i;
		for(j=1;j<m[i];++j){
			if(firstc[works[i][j]]==0){
				ff=n+works[i][j];
				break;
			}
		}
		g[i].push_back(ff);
		g[ff].push_back(i);
		deg[i]++; deg[ff]++;
	}

	int t=0;
	for(i=n;i<n+n+n;++i){
		if(deg[i] < 2){
			q[t++]=i;
		}
	}
	int x;
	for(i=0;i<t;++i){
		if(deg[q[i]] == 0){
			c[q[i]]=0;
		}
		else{
			c[q[i]]=0;
			for(j=0;j<g[q[i]].size();++j){
				if(c[g[q[i]][j]]==1){
					x=g[q[i]][j];
					break;
				}
			}
			c[x]=0;
			for(j=0;j<g[x].size();++j){
				deg[g[x][j]]--;
				if(deg[g[x][j]] < 2 && c[g[x][j]] == 1){
					q[t++]=g[x][j];
				}
			}
		}
	}

	int a=0,b=0;
	for(i=0;i<n;++i) a+=c[i];
	for(i=n;i<n+n+n;++i) b+=c[i];
	return a<=b;
}

int main(){
	//freopen("1.in","rt",stdin);
	//freopen("1_3.in","rt",stdin);
	//freopen("1_5.in","rt",stdin);
	int t,T,i,j;
	scanf("%d",&T);
	for(t=1;t<=T;++t){
		printf("Case #%d\n",t);
		scanf("%d",&n);
		for(i=0;i<n;++i){
			scanf("%*d%d",&m[i]);
			for(j=0;j<m[i];++j){
				scanf("%d",&works[i][j]);
				works[i][j]--;
			}
		}
		int res = process();
		printf("%d\n",res);
	}
	return 0;
}
