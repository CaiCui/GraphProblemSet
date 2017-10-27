#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之差分约束系统
  差分约束系统可以转化成一个有向网或无向网问题，然后通过求出一次单源最短路径即可得出满足差分约束不等式的解，
  这也是最短路径问题的基本性质
  差分约束DEMOCODE
  ZOJ2770 火烧联营 构造差分约束不等式，转化为图，利用BellMan-Ford求解最短路径
*/
#define INF 9999999
#define NMAX 1001
#define EMAX 23000
int n;
int m;
int c[NMAX];//第i个大本营最多有c[i]个士兵
int dist[NMAX];//从源点到各个顶点最短路径长度(源点为Sn)
int d[NMAX];//前i个大本营容量总和
int ei; //边序号
struct eg{
  int u,v,w;
}edges[EMAX];
void init()
{
    ei=0;
    int i;
    //除了源点外，其他顶点最短距离初始化为INF
    for(i=0;i<=n;i++)
        dist[i]=INF;
    d[0]=0;
    dist[n]=0;
}
//如果存在源点可达的负权值回路，返回false
bool bellman_ford()
{
   int i,k,t;
   //算法执行N-1次，N表示顶点个数，由于本题中，添加了0顶点，所以顶点数为n+1
   for(i=0;i<n;i++)
   {
       for(k=0;k<ei;k++)
       {
           t=dist[edges[k].u]+edges[k].w;
           if(dist[edges[k].u]!=INF&&t<dist[edges[k].v])
           {
               dist[edges[k].v]=t;
           }
       }
   }
   //判断环路，重新再做一下每条边的检查，判断加入该边后是否会使路径再缩短，成立则存在环
   for(k=0;k<ei;k++)
   {
       if(dist[edges[k].u]!=INF&&dist[edges[k].u]+edges[k].w<dist[edges[k].v])
        return false;
   }
   return true;
}
int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        init();
        int i,u,v,w;
        for(i=1;i<=n;i++)//构造不等式组A，与n相关
        {
           scanf("%d",&c[i]);
           edges[ei].u=i-1;
           edges[ei].v=i;
           edges[ei].w=c[i];//构造边<i-1,i>,权值为Ci
           ei++;
           edges[ei].u=i;
           edges[ei].v=i-1;
           edges[ei].w=0;//构造边<i,i-1>,权值为0
           ei++;
           d[i]=c[i]+d[i-1];
        }
        for(i=0;i<m;i++)//构造不等式组B，与m相关
        {
              scanf("%d %d %d",&u,&v,&w);
              edges[ei].u=v;
              edges[ei].v=u-1;
              edges[ei].w=-w;
              ei++;
              edges[ei].u=u-1;
              edges[ei].v=v;
              edges[ei].w=d[v]-d[u-1];
              ei++;
        }
        if(!bellman_ford())
            printf("Bad Estimations\n");
        else
            printf("%d\n",dist[n]-dist[0]);
    }
    return 0;
}
