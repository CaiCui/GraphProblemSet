#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮����Ȩֵ����ĵ�Դ���·��--Bellman-Ford�㷨
  Ҫ��ͼ�в��ܰ���Ȩֵ�ܺ�Ϊ���Ļ�·������Ȧ
  ��⣺��Դ��v0��������������·��
  �㷨���һϵ�е�dist1[u],dist2[u],dist3[u]...disti[u]..distn-1[u]
  ���յõ�dist(n-1)[u]���Ǵ�v0��u�����·��
  disti[u]:��v0������ྭ�������ɸ�Ȩֵ��·��i���ߵ���u�����·���ĳ���
  ���������Ƽ��㣬�е�����DP˼�룬���Ʒ�������
  ��ʼ��dist1[u]=Edge[v0][u]
        distk[u]=min{distk-1[u],min{distk-1[j]+Edge[j][u],j!=u}}
*/
#define INF 1000000
#define MAXN 8
int n;
int Edge[MAXN][MAXN];
int dist[MAXN];
int path[MAXN];
void BellMan(int v0)
{
    int i,j,k,u;
    for(i=0;i<n;i++)//��ʼ��
    {
        dist[i]=Edge[v0][i];
        if(i!=v0&&dist[i]<INF)path[i]=v0;
        else
            path[i]=-1;
    }
    for(k=2;k<n;k++)//dist������ƣ���1�Ƶ�n-1
    {
        for(u=0;u<n;u++)
        {
            if(u!=v0)
            {
                for(j=0;j<n;j++)
                {
                    if(Edge[j][u]<INF&&dist[j]+Edge[j][u]<dist[u])
                    {
                        dist[u]=dist[j]+Edge[j][u];
                        path[u]=j;
                    }
                }
            }
        }
    }
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d",&n);
    while(1)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)break;
        Edge[u][v]=w;//����ͼ
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        if(i==j)Edge[i][j]=0;
        else if(Edge[i][j]==0)
           Edge[i][j]=INF;
    }
    BellMan(0);
    int shortest[MAXN];//������·�����
    for(i=1;i<n;i++)
    {
        printf("%d\t",dist[i]);
        //�����0�����������·��
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
