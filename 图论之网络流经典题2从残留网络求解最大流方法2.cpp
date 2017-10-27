#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之网络最大流
  POJ1273 排水沟
  完全的网络流模拟，求出最大流
*/
#define MAXN 210
struct Matrix{
  int c,f;//容量，流量
};
Matrix Edge[MAXN][MAXN];//流及容量矩阵
int M,N;//弧和节点
int s,t;//源点和汇点
int residual[MAXN][MAXN]; //残留网络
int qu[MAXN*MAXN],qs,qe;//队列，队头和队尾
int pre[MAXN]; //增广路上顶点i的前一个
int vis[MAXN]; //访问标记
int maxflow,min_augment;//最大流和改进量
void find_argument_path()//BFS求解增广路
{
    int i,cu;
    memset(vis,0,sizeof(vis));
    memset(residual,0,sizeof(residual));
    memset(pre,0,sizeof(pre));
    //首元素进队
    qs=0;
    qu[qs]=s;
    pre[s]=s;
    vis[s]=1;
    qe=1;
    while(qs<qe&&pre[t]==0)
    {
        cu=qu[qs];
        for(i=1;i<=N;i++)
        {
            if(vis[i]==0)
            {
               if(Edge[cu][i].c-Edge[cu][i].f>0)//正向边
               {
                   residual[cu][i]=Edge[cu][i].c-Edge[cu][i].f;//残留网络
                   pre[i]=cu;
                   qu[qe++]=i;
                   vis[i]=1;
               }
               else if(Edge[i][cu].f>0)//反向边
               {
                   residual[cu][i]=Edge[i][cu].f;
                   pre[i]=cu;
                   vis[i]=1;
                   qu[qe++]=i;
               }
            }
        }
        qs++;
    }
}
void augment_flow()//计算可改进量
{
    int i=t,j;
    if(pre[i]==0)//汇点不可改进
    {
        min_augment=0;
        return;
    }
    j=0x7fffffff;
    while(i!=s)//求可改进量最小值
    {
        if(residual[pre[i]][i]<j)
            j=residual[pre[i]][i];
        i=pre[i];
    }
    min_augment=j;
}
void update_flow()//流量调整
{
     int i=t;
     if(pre[i]==0)return;
     while(i!=s)
     {
         if(Edge[pre[i]][i].c-Edge[pre[i]][i].f>0)
            Edge[pre[i]][i].f+=min_augment;
         else if(Edge[i][pre[i]].f>0)
            //Edge[pre[i]][i].f+=min_augment;和下面那句都可以ac,效果一样，下面是反向减流量，这句相当于同样这条边正向加流量。等价的！！
            Edge[i][pre[i]].f-=min_augment;
         i=pre[i];
     }
}
void solve()//求解
{
    s=1;
    t=N;
    maxflow=0;
    while(true)
    {
        find_argument_path();
        augment_flow();
        maxflow+=min_augment;
        if(min_augment>0)
            update_flow();
        else
            return;
    }
}
int main()
{
    int i;
    int u,v,c;
    while(scanf("%d%d",&M,&N)!=EOF)
    {
        memset(Edge,0,sizeof(Edge));
        for(i=0;i<M;i++)
        {
            scanf("%d%d%d",&u,&v,&c);
            Edge[u][v].c+=c;
        }
        solve();
        printf("%d\n",maxflow);
    }
    return 0;
}
