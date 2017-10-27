#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
/*
  图论之边权任意的单源最短路--Bellman-ford算法
  ZOJ1721 门
  难点：图的构造，判断线段是否会被墙挡住，挡不住则连线，否则不能连。
*/
#define INF 200000000
#define MAXN 100
struct POINT{
  double x,y;
};
struct EDGE{
  int u,v;
};
int n;
double wX[20];
POINT p[MAXN];
int pSize;//点的数目
double pY[20][4];
double g[MAXN][MAXN];//图的邻接矩阵
EDGE e[MAXN*MAXN];//有向图的边
int eSize;
int i,j;
//距离计算
double Dis(POINT a,POINT b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
//判断(x3,y3)在(x1,y1)和(x2,y2)所在直线的上方还是下方 >0上 <0下
double Cross(double x1,double y1,double x2,double y2,double x3,double y3)
{
    return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}
//在构造有向网时判断两点间能否连成一条边
bool IsOk(POINT a,POINT b)
{
    if(a.x>=b.x)return false;
    bool flag=true;
    int i=0;
    while(wX[i]<=a.x &&i<n)
        i++;
    while(wX[i]<b.x && i<n)//判断a,b之间是否被墙挡住
    {
        if(Cross(a.x,a.y,b.x,b.y,wX[i],0)*Cross(a.x,a.y,b.x,b.y,wX[i],pY[i][0])<0
           || Cross(a.x,a.y,b.x,b.y,wX[i],pY[i][1])*Cross(a.x,a.y,b.x,b.y,wX[i],pY[i][2])<0||
           Cross(a.x,a.y,b.x,b.y,wX[i],pY[i][3])*Cross(a.x,a.y,b.x,b.y,wX[i],10)<0 )
        {
            flag=false;
            break;
        }
        i++;
    }
    return flag;
}
double BellmanFord(int beg,int end)
{
    double d[MAXN];//距离数组
    int i,j;
    for(i=0;i<MAXN;i++)
        d[i]=INF;
    d[beg]=0;
    bool ex=true;
    for(i=0;i<pSize&&ex;i++)//这里n次和n-1次效果一样
    {
        ex=false;
        for(j=0;j<eSize;j++)
        {
            if(d[e[j].u]<INF&&d[e[j].v]>d[e[j].u]+g[e[j].u][e[j].v])
            {
                d[e[j].v]=d[e[j].u]+g[e[j].u][e[j].v];
                ex=true;
            }
        }

    }
    return d[end];
}
void Solve()
{
    p[0].x=0;
    p[0].y=5;
    pSize=1;
    for(i=0;i<n;i++)
    {
        scanf("%lf",&wX[i]);
        for(j=0;j<4;j++)
        {
            p[pSize].x=wX[i];
            scanf("%lf",&p[pSize].y);
            pY[i][j]=p[pSize].y;
            pSize++;
        }
    }
    p[pSize].x=10;
    p[pSize].y=5;
    pSize++;
    for(i=0;i<pSize;i++)
        for(j=0;j<pSize;j++)
        g[i][j]=INF;
    eSize=0;
    for(i=0;i<pSize;i++)//只能前面的点和后面的点连线
    {
        for(j=i+1;j<pSize;j++)
        {
           if(IsOk(p[i],p[j]))
           {
               g[i][j]=Dis(p[i],p[j]);
               e[eSize].u=i;
               e[eSize].v=j;
               eSize++;
           }
        }
    }
    printf("%.2lf\n",BellmanFord(0,pSize-1));
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(n==-1)break;
        Solve();
    }
    return 0;
}
