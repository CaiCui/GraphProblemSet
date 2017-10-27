#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���ж��������·��--Floyd�㷨ģ��
  DP˼���������
  ���ã������������Ȩֵ��·������������и��ߣ���Bellman-Ford��������һ��
*/
#define INF 10000000
#define MAXN 8
int n;
int Edge[MAXN][MAXN];
int A[MAXN][MAXN],path[MAXN][MAXN];
void Floyd()
{
   int i,j,k;
   for(i=0;i<n;i++)
   {
       for(j=0;j<n;j++)
       {
           A[i][j]=Edge[i][j];
           if(i!=j&&A[i][j]<INF)path[i][j]=i;
           else
            path[i][j]=-1;
       }
   }
   //����ѭ������,��A(-1)���Ƶ�A(0),.....A(n-1)
   for(k=0;k<n;k++)//k�м��ö��
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(k==i||k==j)continue;
                if(A[i][k]+A[k][j]<A[i][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=path[k][j];//��¼�µ�j��ǰһ��������
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
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            Edge[i][j]=INF;
    }
    for(i=0;i<n;i++)
        Edge[i][i]=0;
    while(1)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==-1&&v==-1&&w==-1)break;
        Edge[u][v]=w;
    }
    Floyd();
    int shortest[MAXN];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==j)continue;
            printf("%d=>%d\t%d\t",i,j,A[i][j]);
            memset(shortest,0,sizeof(shortest));
            int k=0;
            shortest[k]=j;
            while(path[i][shortest[k]]!=i)
            {
                k++;
                shortest[k]=path[i][shortest[k-1]];
            }
            k++;
            shortest[k]=i;
            for(int t=k;t>0;t--)
                printf("%d->",shortest[t]);
            printf("%d\n",shortest[0]);
        }
    }
    return 0;
}
