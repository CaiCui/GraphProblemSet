#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之最小生成树唯一性判定！！
  算法：
  1.对图中每条边，扫描其他边，如果存在相同权值的边，则对该边进行标记；
  2.用Kruskal或Prim求解最小生成树
  3.求得MST后，如果该MST中未包含做了标记的边，即可判定MST是唯一；否则，依次去掉包含标记的边再求MST，若求得权值和原MST权值相同，则可判定MST不唯一。
  POJ1679 给定一个连通无向网，判断MST唯一与否
*/
#define MAXN 101
#define MAXM 10000
struct edge{
   int u,v,w;
   int equal; //1表示存在相同权值的边
   int used;  //在第一次求得的MST中，是否包含该边，1表示包含
   int del;   //边是否删除，1删除
}edges[MAXM];
int parent[MAXN];
int n,m;
bool first; //第一求MST的标志变量
void UFSet()
{
    for(int i=0;i<n;i++)parent[i]=-1;
}
int Find(int x)
{
    int s;
    for(s=x;parent[s]>=0;s=parent[s]);
    while(s!=x)
    {
        int tmp=parent[x];
        parent[x]=s;
        x=tmp;
    }
    return s;
}
void Union(int R1,int R2)
{
    int r1=Find(R1),r2=Find(R2);
    int tmp=parent[r1]+parent[r2];
    if(parent[r1]>parent[r2])
    {
        parent[r1]=r2;
        parent[r2]=tmp;
    }
    else
    {
        parent[r2]=r1;
        parent[r1]=tmp;
    }
}
int cmp(const void *a,const void *b)
{
    edge aa=*(const edge *)a;
    edge bb=*(const edge *)b;
    return aa.w-bb.w;
}
int Kruskal()
{
    int sumweight=0,num=0;
    int u,v;
    UFSet();
    for(int i=0;i<m;i++)
    {
        if(edges[i].del==1)continue;//忽略去掉的边
        u=edges[i].u;
        v=edges[i].v;
        if(Find(u)!=Find(v))
        {
            sumweight+=edges[i].w;
            num++;
            Union(u,v);
            if(first)
                edges[i].used=1;
        }
        if(num>=n-1)break;
    }
    return sumweight;
}
int main()
{
    int u,v,w;
    int t,i,j,k;
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%d%d",&n,&m);
        for(j=0;j<m;j++)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[j].u=u-1;
            edges[j].v=v-1;
            edges[j].w=w;
            edges[j].equal=0;
            edges[j].del=0;
            edges[j].used=0;
        }
        for(j=0;j<m;j++)//标记权值相同的边
        {
            for(k=0;k<m;k++)
            {
                if(k==j)
                    continue;
                if(edges[k].w==edges[j].w)
                    edges[j].equal=1;
            }
        }
        //排序边权值，从小到大
        qsort(edges,m,sizeof(edges[0]),cmp);
        first=true;
        int weight1,weight2;
        weight1=Kruskal();//第一次求MST
        first=false;
        for(j=0;j<m;j++)
        {
            //依次去掉原MST中相同权值的边,执行算法的第三步
            if(edges[j].used&&edges[j].equal)
            {
                edges[j].del=1;
                weight2=Kruskal();
                if(weight1==weight2)
                {
                    printf("Not Unique!\n");
                    break;
                }
                edges[j].del=0;
            }
        }
        if(j>=m)
            printf("%d\n",weight1);

    }
    return 0;
}
