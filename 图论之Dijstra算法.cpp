#include<bits/stdc++.h>
using namespace std;
/*
  图论之边上权值非负情形的单源最短路--Dijkstra算法
  适用于无向网和有向网
  思想：
  按照路径长度的递增次序，逐步产生最短路径。
  首先求出长度最短的一条路径，再参照它求出长度次短的一条最短路径，依次类推，完成从源点到各个顶点的路径计算更新。
  核心: dist[k]=min{dist[k],dist[u]+Edge[u][k]}
  求解，从v0到各顶点的最短路径长度。
*/
#define INF 10000000
#define MAXN 20
int n;
int Edge[MAXN][MAXN];
int S[MAXN]; //S集合存放已经找到最短路径的顶点
int dist[MAXN]; //存放从源点v0到当前顶点i的距离
int path[MAXN]; //倒存路径
void Dijstra(int v0)//求出有向图从v0到各个其他顶点的最短路径
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        dist[i]=Edge[v0][i];
        S[i]=0;
        if(i!=v0&&dist[i]<INF)
            path[i]=v0;
        else
            path[i]=-1;
    }
    S[v0]=1;
    dist[v0]=0;//处理源点
    for(i=0;i<n-1;i++)//确定n-1条最短路径
    {
        int min=INF;
        int u=v0;
        //选择当前集合T中具有最短路径的顶点u
        for(j=0;j<n;j++)
        {
            if(!S[j]&&dist[j]<min)
            {
                u=j;
                min=dist[j];
            }
        }
        S[u]=1;//将u加入集合S，表示已经求出它的最短路径
        //利用u,修改更新一遍T中dist和path的数组值
        for(k=0;k<n;k++)
        {
            if(!S[k]&&Edge[u][k]<INF&&dist[u]+Edge[u][k]<dist[k])
            {
                dist[k]=dist[u]+Edge[u][k];
                path[k]=u;
            }
        }
    }
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d",&n);
    while(true)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)
            break;
        Edge[u][v]=w;
    }
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(i==j)
          Edge[i][j]=0;
        else if(Edge[i][j]==0)
          Edge[i][j]=INF;
    Dijstra(0);
    int shortest[MAXN];//最短路径数组
    for(i=1;i<n;i++)
    {
        printf("%d\t",dist[i]);//输出v0到i的最短路径
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
        {
            printf("%d->",shortest[j]);
        }
        printf("%d\n",shortest[0]);
    }

    return 0;
}
