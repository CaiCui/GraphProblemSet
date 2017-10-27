#include<bits/stdc++.h>
using namespace std;
/*
1.1 The Generation Of A Graph
约定：
    n:图的阶数，即顶点的个数
    m:图的边数
    完全图：m=n*(n-1)/2
    有向完全图:m=n*(n-1)
    度与边的关系：所有点度数之和=图的边数x2
    图的表示:邻接矩阵或邻接表
    数组下标i对应顶点为i+1
其他概念见图论一书
*/
//邻接矩阵建图，并给出各顶点的入度和出度
#define MAXN 100
int Edge[MAXN][MAXN];
int main()
{
    int n,m;
    int i,j;
    int u,v;
    int od,id;
    while(scanf("%d%d",&n,&m)&&m*m+n*n!=0)
    {
        memset(Edge,0,sizeof(Edge));
        for(i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            Edge[u-1][v-1]=1;
        }
        for(i=0;i<n;i++)
        {
            od=0;
            for(j=0;j<n;j++) od+=Edge[i][j];
            if(i==0)printf("%d",od);
            else printf(" %d",od);
        }
        printf("\n");
        for(i=0;i<n;i++)
        {
            id=0;
            for(j=0;j<n;j++)id+=Edge[j][i];
            if(i==0)printf("%d",id);
            else printf(" %d",id);
        }
        printf("\n");
    }
    return 0;
}
