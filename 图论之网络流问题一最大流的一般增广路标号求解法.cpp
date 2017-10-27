#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之网络最大流
  网络流最大流的判定定理：最大流最小割原理
  求解：增广路算法(AP)和预流推进算法(PP)
  1.增广路算法之一般增广路方法--Ford-Fulkerson标号法
  关键：寻找增广路和改进网络流
  Demo:使用标号法输出图中的各个弧的流量和求得的网络最大流
  流程见书
*/
#define MAXN 1000 //顶点个数的最大值
#define INF 9999999 //无穷大
#define MIN(a,b) ((a)<(b)?(a):(b))
struct ArcType{
  int c,f;//边的容量和流量
};
ArcType Edge[MAXN][MAXN];//邻接矩阵
int n,m;
int flag[MAXN]; //顶点状态，-1未标号，0标号未检查，1标号已检查
int prev[MAXN]; //标号法中标号的第一个分量，表示从哪个顶点得到，用于改进流量
int alpha[MAXN]; //标号的第二个分量，用于改进的阿尔法参数
int Queue[MAXN]; //BFS
int v; //队首
int qs,qe;//指针
int i,j;
void ford()
{
    while(true)//标号到不存在可改进路为止
    {
        //顶点状态数组均初始化为-1
        memset(flag,0xff,sizeof(flag));
        memset(prev,0xff,sizeof(prev));
        memset(alpha,0xff,sizeof(alpha));
        //标记源点为已标号未检查点
        flag[0]=0;
        prev[0]=0;
        alpha[0]=INF;
        qs=qe=0;
        Queue[qe]=0;
        qe++;
        while(qs<qe&&flag[n-1]==-1)//队列不空同时汇点未标号
        {
            v=Queue[qs];
            qs++;
            for(i=0;i<n;i++)//检查v的正向和反向“邻接”顶点
            {
                if(flag[i]==-1)//i未标号
                {
                    //正向且流量<容量
                    if(Edge[v][i].c<INF &&Edge[v][i].f<Edge[v][i].c)
                    {
                        flag[i]=0;//已标号未检查
                        prev[i]=v;
                        alpha[i]=MIN(alpha[v],Edge[v][i].c-Edge[v][i].f);
                        Queue[qe]=i;
                        qe++;//入队
                    }
                    //反向且有流量
                    else if(Edge[i][v].c<INF && Edge[i][v].f>0)
                    {
                        flag[i]=0;//已标号未检查
                        prev[i]=-v;
                        alpha[i]=MIN(alpha[v],Edge[i][v].f);
                        Queue[qe]=i;
                        qe++;//入队
                    }
                }
            }
            flag[v]=1;//顶点v已经标号且检查
        }
        //当汇点没有获得标号，或者汇点调整量为0，应该退出while循环
        if(flag[n-1]==-1 || alpha[n-1]==0)break;
        //反向调整
        int k1=n-1,k2=abs(prev[k1]);
        int a=alpha[n-1];//改进量
        while(1)
        {
            if(Edge[k2][k1].f<INF)//正向
                Edge[k2][k1].f=Edge[k2][k1].f+a;
            else//反向
                Edge[k1][k2].f=Edge[k1][k2].f-a;
            if(k2==0)break;//结束调整
            k1=k2;
            k2=abs(prev[k2]);
        }
    }//end of while(true)
    //输出
    int maxFlow=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==0 && Edge[i][j].f<INF)//求出最大流
              maxFlow=maxFlow+Edge[i][j].f;
            if(Edge[i][j].f<INF)
                printf("%d->%d:%d\n",i,j,Edge[i][j].f);
        }
    }
    printf("maxFlow:%d\n",maxFlow);
}
int main()
{
    int u,v,c,f;//弧的起点、终点、容量、流量
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            Edge[i][j].c=Edge[i][j].f=INF;
    }
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d%d",&u,&v,&c,&f);
        Edge[u][v].c=c;
        Edge[u][v].f=f;
    }
    ford();
    return 0;
}
