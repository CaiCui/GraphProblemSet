#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之边上权值任意的单源最短路径--Bellman-Ford算法
  要求：图中不能包含权值总和为负的回路，即负圈
  求解：从源点v0到其他各点的最短路径
  算法求解一系列的dist1[u],dist2[u],dist3[u]...disti[u]..distn-1[u]
  最终得到dist(n-1)[u]即是从v0到u的最短路径
  disti[u]:从v0出发最多经过不构成负权值回路的i条边到达u的最短路径的长度
  方法：递推计算，有点类似DP思想，递推方程如下
  初始：dist1[u]=Edge[v0][u]
        distk[u]=min{distk-1[u],min{distk-1[j]+Edge[j][u],j!=u}}
*/
#define INF 1000000
#define MAXN 8
int n;
int Edge[MAXN][MAXN];
int dist[MAXN];
int path[MAXN];
void BellMan(int v0)
{
    int i,j,k,u;
    for(i=0;i<n;i++)//初始化
    {
        dist[i]=Edge[v0][i];
        if(i!=v0&&dist[i]<INF)path[i]=v0;
        else
            path[i]=-1;
    }
    for(k=2;k<n;k++)//dist正向递推，从1推到n-1
    {
        for(u=0;u<n;u++)
        {
            if(u!=v0)
            {
                for(j=0;j<n;j++)
                {
                    if(Edge[j][u]<INF&&dist[j]+Edge[j][u]<dist[u])
                    {
                        dist[u]=dist[j]+Edge[j][u];
                        path[u]=j;
                    }
                }
            }
        }
    }
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d",&n);
    while(1)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)break;
        Edge[u][v]=w;//有向图
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        if(i==j)Edge[i][j]=0;
        else if(Edge[i][j]==0)
           Edge[i][j]=INF;
    }
    BellMan(0);
    int shortest[MAXN];//输出最短路径序号
    for(i=1;i<n;i++)
    {
        printf("%d\t",dist[i]);
        //输出从0到其他点最短路径
        memset(shortest,0,sizeof(shortest));
        int k=0;
        shortest[k]=i;
        while(path[shortest[k]]!=0)
        {
            k++;
            shortest[k]=path[shortest[k-1]];
        }
        k++;
        shortest[k]=0;
        for(j=k;j>0;j--)
            printf("%d->",shortest[j]);
        printf("%d\n",shortest[0]);
    }

    return 0;
}
