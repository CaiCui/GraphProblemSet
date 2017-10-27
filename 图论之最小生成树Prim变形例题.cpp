#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之最小生成树Prim
  ZOJ1586
  不需要记录路径，只需要记录权值，计算cost将lowcost和nearvex数组合二为一
*/
#define MAX 1000000
int Edge[1010][1010];
int adapter[1010]; //适配器价格
int lowcost[1010]; //lowcost+nearvex数组
int t,n;
void init()
{
    int i,k;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&adapter[i]);
    for(i=0;i<n;i++)
    {
        for(k=0;k<n;k++)
        {
            scanf("%d",&Edge[i][k]);
            if(i==k)
               Edge[i][k]=MAX;
            else
               Edge[i][k]+=adapter[i]+adapter[k];

        }
    }
    memset(lowcost,0,sizeof(lowcost));
}
void prim()
{
    int i,k;
    int sum=0;
    lowcost[0]=-1; //从顶点0开始构造最小生成树
    for(i=1;i<n;i++)
    {
        lowcost[i]=Edge[0][i];
    }
    for(i=1;i<n;i++)
    {
        int min=MAX,j;
        for(k=0;k<n;k++)//搜索当前可用的权值最小的边
        {
            if(lowcost[k]!=-1 && lowcost[k]<min)
            {
                j=k;
                min=lowcost[k];
            }
        }
        sum+=min;
        lowcost[j]=-1;//引入顶点j至T集合
        for(k=0;k<n;k++)
        {
            if(Edge[j][k]<lowcost[k])
                lowcost[k]=Edge[j][k];
        }
    }
    printf("%d\n",sum);
}
int main()
{
    scanf("%d",&t); //测试数据的个数
    for(int i=0;i<t;i++)
    {
        init();
        prim();
    }
    return 0;
}
