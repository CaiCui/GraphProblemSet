#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮��С������(Prim�㷨ģ��)
  ����˼�룺�Զ���Ϊ������λ������ʼ���������ͨ��ѡ��ǰ���õ���СȨֵ�����ΰ�����������뵽������
  ������Ŵ�1��ʼ
  ���Ӷ�O(n^2)�ʺϳ���ͼ
*/
#define INF 1000000
#define MAXN 21
int n,m;
int Edge[MAXN][MAXN];
int lowcost[MAXN];
int nearvex[MAXN];
void prim(int u0)//��u0����ִ��prim�㷨
{
    int i,j;
    int sumweight=0;  //��������Ȩ��
    for(i=1;i<=n;i++) //��ʼ�������ؼ�����
    {
        lowcost[i]=Edge[u0][i];
        nearvex[i]=u0;
    }
    nearvex[u0]=-1;
    for(i=1;i<n;i++)
    {
        int min=INF;
        int v=-1;
        //��lowcost������Ѱ����Сֵ
        for(j=1;j<=n;j++)
        {
            if(nearvex[j]!=-1 && lowcost[j]<min)
            {
                v=j;
                min=lowcost[j];
            }
        }
        if(v!=-1) //v==-1��ʾû���ҵ�Ȩֵ��С�ı�
        {
            printf("%d %d %d\n",nearvex[v],v,lowcost[v]);
            nearvex[v]=-1;
            sumweight+=lowcost[v];
            for(j=1;j<=n;j++)//���¼����v�Ļ����ϸ������бߵ���СȨֵ
            {
                if(nearvex[j]!=-1 && Edge[v][j]<lowcost[j])
                {
                    lowcost[j]=Edge[v][j];
                    nearvex[j]=v;
                }
            }
        }

    }
    printf("weight of MST is %d\n",sumweight);
}
int main()
{
    int i,j;
    int u,v,w;
    scanf("%d%d",&n,&m);
    memset(Edge,0,sizeof(Edge));
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        Edge[u][v]=Edge[v][u]=w;
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
    {
        if(i==j)Edge[i][j]=0;
        else if (Edge[i][j]==0)Edge[i][j]=INF;
    }
    prim(1);
    return 0;
}
