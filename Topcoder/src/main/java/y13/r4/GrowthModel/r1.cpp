//You can include standard C++ language libraries that you want use.//
#include <stdio.h>

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions,
but main function call "solution" function only. */

};
#define SIZE 20000000

char str[2][SIZE];
char firstrule[SIZE];

#include <memory.h>
#include <string.h>

void algorithm::solution(char *input, char *output){
	freopen(input,"rt",stdin);
	freopen(output,"wt",stdout);
	int t,T;
	scanf("%d",&T);
	for (t=0;t<T;++t)
	{
		int n;
		scanf("%d",&n);
		memset(firstrule,0,sizeof(firstrule));
		scanf("%s",firstrule);
		memset(str[0],0,sizeof(str[0]));
		memcpy(str[0],firstrule,sizeof(firstrule));
		int from = 0,to = 0;
		if (n==1){
			printf("%s",firstrule);
		}
		for (int i=0;i<n-1;++i)
		{
			from = i%2;
			to = !from;
			memset(str[to],0,sizeof(str[to]));
			int c = 0;
			int len = strlen(firstrule);
			int len2 = strlen(str[from]);
			for (int j=0;j<len;++j)
			{
				if (i==n-2)
				{
					if (firstrule[j]=='F')
					{
						printf("%s",str[from]);
					}
					else{
						printf("%c",firstrule[j]);
					}
				}
				else{
					if (firstrule[j]=='F')
					{
						strcpy(str[to]+c,str[from]);
						c += len2;
					}
					else
					{
						str[to][c++] = firstrule[j];
					}
				}
			}
		}
		printf("\n");
	}
}
