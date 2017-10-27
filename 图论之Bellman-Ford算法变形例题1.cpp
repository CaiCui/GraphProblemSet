#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮����Ȩֵ����ĵ�Դ���·��--Bellman-Ford�㷨
  �ڽӱ� ����ʹ���Ӷȱ�ΪO(n^2)���ڽӾ���ΪO(n^3)
  Bellman-Ford��������·��
  ZOJ1092 �׻�
  ���ñ���������˼�����n�Ρ���ΪҪ�ص�ԭ�㣬��ÿ����ͬ��ִ�У��ж��Ƿ��н⡣
*/
#define maxn 50
#define maxm 1000
#define max(a,b) ((a)>(b)?(a):(b))
struct exchange{
   int ci,cj;
   double cij;
}ex[maxm];
int i,j,k;
int n,m;
char name[maxn][20],a[20],b[20];
double x;
double maxdist[maxn];
int flag;
int kase=0;
int readcase()
{
    scanf("%d",&n);
    if(n==0)return 0;
    for(i=0;i<n;i++)
        scanf("%s",name[i]);
    scanf("%d",&m);
    for(i=0;i<m;i++)//�������
    {
        scanf("%s %lf %s",a,&x,b);
        for(j=0;strcmp(a,name[j]);j++)
            ;
        for(k=0;strcmp(b,name[k]);k++)
            ;
        ex[i].ci=j;
        ex[i].cj=k;
        ex[i].cij=x;
    }
    return 1;
}
//����v0�����ֻص�v0���·��
void bellman(int v0)
{
        memset(maxdist,0,sizeof(maxdist));
        maxdist[v0]=1;
        for(k=1;k<=n;k++)//��maxdist[0]���Ƶ�n
        {
            for(i=0;i<m;i++)
            {
                if(maxdist[ex[i].ci]*ex[i].cij>maxdist[ex[i].cj])//�ж�ÿ���ߣ��������ܷ�ʹ����������
                    maxdist[ex[i].cj]=maxdist[ex[i].ci]*ex[i].cij;
            }
        }
        if(maxdist[v0]>1.0)flag=1;
}
int main()
{

    while(readcase())
        {
            flag=0;
            for(i=0;i<n&&!flag;i++)
                {
                    bellman(i);
                }
            if(flag)
                printf("Case %d:Yes\n",++kase);
            else
                printf("Case %d:No\n",++kase);
        }
    return 0;
}
