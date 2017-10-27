#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之边上权值任意的单源最短路径--Bellman-Ford算法
  邻接表 可以使复杂度变为O(n^2)，邻接矩阵为O(n^3)
  Bellman-Ford变形求解最长路径
  ZOJ1092 套汇
  利用贝尔曼福特思想求解n次。因为要回到原点，对每个点同样执行，判断是否有解。
*/
#define maxn 50
#define maxm 1000
#define max(a,b) ((a)>(b)?(a):(b))
struct exchange{
   int ci,cj;
   double cij;
}ex[maxm];
int i,j,k;
int n,m;
char name[maxn][20],a[20],b[20];
double x;
double maxdist[maxn];
int flag;
int kase=0;
int readcase()
{
    scanf("%d",&n);
    if(n==0)return 0;
    for(i=0;i<n;i++)
        scanf("%s",name[i]);
    scanf("%d",&m);
    for(i=0;i<m;i++)//读入汇率
    {
        scanf("%s %lf %s",a,&x,b);
        for(j=0;strcmp(a,name[j]);j++)
            ;
        for(k=0;strcmp(b,name[k]);k++)
            ;
        ex[i].ci=j;
        ex[i].cj=k;
        ex[i].cij=x;
    }
    return 1;
}
//求解从v0出发又回到v0的最长路径
void bellman(int v0)
{
        memset(maxdist,0,sizeof(maxdist));
        maxdist[v0]=1;
        for(k=1;k<=n;k++)//从maxdist[0]递推到n
        {
            for(i=0;i<m;i++)
            {
                if(maxdist[ex[i].ci]*ex[i].cij>maxdist[ex[i].cj])//判断每条边，加入它能否使最大距离增加
                    maxdist[ex[i].cj]=maxdist[ex[i].ci]*ex[i].cij;
            }
        }
        if(maxdist[v0]>1.0)flag=1;
}
int main()
{

    while(readcase())
        {
            flag=0;
            for(i=0;i<n&&!flag;i++)
                {
                    bellman(i);
                }
            if(flag)
                printf("Case %d:Yes\n",++kase);
            else
                printf("Case %d:No\n",++kase);
        }
    return 0;
}
