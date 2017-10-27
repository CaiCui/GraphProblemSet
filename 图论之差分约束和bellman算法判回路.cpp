#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���Լ��ϵͳ
  ���Լ��ϵͳ����ת����һ�������������������⣬Ȼ��ͨ�����һ�ε�Դ���·�����ɵó�������Լ������ʽ�Ľ⣬
  ��Ҳ�����·������Ļ�������
  ���Լ��DEMOCODE
  ZOJ2770 ������Ӫ ������Լ������ʽ��ת��Ϊͼ������BellMan-Ford������·��
*/
#define INF 9999999
#define NMAX 1001
#define EMAX 23000
int n;
int m;
int c[NMAX];//��i����Ӫ�����c[i]��ʿ��
int dist[NMAX];//��Դ�㵽�����������·������(Դ��ΪSn)
int d[NMAX];//ǰi����Ӫ�����ܺ�
int ei; //�����
struct eg{
  int u,v,w;
}edges[EMAX];
void init()
{
    ei=0;
    int i;
    //����Դ���⣬����������̾����ʼ��ΪINF
    for(i=0;i<=n;i++)
        dist[i]=INF;
    d[0]=0;
    dist[n]=0;
}
//�������Դ��ɴ�ĸ�Ȩֵ��·������false
bool bellman_ford()
{
   int i,k,t;
   //�㷨ִ��N-1�Σ�N��ʾ������������ڱ����У������0���㣬���Զ�����Ϊn+1
   for(i=0;i<n;i++)
   {
       for(k=0;k<ei;k++)
       {
           t=dist[edges[k].u]+edges[k].w;
           if(dist[edges[k].u]!=INF&&t<dist[edges[k].v])
           {
               dist[edges[k].v]=t;
           }
       }
   }
   //�жϻ�·����������һ��ÿ���ߵļ�飬�жϼ���ñߺ��Ƿ��ʹ·�������̣���������ڻ�
   for(k=0;k<ei;k++)
   {
       if(dist[edges[k].u]!=INF&&dist[edges[k].u]+edges[k].w<dist[edges[k].v])
        return false;
   }
   return true;
}
int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        init();
        int i,u,v,w;
        for(i=1;i<=n;i++)//���첻��ʽ��A����n���
        {
           scanf("%d",&c[i]);
           edges[ei].u=i-1;
           edges[ei].v=i;
           edges[ei].w=c[i];//�����<i-1,i>,ȨֵΪCi
           ei++;
           edges[ei].u=i;
           edges[ei].v=i-1;
           edges[ei].w=0;//�����<i,i-1>,ȨֵΪ0
           ei++;
           d[i]=c[i]+d[i-1];
        }
        for(i=0;i<m;i++)//���첻��ʽ��B����m���
        {
              scanf("%d %d %d",&u,&v,&w);
              edges[ei].u=v;
              edges[ei].v=u-1;
              edges[ei].w=-w;
              ei++;
              edges[ei].u=u-1;
              edges[ei].v=v;
              edges[ei].w=d[v]-d[u-1];
              ei++;
        }
        if(!bellman_ford())
            printf("Bad Estimations\n");
        else
            printf("%d\n",dist[n]-dist[0]);
    }
    return 0;
}
