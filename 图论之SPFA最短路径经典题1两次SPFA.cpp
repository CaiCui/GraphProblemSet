#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���·Bellman-ford�㷨�Ľ�--SPFA
  POJ 3268 ��ţ�ɶ�
  �ֱ���ru�߱��chu�߱���Ϊ���ݽṹ��ʹ������SPFA������㵽X������ʱ���X����������ʱ��
  ������Ӻ�ȡ�����ļ��ɡ�
*/
#define MAXN 101000
#define INT_MAX 2000000
struct NODE{
  int v;
  int w;
  NODE *next;
}edge[MAXN],redge[MAXN],temp[MAXN*2];//edge��redge�ֱ�Ϊ����ͼ�ͷ���ͼ
int pos=0;
int ecost[MAXN];
int N,M,W,src,Q[MAXN]; //������Qģ�����
bool visited[MAXN];
//SPFA�㷨��direction����0����1��
void SPFA(int direction)
{
    int h,t,u,i;
    NODE *ptr;
    h=0,t=1;
    memset(visited,0,sizeof(visited));
    for(i=0;i<=N;i++)
        ecost[i]=INT_MAX;
    Q[0]=src;
    ecost[src]=0;
    while(h!=t)
    {
        u=Q[h];
        h++;
        visited[u]=false;
        if(direction==0)ptr=edge[u].next;//�����src�����������̾��룬���߱�
        else
            ptr=redge[u].next;//����Ӹ����㵽src����̾��룬��߱�
        while(ptr)
        {
            if(ecost[ptr->v]>ecost[u]+ptr->w)
            {
                ecost[ptr->v]=ecost[u]+ptr->w;
                if(!visited[ptr->v])
                {
                    Q[t]=ptr->v;
                    t++;
                    visited[ptr->v]=true;
                }
            }
            ptr=ptr->next;
        }
    }
}
void Insert(const int &x,const int &y,const int &w)//���ڽӱ����,������
{
    NODE *ptr=&temp[pos++];
    ptr->v=y;
    ptr->w=w;
    ptr->next=edge[x].next;
    edge[x].next=ptr;
    ptr=&temp[pos++];
    ptr->v=x;
    ptr->w=w;
    ptr->next=redge[y].next;
    redge[y].next=ptr;
}
int main()
{
    int i,x,y,w;
    int ans[MAXN],MaxTime;//�ۼӵ����ʱ������ʱ�����ֵ
    while(scanf("%d%d%d",&N,&M,&src)!=EOF)
    {
        pos=0;
        for(i=0;i<=N;i++)
        {
            edge[i].next=NULL;
            redge[i].next=NULL;
        }
        for(i=0;i<M;i++)
        {
            scanf("%d%d%d",&x,&y,&w);
            Insert(x,y,w);
        }
        MaxTime=0;
        memset(ans,0,sizeof(ans));
        //���������·
        SPFA(0);
        for(i=1;i<=N;i++)
        {
            if(i!=src)
            {
                ans[i]+=ecost[i];
                cout<<ecost[i]<<endl;
            }
        }
        //
        SPFA(1);
         for(i=1;i<=N;i++)
        {
            if(i!=src)
            {
                ans[i]+=ecost[i];
                 cout<<ecost[i]<<endl;
                if(ans[i]>MaxTime)
                    MaxTime=ans[i];
            }
        }
        printf("%d\n",MaxTime);
    }
    return 0;
}
