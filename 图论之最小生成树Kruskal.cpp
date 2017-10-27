#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮����������С������(��ϰ)
  ����ѡȡ��С�������ѣ��߲��鼯��Kruskal�㷨
*/
#define MAXN 11
#define MAXM 20
struct edge{
   int u,v,w;
}edges[MAXM];
int parent[MAXN]; //parent[i]Ϊ����i���ڼ����ж�Ӧ�����еĸ��ڵ�
int n,m;
int i,j;
//�Ż�Ȩֵ�ϲ��Ĳ��鼯����
void UFset()
{
    for(i=1;i<=n;i++)
        parent[i]=-1;
}
int Find(int x) //���Ҳ�����x�������ϵĸ��ڵ�
{
   int s;
   for(s=x;parent[s]>=0;s=parent[s]);
   while(s!=x)//·��ѹ��
   {
       int tmp=parent[x];
       parent[x]=s;
       x=tmp;
   }
   return s;
}
//���Ϻϲ�
void Union(int R1,int R2)
{
    int r1=Find(R1),r2=Find(R2);//Ѱ��R1,R2���ڵ�
    int tmp=parent[r1]+parent[r2]; //����������Ͻڵ����֮��(����)
    //��������������Ԫ�ظ�������ƴ�ӣ����R2������������>R1����(ע���Ǹ����Ƚ�)
    if(parent[r1]>parent[r2]) //��Ȩ�Ż�
        {
           parent[r1]=r2;
           parent[r2]=tmp;
        }
    else
        {
           parent[r2]=r1;
           parent[r1]=tmp;
        }
}

int cmp(const void *a,const void *b)//��С����
{
    edge aa=*(const edge *)a;
    edge bb=*(const edge *)b;
    return aa.w-bb.w;
}

void Kruscal()
{
    int sumweight=0;//������Ȩֵ
    int num=0;      //��ѡ�õıߵ���Ŀ
    int u,v;
    UFset();
    for(i=0;i<m;i++)
    {
        u=edges[i].u;
        v=edges[i].v;
        if(Find(u)!=Find(v))
        {
            printf("%d %d %d\n",u,v,edges[i].w);
            sumweight+=edges[i].w;
            num++;
            Union(u,v);
        }
        if(num>=n-1)break;
    }
    printf("weight of MST is %d\n",sumweight);
}
int main()
{
    int u,v,w;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        edges[i].u=u;
        edges[i].v=v;
        edges[i].w=w;
    }
    qsort(edges,m,sizeof(edges[0]),cmp);
    Kruscal();
    return 0;
}
