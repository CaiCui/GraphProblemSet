#include<bits/stdc++.h>
using namespace std;
/*
1.1 The Generation Of A Graph
Լ����
    n:ͼ�Ľ�����������ĸ���
    m:ͼ�ı���
    ��ȫͼ��m=n*(n-1)/2
    ������ȫͼ:m=n*(n-1)
    ����ߵĹ�ϵ�����е����֮��=ͼ�ı���x2
    ͼ�ı�ʾ:�ڽӾ�����ڽӱ�
    �����±�i��Ӧ����Ϊi+1
���������ͼ��һ��
*/
//�ڽӾ���ͼ�����������������Ⱥͳ���
#define MAXN 100
int Edge[MAXN][MAXN];
int main()
{
    int n,m;
    int i,j;
    int u,v;
    int od,id;
    while(scanf("%d%d",&n,&m)&&m*m+n*n!=0)
    {
        memset(Edge,0,sizeof(Edge));
        for(i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            Edge[u-1][v-1]=1;
        }
        for(i=0;i<n;i++)
        {
            od=0;
            for(j=0;j<n;j++) od+=Edge[i][j];
            if(i==0)printf("%d",od);
            else printf(" %d",od);
        }
        printf("\n");
        for(i=0;i<n;i++)
        {
            id=0;
            for(j=0;j<n;j++)id+=Edge[j][i];
            if(i==0)printf("%d",id);
            else printf(" %d",id);
        }
        printf("\n");
    }
    return 0;
}
