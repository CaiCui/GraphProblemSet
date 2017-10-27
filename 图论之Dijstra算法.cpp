#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮����Ȩֵ�Ǹ����εĵ�Դ���·--Dijkstra�㷨
  ��������������������
  ˼�룺
  ����·�����ȵĵ��������𲽲������·����
  �������������̵�һ��·�����ٲ�����������ȴζ̵�һ�����·�����������ƣ���ɴ�Դ�㵽���������·��������¡�
  ����: dist[k]=min{dist[k],dist[u]+Edge[u][k]}
  ��⣬��v0������������·�����ȡ�
*/
#define INF 10000000
#define MAXN 20
int n;
int Edge[MAXN][MAXN];
int S[MAXN]; //S���ϴ���Ѿ��ҵ����·���Ķ���
int dist[MAXN]; //��Ŵ�Դ��v0����ǰ����i�ľ���
int path[MAXN]; //����·��
void Dijstra(int v0)//�������ͼ��v0������������������·��
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        dist[i]=Edge[v0][i];
        S[i]=0;
        if(i!=v0&&dist[i]<INF)
            path[i]=v0;
        else
            path[i]=-1;
    }
    S[v0]=1;
    dist[v0]=0;//����Դ��
    for(i=0;i<n-1;i++)//ȷ��n-1�����·��
    {
        int min=INF;
        int u=v0;
        //ѡ��ǰ����T�о������·���Ķ���u
        for(j=0;j<n;j++)
        {
            if(!S[j]&&dist[j]<min)
            {
                u=j;
                min=dist[j];
            }
        }
        S[u]=1;//��u���뼯��S����ʾ�Ѿ�����������·��
        //����u,�޸ĸ���һ��T��dist��path������ֵ
        for(k=0;k<n;k++)
        {
            if(!S[k]&&Edge[u][k]<INF&&dist[u]+Edge[u][k]<dist[k])
            {
                dist[k]=dist[u]+Edge[u][k];
                path[k]=u;
            }
        }
    }
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d",&n);
    while(true)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)
            break;
        Edge[u][v]=w;
    }
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(i==j)
          Edge[i][j]=0;
        else if(Edge[i][j]==0)
          Edge[i][j]=INF;
    Dijstra(0);
    int shortest[MAXN];//���·������
    for(i=1;i<n;i++)
    {
        printf("%d\t",dist[i]);//���v0��i�����·��
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
        {
            printf("%d->",shortest[j]);
        }
        printf("%d\n",shortest[0]);
    }

    return 0;
}
