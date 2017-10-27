#include<bits/stdc++.h>
using namespace std;
/*
  图论之差分系统约束
  ZOJ1508 区间
  好题--构造约束条件进行处理，同时变形bellman-ford算法，当dist[]数组没有变化时，算法就可以停止
  解题关键: 在区间的最小值和最大值之间求得一条最短路径长度。
  数组下标竟然可以为负值也能访问计算
*/
#define inf 999999
#define EMAX 50002
struct e{
  int u,v,w;//起点终点权值
}edges[EMAX];
int n;
int dist[EMAX];
int mn;//所有区间左端点最小值
int mx;//所有区间右端点最大值
void init()
{
    int i;
    for(i=0;i<EMAX;i++)//将源点到各顶点的最短路径长度初始化为0,因为Si-Smx<=0,详解见书
        dist[i]=0;
    mx=1;
    mn=inf;

}
void bellman_ford()
{
    int i,t;
    int f=1;//提前结束的标志变量
    //如果某次没有产生路径的松弛，则提前结束
    while(f)
    {
        f=0;
        for(i=0;i<n;i++)
        {
            t=dist[edges[i].u]+edges[i].w;
            if(t<dist[edges[i].v])
            {
                dist[edges[i].v]=t;
                f=1;
            }
        }

        //根据第二个约束条件修改dist
        for(i=mn;i<=mx;i++)
        {
            t=dist[i-1]+1;
            if(dist[i]>t)
            {
                dist[i]=t;
                f=1;
            }
        }
        //根据第三个约束条件修改dist
        for(i=mx;i>=mn;i--)
        {
            t=dist[i];
            if(dist[i-1]>t)
            {
                dist[i-1]=t;
                f=1;
            }
        }

    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        init();
        int i,u,v,w;
        for(i=0;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[i].u=v;
            edges[i].v=u-1;
            edges[i].w=-w;
            //求区间端点最大最小值
            if(mn>u)mn=u;
            if(mx<v)mx=v;

        }
        bellman_ford();
        printf("%d\n",dist[mx]-dist[mn-1]);
    }
    return 0;
}
