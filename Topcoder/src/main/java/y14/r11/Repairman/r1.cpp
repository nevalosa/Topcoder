#include <stdio.h>
#include <string.h>
#include <limits.h>

int loc[1001];
int weight[1001];

#define L 0
#define R 1
#define INVALID -1

long long dptable[1002][1002][2];
long long partial_w[1002];

inline long long min(long long x, long long y)
{
         if(x == INVALID && y == INVALID)
                   return 0;
         if(x == INVALID)
                   return y;
         if(y == INVALID)
                   return x;
         return x > y ? y : x;
}

int main()
{
         int i, p1, p2, n, tc, c;
         long long total_w, w;
         long long result, t;
         scanf("%d", &tc);
         for(c = 1; c <= tc; c++)
         {
                   scanf("%d", &n);
                   for(i = 1; i <= n; i++)
                            scanf("%d", &loc[i]);
                   total_w = 0;
                   partial_w[0] = 0;
                   for(i = 1; i <= n; i++)
                   {
                            scanf("%d", &weight[i]);
                            partial_w[i] = partial_w[i-1]+weight[i];
                   }
                   total_w = partial_w[n+1] = partial_w[n];
                                     
                   memset(dptable, INVALID, sizeof(dptable));
                   dptable[1][n+1][R] = 0;
                   dptable[1][n+1][L] = 0;
                   for(i = 2; i <= n; i++)
                   {
                            //dptable[i][n+1][R] = INVALID;
                            dptable[i][n+1][L] = (loc[i]-loc[i-1])*partial_w[i-1]+dptable[i-1][n+1][L];
                   }
                   dptable[n][0][R] = 0;
                   dptable[n][0][L] = 0;
                   for(i = 1; i < n; i++)
                   {
                            //dptable[i][0][L] = INVALID;
                            dptable[i][0][R] = (loc[i+1]-loc[i])*(total_w-partial_w[i])+dptable[i-1][0][R];
                   }
                   for(i = n; i >= 2; i--)
                   {
                            for(p1 = 1; p1 <= n+1-i; p1++)
                            {
                                     p2 = i+p1-1;
                                     w = total_w-(partial_w[p2-1]-partial_w[p1-1]);
                                     dptable[p1][p2][R] = (loc[p2]-loc[p1])*w+min(dptable[p2][p1-1][L], dptable[p2][p1-1][R]);
                                     if(p1 > 1)
                                               dptable[p1][p2][L] = (loc[p1]-loc[p1-1])*w+min(dptable[p1-1][p2][L], dptable[p1-1][p2][R]);
                                     //else
                                     //      dptable[p1][p2][L] = INVALID;

                                     w = w-weight[p2]+weight[p1];
                                     dptable[p2][p1][L] = (loc[p2]-loc[p1])*w+min(dptable[p1][p2+1][L], dptable[p1][p2+1][R]);
                                     if(p2 < n)
                                               dptable[p2][p1][R] = (loc[p2+1]-loc[p2])*w+min(dptable[p2+1][p1][L], dptable[p2+1][p1][R]);
                                     //else
                                     //      dptable[p2][p1][R] = INVALID;
                            }
                   }
                   /*for(p1 = 1; p1 <= n; p1++)
                   {
                            for(p2 = 1; p2 <= n; p2++)
                                     printf("%lld/%lld ", dptable[p1][p2][L], dptable[p1][p2][R]);
                            printf("\n");
                   }*/
                   result = LLONG_MAX;
                   for(p1 = 1; p1 < n; p1++)
                            if((t = min(dptable[p1][p1+1][R], dptable[p1][p1+1][L])) < result)
                                     result = t;
                   if((t = dptable[n][n-1][L]) < result)
                            result = t;
                   printf("Case #%d\n%lld\n", c, result);
         }
         return 0;
}
