#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���ж��������·��--Floyd�㷨
  ZOJ1952  �������� �����С�ɴ�·�����Ͻ�
  Flyod���Ʊ���2��
  A(-1)[i][j]=Edge[i][j]
  A(k)[i][j]=max{A(k-1)[i][j],min(A(k-1)[i][k],A(k-1)[k][j]),k=0,1...n-1}

*/
#define MAXCITIES 256
#define INF 10000000
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
int kase=0;
int n,r;
int w[MAXCITIES][MAXCITIES];
char city[MAXCITIES][30];
char start[30],dest[30];
int numcities;
//��ӳ���������
int index(char *s)
{
    int i;
    for(i=0;i<numcities;i++)
    {
        if(!strcmp(city[i],s))
            return i;
    }
    strcpy(city[i],s);
    numcities++;
    return i;
}
int read_case()//��������
{
    int i,j,k,limit;
    scanf("%d%d",&n,&r);
    if(n==0)return 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            w[i][j]=0;//��ʼ���ڽӾ���
    }
    for(i=0;i<n;i++)
        w[i][i]=INF;
    numcities=0;
    //�����·����
    for(k=0;k<r;k++)
    {
        scanf("%s%s%d",start,dest,&limit);
        i=index(start);
        j=index(dest);
        w[i][j]=w[j][i]=limit;
    }
    //��������յ�
    scanf("%s%s",start,dest);
    return 1;
}
void solve_case()
{
    int i,j,k;
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                w[i][j]=MAX(w[i][j],MIN(w[i][k],w[k][j]));
            }
        }
    }
    i=index(start);
    j=index(dest);
    printf("Scenario $%d\n",++kase);
    printf("%d tons\n\n",w[i][j]);
}
int main()
{
    while(read_case())
        solve_case();
    return 0;
}
