#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之生成树和最小生成树(复习)
  基于选取最小（排序或堆）边并查集的Kruskal算法
*/
#define MAXN 11
#define MAXM 20
struct edge{
   int u,v,w;
}edges[MAXM];
int parent[MAXN]; //parent[i]为顶点i所在集合中对应的树中的根节点
int n,m;
int i,j;
//优化权值合并的并查集构造
void UFset()
{
    for(i=1;i<=n;i++)
        parent[i]=-1;
}
int Find(int x) //查找并返回x所属集合的根节点
{
   int s;
   for(s=x;parent[s]>=0;s=parent[s]);
   while(s!=x)//路径压缩
   {
       int tmp=parent[x];
       parent[x]=s;
       x=tmp;
   }
   return s;
}
//集合合并
void Union(int R1,int R2)
{
    int r1=Find(R1),r2=Find(R2);//寻找R1,R2根节点
    int tmp=parent[r1]+parent[r2]; //求得两个集合节点个数之和(负数)
    //根据两个集合中元素个数多少拼接，如果R2所在树结点个数>R1所在(注意是负数比较)
    if(parent[r1]>parent[r2]) //加权优化
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

int cmp(const void *a,const void *b)//从小到大
{
    edge aa=*(const edge *)a;
    edge bb=*(const edge *)b;
    return aa.w-bb.w;
}

void Kruscal()
{
    int sumweight=0;//生成树权值
    int num=0;      //已选用的边的数目
    int u,v;
    UFset();
    for(i=0;i<m;i++)
    {
        u=edges[i].u;
        v=edges[i].v;
        if(Find(u)!=Find(v))
        {
            printf("%d %d %d\n",u,v,edges[i].w);
            sumweight+=edges[i].w;
            num++;
            Union(u,v);
        }
        if(num>=n-1)break;
    }
    printf("weight of MST is %d\n",sumweight);
}
int main()
{
    int u,v,w;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        edges[i].u=u;
        edges[i].v=v;
        edges[i].w=w;
    }
    qsort(edges,m,sizeof(edges[0]),cmp);
    Kruscal();
    return 0;
}
