#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���·Bellman-ford�㷨�Ľ�--SPFA
  �Ż���BF�㷨��ʱ�临�Ӷȣ�ʹ�ö����Ż�ʵ��BF�㷨
  ÿ�ΰѶ��������У�Ȼ��ȡ����ͷԪ�ؽ����ɳڲ����������ڵĶ����ɳڳɹ�����ӣ��ظ�����������
  ��ʵʵ������һ������Dijkstra��˼�룬ֻ�Ǹ��㷨�����и��ߴ��ڣ�
  �ŵ㣺ʱ�临�Ӷ�ΪO(km),kͨ��Ϊ2��ʾÿ����������ƽ�����������Դ���������
  �Աȣ����㷨��BFS���ƣ���������BFS��ÿ����ֻ�����һ�Σ������㷨�У����е㶼������Ӷ�Σ������޸ġ�
  ʵ�֣�
    ʹ�ó��߱������ *
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
ArcNode *List[MAXN];  //ÿ����ı������ͷָ��
int inq[MAXN];        //ÿ�������Ƿ��ڶ����еı�־
int dist[MAXN],path[MAXN];
void SPFA(int src)
{
    int i,u;
    ArcNode *tmp;
    for(i=0;i<n;i++)//��ʼ��
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
