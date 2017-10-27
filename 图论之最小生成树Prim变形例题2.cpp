#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮Prim
  ZOJ2158 ������룬������ͼ�����С������
*/
#define INF 1000000
#define MAXN 2000
#define CODELEN 7 //���볤��
int N;
char codes[MAXN][CODELEN+3]; //�洢�������ͱ���
int d[MAXN][MAXN]; //ÿ�Կ������ͼ�ľ���
int lowcost[MAXN]; //��С��������������
int min_tree()
{
    int i,j,k;
    int dist;
    memset(d,0,sizeof(d));
    for(i=0;i<N;i++)//���d[][]����
        for(j=i+1;j<N;j++)
    {
        dist=0;
        for(k=0;k<7;k++)
          dist+=codes[i][k]!=codes[j][k];//����
        d[i][j]=d[j][i]=dist;
    }
    //Prim����СȨֵ
    int sum=0;
    lowcost[0]=-1;
    for(i=1;i<N;i++)
        lowcost[i]=d[0][i];
    for(i=1;i<N;i++)
    {
        int min=INF;
        for(k=0;k<N;k++)
        {
            if(lowcost[k]!=-1&&lowcost[k]<min)
            {
                j=k;
                min=lowcost[k];
            }
        }
        sum+=min;
        lowcost[j]=-1;
        for(k=0;k<N;k++)
        {
            if(d[j][k]<lowcost[k])
                lowcost[k]=d[j][k];
        }
    }
    return sum;
}
int main()
{
    int i;
    while(true)
    {
        scanf("%d",&N);
        if(N==0)break;
        for(i=0;i<N;i++)
            scanf("%s",codes[i]);
        i=min_tree();
        printf("The HPQ is %d\n",i);
    }
    return 0;
}
