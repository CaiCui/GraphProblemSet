#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮��С������Prim
  ZOJ1586
  ����Ҫ��¼·����ֻ��Ҫ��¼Ȩֵ������cost��lowcost��nearvex����϶�Ϊһ
*/
#define MAX 1000000
int Edge[1010][1010];
int adapter[1010]; //�������۸�
int lowcost[1010]; //lowcost+nearvex����
int t,n;
void init()
{
    int i,k;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&adapter[i]);
    for(i=0;i<n;i++)
    {
        for(k=0;k<n;k++)
        {
            scanf("%d",&Edge[i][k]);
            if(i==k)
               Edge[i][k]=MAX;
            else
               Edge[i][k]+=adapter[i]+adapter[k];

        }
    }
    memset(lowcost,0,sizeof(lowcost));
}
void prim()
{
    int i,k;
    int sum=0;
    lowcost[0]=-1; //�Ӷ���0��ʼ������С������
    for(i=1;i<n;i++)
    {
        lowcost[i]=Edge[0][i];
    }
    for(i=1;i<n;i++)
    {
        int min=MAX,j;
        for(k=0;k<n;k++)//������ǰ���õ�Ȩֵ��С�ı�
        {
            if(lowcost[k]!=-1 && lowcost[k]<min)
            {
                j=k;
                min=lowcost[k];
            }
        }
        sum+=min;
        lowcost[j]=-1;//���붥��j��T����
        for(k=0;k<n;k++)
        {
            if(Edge[j][k]<lowcost[k])
                lowcost[k]=Edge[j][k];
        }
    }
    printf("%d\n",sum);
}
int main()
{
    scanf("%d",&t); //�������ݵĸ���
    for(int i=0;i<t;i++)
    {
        init();
        prim();
    }
    return 0;
}
