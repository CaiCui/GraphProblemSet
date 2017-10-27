#include<bits/stdc++.h>
using namespace std;
/*
  图论之最短路Bellman-ford算法改进--SPFA
  优化了BF算法的时间复杂度，使用队列优化实现BF算法
  每次把顶点加入队列，然后取出队头元素进行松弛操作，若相邻的顶点松弛成功则入队，重复上述操作。
  其实实现中有一点类似Dijkstra的思想，只是该算法允许有负边存在！
  优点：时间复杂度为O(km),k通常为2表示每个顶点的入队平均次数，可以处理负边情形
  对比：该算法和BFS类似，区别在于BFS的每个点只能入队一次，而本算法中，所有点都可以入队多次，反复修改。
  实现：
    使用出边表来求解 *
*/
#define INF 10000000
#define MAXN 10
struct ArcNode{
   int to;
   int weight;
   ArcNode *next;
};
queue<int>Q;
int n;
ArcNode *List[MAXN];  //每个点的边链表表头指针
int inq[MAXN];        //每个顶点是否在队列中的标志
int dist[MAXN],path[MAXN];
void SPFA(int src)
{
    int i,u;
    ArcNode *tmp;
    for(i=0;i<n;i++)//初始化
    {
        dist[i]=INF;
        path[i]=src;
        inq[i]=0;
    }
    dist[src]=0;
    path[src]=src;
    inq[src]++;
    Q.push(src);
    while(!Q.empty())
    {
        u=Q.front();
        Q.pop();
        inq[u]--;
        tmp=List[u];
        while(tmp!=NULL)
        {
            int v=tmp->to;
            if(dist[v]>dist[u]+tmp->weight)
            {
                dist[v]=dist[u]+tmp->weight;
                path[v]=u;
                if(!inq[v])
                {
                    Q.push(v);
                    inq[v]++;
                }
            }
            tmp=tmp->next;
        }
    }
}
int main()
{
    int i,j,u,v,w;
    scanf("%d",&n);
    memset(List,0,sizeof(List));
    ArcNode *temp;
    while(1)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)break;
        temp=new ArcNode;
        temp->to=v;
        temp->weight=w;
        temp->next=NULL;
        if(List[u]==NULL)
            List[u]=temp;
        else
        {
            temp->next=List[u];
            List[u]=temp;
        }
    }
    SPFA(0);
    for(j=0;j<n;j++)
    {
        temp=List[j];
        while(temp!=NULL)
        {
            List[j]=temp->next;
            delete temp;
            temp=List[j];
        }
    }
    int shortest[MAXN];
    for(i=1;i<n;i++)
    {
        printf("%d\t",dist[i]);
        memset(shortest,0,sizeof(shortest));
        int k=0;
        shortest[k]=i;
        while(path[shortest[k]]!=0)
        {
            k++;
            shortest[k]=path[shortest[k-1]];
        }
        k++;
        shortest[k]=0;
        for(j=k;j>0;j--)
            printf("%d->",shortest[j]);
        printf("%d\n",shortest[0]);
    }
    return 0;
}
