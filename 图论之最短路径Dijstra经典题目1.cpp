#include<iostream>
#include<cstdio>
using namespace std;
/*
  图论之边上权值非负情形的单源最短路--Dijkstra算法
   ZOJ 1298 多米诺骨牌效应
   好题
   分析：
   分两种情况：
   第一种是最后倒下的是关键牌，此时只需要求出第一张牌到每个关键牌的最短路径，那么最长的那个最短路径就是结果。
   第二种是最后倒下的是两张关键牌之间的普通牌，此时时间为到这两张关键牌的时间的一半，再加上最后这两张牌之间的这行时间的一半；
   如何判断是哪种情况呢？
   其实首先求出第一张牌到每个关键牌的最短路径，然后找出最短路径中最大的记为Mx1,
   然后求出每行普通牌，也就是每条边完全倒下需要的时间，计算方法：(time[i]+time[j]+Edge[i][j])/2，其中time[i]表示从第一张牌到此关键牌
   i的最短路径长度，Edge[][]就表示关键牌i和j之间的时间(即给定的普通行完全倒下时间，也就是边<i,j>的权值),记为Mx2;
   如果Mx2>Mx1，说明是第二种情况，原因显而易见，Mx2>Mx1说明终点不是关键牌，说明还有普通行也就是某关键牌i,j之间还有边没倒完，
   所以加上后才大于到各个关键牌的最短路径的最大值.
*/
#define MAXN 500
#define INF 100000
int n,m;
int Edge[MAXN][MAXN]; //图的邻接矩阵
int caseno=1; //测试数据的序号
int time[MAXN]; //第i张牌，即第i个节点倒下的时间
int S[MAXN]; //S[]表示关键牌i倒下时间是否已经计算，即Dijkstra算法中的已求的最短路径节点的集合
void solve_case()
{
    int i,j,k;
    //Dijkstra
    for(i=0;i<n;i++)
    {
        time[i]=Edge[0][i];
        S[i]=0;
    }
    time[0]=0;
    S[0]=1;
    for(i=0;i<n-1;i++)
    {
        int min=INF,u=0;
        for(j=0;j<n;j++)
        {
            if(!S[j] &&time[j]<min)
            {
                u=j;
                min=time[j];
            }
        }
        S[u]=1;
        for(k=0;k<n;k++)//更新time[]
        {
            if(!S[k] && Edge[u][k]<INF && time[u]+Edge[u][k]<time[k])
                {
                    time[k] = time[u] + Edge[u][k];
                }
        }
    }
    double maxtime1=-INF;
    int pos;//结果位置
    for(i=0;i<n;i++)//求出最大的maxtime1
    {
        if(time[i]>maxtime1)
        {
            maxtime1=time[i];
            pos=i;
        }
    }

    double maxtime2=-INF,t; //每行普通牌倒下的时间，即每条边完全倒下的时间,求出最大值和位置
    int pos1,pos2;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        t = (time[i]+time[j]+Edge[i][j])/2.0;
        if(Edge[i][j]<INF && t>maxtime2)
        {
            maxtime2 = t;
            pos1 = i;
            pos2 = j;
        }
    }
    printf("System #%d\n",caseno++); //输出
    printf("The last domino falls after ");
    if(maxtime2 > maxtime1)
            printf("%.1f seconds,between the key dominoes %d and %d. \n\n",maxtime2,pos1+1,pos2+1);
    else
        printf("%.1f seconds, at key domino %d. \n\n",maxtime1,pos);
}
int read_case()//读入数据
{
    int i,j;
    int v1,v2,t;
    scanf("%d%d",&n,&m);
    if(n==0&&m==0)return 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            Edge[i][j]=INF;//无连接
    }
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&v1,&v2,&t);
        v1--;
        v2--;
        Edge[v1][v2]=Edge[v2][v1]=t; //构建无向图
    }
    return 1;
}
int main()
{
    while(read_case())
      solve_case();
    return 0;
}
