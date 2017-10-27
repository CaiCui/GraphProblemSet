#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
/*
  ͼ��֮��Ȩ����ĵ�Դ���·--Bellman-ford�㷨
  ZOJ1721 ��
  �ѵ㣺ͼ�Ĺ��죬�ж��߶��Ƿ�ᱻǽ��ס������ס�����ߣ�����������
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
int pSize;//�����Ŀ
double pY[20][4];
double g[MAXN][MAXN];//ͼ���ڽӾ���
EDGE e[MAXN*MAXN];//����ͼ�ı�
int eSize;
int i,j;
//�������
double Dis(POINT a,POINT b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
//�ж�(x3,y3)��(x1,y1)��(x2,y2)����ֱ�ߵ��Ϸ������·� >0�� <0��
double Cross(double x1,double y1,double x2,double y2,double x3,double y3)
{
    return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}
//�ڹ���������ʱ�ж�������ܷ�����һ����
bool IsOk(POINT a,POINT b)
{
    if(a.x>=b.x)return false;
    bool flag=true;
    int i=0;
    while(wX[i]<=a.x &&i<n)
        i++;
    while(wX[i]<b.x && i<n)//�ж�a,b֮���Ƿ�ǽ��ס
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
    double d[MAXN];//��������
    int i,j;
    for(i=0;i<MAXN;i++)
        d[i]=INF;
    d[beg]=0;
    bool ex=true;
    for(i=0;i<pSize&&ex;i++)//����n�κ�n-1��Ч��һ��
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
    for(i=0;i<pSize;i++)//ֻ��ǰ��ĵ�ͺ���ĵ�����
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
