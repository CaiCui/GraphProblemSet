#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���ϵͳԼ��
  ZOJ1508 ����
  ����--����Լ���������д���ͬʱ����bellman-ford�㷨����dist[]����û�б仯ʱ���㷨�Ϳ���ֹͣ
  ����ؼ�: ���������Сֵ�����ֵ֮�����һ�����·�����ȡ�
  �����±꾹Ȼ����Ϊ��ֵҲ�ܷ��ʼ���
*/
#define inf 999999
#define EMAX 50002
struct e{
  int u,v,w;//����յ�Ȩֵ
}edges[EMAX];
int n;
int dist[EMAX];
int mn;//����������˵���Сֵ
int mx;//���������Ҷ˵����ֵ
void init()
{
    int i;
    for(i=0;i<EMAX;i++)//��Դ�㵽����������·�����ȳ�ʼ��Ϊ0,��ΪSi-Smx<=0,������
        dist[i]=0;
    mx=1;
    mn=inf;

}
void bellman_ford()
{
    int i,t;
    int f=1;//��ǰ�����ı�־����
    //���ĳ��û�в���·�����ɳڣ�����ǰ����
    while(f)
    {
        f=0;
        for(i=0;i<n;i++)
        {
            t=dist[edges[i].u]+edges[i].w;
            if(t<dist[edges[i].v])
            {
                dist[edges[i].v]=t;
                f=1;
            }
        }

        //���ݵڶ���Լ�������޸�dist
        for(i=mn;i<=mx;i++)
        {
            t=dist[i-1]+1;
            if(dist[i]>t)
            {
                dist[i]=t;
                f=1;
            }
        }
        //���ݵ�����Լ�������޸�dist
        for(i=mx;i>=mn;i--)
        {
            t=dist[i];
            if(dist[i-1]>t)
            {
                dist[i-1]=t;
                f=1;
            }
        }

    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        init();
        int i,u,v,w;
        for(i=0;i<n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[i].u=v;
            edges[i].v=u-1;
            edges[i].w=-w;
            //������˵������Сֵ
            if(mn>u)mn=u;
            if(mx<v)mx=v;

        }
        bellman_ford();
        printf("%d\n",dist[mx]-dist[mn-1]);
    }
    return 0;
}
