#include<bits/stdc++.h>
using namespace std;
/*
  图论之Prim
  ZOJ2158 编码距离，构建好图求解最小生成树
*/
#define INF 1000000
#define MAXN 2000
#define CODELEN 7 //编码长度
int N;
char codes[MAXN][CODELEN+3]; //存储卡车类型编码
int d[MAXN][MAXN]; //每对卡车类型间的距离
int lowcost[MAXN]; //最小成生树辅助数组
int min_tree()
{
    int i,j,k;
    int dist;
    memset(d,0,sizeof(d));
    for(i=0;i<N;i++)//求解d[][]数组
        for(j=i+1;j<N;j++)
    {
        dist=0;
        for(k=0;k<7;k++)
          dist+=codes[i][k]!=codes[j][k];//技巧
        d[i][j]=d[j][i]=dist;
    }
    //Prim求最小权值
    int sum=0;
    lowcost[0]=-1;
    for(i=1;i<N;i++)
        lowcost[i]=d[0][i];
    for(i=1;i<N;i++)
    {
        int min=INF;
        for(k=0;k<N;k++)
        {
            if(lowcost[k]!=-1&&lowcost[k]<min)
            {
                j=k;
                min=lowcost[k];
            }
        }
        sum+=min;
        lowcost[j]=-1;
        for(k=0;k<N;k++)
        {
            if(d[j][k]<lowcost[k])
                lowcost[k]=d[j][k];
        }
    }
    return sum;
}
int main()
{
    int i;
    while(true)
    {
        scanf("%d",&N);
        if(N==0)break;
        for(i=0;i<N;i++)
            scanf("%s",codes[i]);
        i=min_tree();
        printf("The HPQ is %d\n",i);
    }
    return 0;
}
