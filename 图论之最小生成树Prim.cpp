#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之最小生成树(Prim算法模板)
  基本思想：以顶点为主导地位，从起始顶点出发，通过选择当前可用的最小权值边依次把其他顶点加入到生成树
  顶点序号从1开始
  复杂度O(n^2)适合稠密图
*/
#define INF 1000000
#define MAXN 21
int n,m;
int Edge[MAXN][MAXN];
int lowcost[MAXN];
int nearvex[MAXN];
void prim(int u0)//从u0出发执行prim算法
{
    int i,j;
    int sumweight=0;  //生成树的权重
    for(i=1;i<=n;i++) //初始化两个关键数组
    {
        lowcost[i]=Edge[u0][i];
        nearvex[i]=u0;
    }
    nearvex[u0]=-1;
    for(i=1;i<n;i++)
    {
        int min=INF;
        int v=-1;
        //在lowcost数组中寻找最小值
        for(j=1;j<=n;j++)
        {
            if(nearvex[j]!=-1 && lowcost[j]<min)
            {
                v=j;
                min=lowcost[j];
            }
        }
        if(v!=-1) //v==-1表示没有找到权值最小的边
        {
            printf("%d %d %d\n",nearvex[v],v,lowcost[v]);
            nearvex[v]=-1;
            sumweight+=lowcost[v];
            for(j=1;j<=n;j++)//在新加入的v的基础上更新所有边的最小权值
            {
                if(nearvex[j]!=-1 && Edge[v][j]<lowcost[j])
                {
                    lowcost[j]=Edge[v][j];
                    nearvex[j]=v;
                }
            }
        }

    }
    printf("weight of MST is %d\n",sumweight);
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(Edge,0,sizeof(Edge));
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        Edge[u][v]=Edge[v][u]=w;
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
    {
        if(i==j)Edge[i][j]=0;
        else if (Edge[i][j]==0)Edge[i][j]=INF;
    }
    prim(1);
    return 0;
}
