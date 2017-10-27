#include<bits/stdc++.h>
using namespace std;
/*
  图论之最短路Bellman-ford算法改进--SPFA
  POJ 3268 奶牛派对
  分别用ru边表和chu边表作为数据结构，使用两次SPFA求出各点到X点的最短时间和X到各点的最短时间
  两者相加后，取出最大的即可。
*/
#define MAXN 101000
#define INT_MAX 2000000
struct NODE{
  int v;
  int w;
  NODE *next;
}edge[MAXN],redge[MAXN],temp[MAXN*2];//edge和redge分别为正向图和反向图
int pos=0;
int ecost[MAXN];
int N,M,W,src,Q[MAXN]; //用数组Q模拟队列
bool visited[MAXN];
//SPFA算法。direction表方向，0正，1反
void SPFA(int direction)
{
    int h,t,u,i;
    NODE *ptr;
    h=0,t=1;
    memset(visited,0,sizeof(visited));
    for(i=0;i<=N;i++)
        ecost[i]=INT_MAX;
    Q[0]=src;
    ecost[src]=0;
    while(h!=t)
    {
        u=Q[h];
        h++;
        visited[u]=false;
        if(direction==0)ptr=edge[u].next;//求出从src到各个点的最短距离，出边表
        else
            ptr=redge[u].next;//求出从各个点到src的最短距离，入边表
        while(ptr)
        {
            if(ecost[ptr->v]>ecost[u]+ptr->w)
            {
                ecost[ptr->v]=ecost[u]+ptr->w;
                if(!visited[ptr->v])
                {
                    Q[t]=ptr->v;
                    t++;
                    visited[ptr->v]=true;
                }
            }
            ptr=ptr->next;
        }
    }
}
void Insert(const int &x,const int &y,const int &w)//对邻接表插入,正向反向
{
    NODE *ptr=&temp[pos++];
    ptr->v=y;
    ptr->w=w;
    ptr->next=edge[x].next;
    edge[x].next=ptr;
    ptr=&temp[pos++];
    ptr->v=x;
    ptr->w=w;
    ptr->next=redge[y].next;
    redge[y].next=ptr;
}
int main()
{
    int i,x,y,w;
    int ans[MAXN],MaxTime;//累加的最短时间和最短时间最大值
    while(scanf("%d%d%d",&N,&M,&src)!=EOF)
    {
        pos=0;
        for(i=0;i<=N;i++)
        {
            edge[i].next=NULL;
            redge[i].next=NULL;
        }
        for(i=0;i<M;i++)
        {
            scanf("%d%d%d",&x,&y,&w);
            Insert(x,y,w);
        }
        MaxTime=0;
        memset(ans,0,sizeof(ans));
        //正向求最短路
        SPFA(0);
        for(i=1;i<=N;i++)
        {
            if(i!=src)
            {
                ans[i]+=ecost[i];
                cout<<ecost[i]<<endl;
            }
        }
        //
        SPFA(1);
         for(i=1;i<=N;i++)
        {
            if(i!=src)
            {
                ans[i]+=ecost[i];
                 cout<<ecost[i]<<endl;
                if(ans[i]>MaxTime)
                    MaxTime=ans[i];
            }
        }
        printf("%d\n",MaxTime);
    }
    return 0;
}
