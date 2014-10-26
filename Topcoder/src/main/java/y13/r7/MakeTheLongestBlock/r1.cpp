#include <algorithm>

using namespace std;

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions,
but main function call "solution" function only. */

};

using namespace std;


#include<stdio.h>
#include<string.h>
#define MAXN 100000
#define MAXST MAXN*20

int n,m,sn;
int wn[MAXN], words[MAXN][20];
int g[MAXST][10], f[MAXST], d[MAXST][10], o[MAXST], q[MAXST];

void generate_diagram(){
	int i,j,x,t,s;
	for(i=0;i<n*20;i++){
		for(j=0;j<10;j++) g[i][j]=0;
		f[i]=0; o[i]=0;
	}

	// goto
	sn=1;
	for(i=0;i<n;i++){
		x=0;
		for(j=0;j<wn[i];j++){
			if(g[x][words[i][j]] == 0){
				g[x][words[i][j]]=sn;
				x=sn++;
			}
			else{
				x=g[x][words[i][j]];
			}
		}
		o[x]=1;
	}

	// failure
	t=0;
	for(i=0;i<m;i++){
		if(g[0][i] != 0) q[t++]=g[0][i];
	}
	for(i=0;i<t;i++){
		x=q[i];
		for(j=0;j<m;j++){
			if(g[x][j] != 0){
				q[t++]=g[x][j];
				s=f[x];
				while(g[s][j] == 0 && s > 0) s=f[s];
				f[g[x][j]]=g[s][j];
				o[g[x][j]] = (o[g[x][j]] | o[g[s][j]]);
			}
		}
	}

	// delta
	t=0;
	for(i=0;i<m;i++){
		d[0][i]=g[0][i];
		if(g[0][i] != 0) q[t++]=g[0][i];
	}
	for(i=0;i<t;i++){
		x=q[i];
		for(j=0;j<m;j++){
			if(g[x][j] != 0){
				q[t++]=g[x][j];
				d[x][j]=g[x][j];
			}
			else d[x][j]=d[f[x]][j];
		}
	}
}

int cal_longestpath(){
	// reuse array f as reachable or not, array o as in-degree count after reachable search and as maximum distance after topological search
	int i,j,t=1,x,y,nn;
	for(i=0;i<sn;i++) f[i]=0;
	q[0]=0; f[0]=1;
	for(i=0;i<t;i++){
		x=q[i];
		for(j=0;j<m;j++){
			y=d[x][j];
			if(o[y] == 1) continue;
			if(f[y] == 0){
				f[y]=1;
				q[t++]=y;
			}
		}
	}

	for(i=0;i<sn;i++){
		if(f[i]==0) continue;
		for(j=0;j<m;j++){
			if(f[d[i][j]] == 0) continue;
			o[d[i][j]]++;
		}
	}

	t=0; nn=0;
	for(i=0;i<sn;i++){
		nn=nn+f[i];
		if(o[i]==0) q[t++]=i;
	}

	for(i=0;i<t;i++){
		x=q[i];
		for(j=0;j<m;j++){
			if(f[d[x][j]] == 0) continue;
			o[d[x][j]]--;
			if(o[d[x][j]] == 0){
				q[t++]=d[x][j];
			}
		}
	}

	if(t<nn) return -1;

	int ans=0;
	for(i=0;i<t;i++) o[q[i]]=0;
	for(i=0;i<t;i++){
		x=q[i];
		for(j=0;j<m;j++){
			if(f[d[x][j]] == 0) continue;
			if(o[x]+1 > o[d[x][j]]){
				o[d[x][j]]=o[x]+1;
				if(o[d[x][j]] > ans) ans=o[d[x][j]];
			}
		}
	}
	return ans;
}

void process(){
	generate_diagram();
	int res=cal_longestpath();
	if(res == -1){
		printf("No\n");
	}
	else{
		printf("%d\n",res);
	}
}

void algorithm::solution(char *input, char *output)
{
	freopen(input,"r",stdin);
	freopen(output,"w",stdout);
	int t,tn,i,j;
	char buf[21];
	scanf("%d",&tn);
	for(t=1;t<=tn;t++){
		printf("Case# %d\n",t);
		scanf("%d%d",&m,&n);
		for(i=0;i<n;i++){
			scanf("%s",buf);
			wn[i]=strlen(buf);
			for(j=0;j<wn[i];j++) words[i][j]=buf[j]-'0';
		}
		process();
	}
}
