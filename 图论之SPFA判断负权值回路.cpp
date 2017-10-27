#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮����Ȩֵ����ĵ�Դ���·��--SPFA�㷨
  POJ3259 ���涴
  ���壺�ж�һ������Ȩֵ�����������Ƿ���ڸ�Ȩֵ��·
  SPFA�жϷ�����ͳ��ÿ��������ӵĴ������������������N������ڸ�Ȩֵ��·��
  ��ֹSPFA
*/
#define INF 10000000 //�����
#define MAXN 600
struct ArcNode{
  int to;
  int weight;
  ArcNode *next;
};
queue<int>Q;
int N,M,W;
ArcNode *List[MAXN];
int inq[MAXN]; //�����ڶ����б�־
int count1[MAXN]; //ÿ��������Ӵ���
int dist[MAXN],path[MAXN];
bool SPFA(int src)
{
    int i,u;
    ArcNode *temp;
    for(i=1;i<=N;i++)
    {
        dist[i]=INF;
        path[i]=src;
        inq[i]=0;
    }
    dist[src]=0;
    path[src]=src;
    inq[src]++;
    Q.push(src);
    count1[src]++;
    while(!Q.empty())
    {
        u=Q.front();
        Q.pop();
        inq[u]--;
        if(count1[u]>N)return true;
        temp=List[u];
        while(temp!=NULL)
        {
            int v=temp->to;
            if(dist[v]>dist[u]+temp->weight)
            {
                dist[v]=dist[u]+temp->weight;
                path[v]=u;
                if(!inq[v])
                {
                    Q.push(v);
                    inq[v]++;
                    count1[v]++;
                }
            }
            temp=temp->next;
        }
    }
    return false;
}

int main()
{
    int i,j,T;
    int u,v,w;
    scanf("%d",&T);
    for(i=1;i<=T;i++)
    {
        scanf("%d%d%d",&N,&M,&W);
        memset(List,0,sizeof(List));
        memset(inq,0,sizeof(inq));
        memset(count1,0,sizeof(count1));
        while(!Q.empty())
            Q.pop();
        ArcNode *temp;
        for(j=1;j<=M;j++)//����˫���
        {
            scanf("%d%d%d",&u,&v,&w);
            temp=new ArcNode;
            temp->to=v;
            temp->weight=w;
            temp->next=NULL;
            if(List[u]==NULL) List[u]=temp;
            else
            {
                temp->next=List[u];
                List[u]=temp;
            }
            temp=new ArcNode;
            temp->to=u;
            temp->weight=w;
            temp->next=NULL;
            if(List[v]==NULL) List[v]=temp;
            else
            {
                temp->next=List[v];
                List[v]=temp;
            }

        }
        for(j=1;j<=W;j++)
        {
            scanf("%d%d%d",&u,&v,&w);
            temp=new ArcNode;
            temp->to=v;
            temp->weight=-w;
            temp->next=NULL;
            if(List[u]==NULL) List[u]=temp;
            else
            {
                temp->next=List[u];
                List[u]=temp;
            }
        }
        if(SPFA(1))printf("YES\n");
        else
            printf("NO\n");
        for(j=1;j<=N;j++)
        {
            temp=List[j];
            while(temp!=NULL)
            {
                List[j]=temp->next;
                delete temp;
                temp=List[j];
            }
        }
    }
    return 0;
}
