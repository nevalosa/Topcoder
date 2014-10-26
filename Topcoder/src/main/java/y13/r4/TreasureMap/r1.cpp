//You can include standard C++ language libraries that you want use.//
#include <stdio.h>

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions,
but main function call "solution" function only. */

};

#define NINF -1000000

int n,m;
char map[20][21];
int st[2],rn,r[16][2],gain[16];
int d[16][16],sd[16];
int c[20][20];
int dy[16][70000];

void getdist(int sx, int sy){
	int i,j,q[400][2],t,way[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	for(i=0;i<n;i++) for(j=0;j<m;j++) c[i][j]=-1;
	q[0][0]=sx; q[0][1]=sy; t=1; c[sx][sy]=0;
	for(i=0;i<t;i++){
		for(j=0;j<4;j++){
			int nx=q[i][0]+way[j][0],ny=q[i][1]+way[j][1];
			if(nx<0 || ny<0 || nx>=n || ny>=m) continue;
			if(map[nx][ny]=='~') continue;
			if(c[nx][ny]<0){
				c[nx][ny]=c[q[i][0]][q[i][1]]+1;
				q[t][0]=nx; q[t][1]=ny;
				t++;
			}
		}
	}
}

int process(){
	int i,j;

	// get start point and ruins
	rn=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(map[i][j]=='E'){
				st[0]=i; st[1]=j;
			}
			if('1'<=map[i][j] && map[i][j]<='9'){
				r[rn][0]=i; r[rn][1]=j;
				gain[rn]=map[i][j]-'0';
				rn++;
			}
		}
	}
	if(rn==0) return 0;

	// get distances
	for(i=0;i<rn;i++){
		getdist(r[i][0],r[i][1]);
		for(j=0;j<rn;j++){
			d[i][j]=c[r[j][0]][r[j][1]];
		}
	}
	getdist(st[0],st[1]);
	for(i=0;i<rn;i++) sd[i]=c[r[i][0]][r[i][1]];
	
	// fill table
	int pw=1;
	for(i=0;i<rn;i++) pw=pw+pw;
	for(i=0;i<rn;i++) for(j=0;j<pw;j++) dy[i][j]=NINF;
	int status,lastp,nextp;
	
	int ans=0;

	for(i=0;i<rn;i++){
		if(sd[i]>0){
			dy[i][1<<i]=sd[i]*(-2)+gain[i];
		}
	}
	for(status=0;status<pw;status++){
		for(lastp=0;lastp<rn;lastp++){
			if(dy[lastp][status]==NINF) continue;

			if(sd[lastp]!=-1){
				if(dy[lastp][status]+sd[lastp]*(-2)>ans){
					ans=dy[lastp][status]+sd[lastp]*(-2);
				}
			}

			for(nextp=0;nextp<rn;nextp++){
				if( (status | (1<<nextp)) == status ) continue;
				if( d[lastp][nextp] == -1) continue;
				int val = dy[lastp][status]+d[lastp][nextp]*(-2)+gain[nextp];
				if(dy[nextp][(status|(1<<nextp))]<val){
					dy[nextp][(status|(1<<nextp))]=val;
				}
			}
		}
	}

	return ans;
}

void algorithm::solution(char *input, char *output){
	freopen(input,"rt",stdin);
	freopen(output,"wt",stdout);
	int t,i;
	for(scanf("%d",&t);t>0;t--){
		scanf("%d%d",&n,&m);
		for(i=0;i<n;i++) scanf("%s",map[i]);
		int res = process();
		printf("%d\n",res);
	}
}
