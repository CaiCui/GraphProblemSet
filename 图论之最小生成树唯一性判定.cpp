#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮��С������Ψһ���ж�����
  �㷨��
  1.��ͼ��ÿ���ߣ�ɨ�������ߣ����������ͬȨֵ�ıߣ���Ըñ߽��б�ǣ�
  2.��Kruskal��Prim�����С������
  3.���MST�������MST��δ�������˱�ǵıߣ������ж�MST��Ψһ����������ȥ��������ǵı�����MST�������Ȩֵ��ԭMSTȨֵ��ͬ������ж�MST��Ψһ��
  POJ1679 ����һ����ͨ���������ж�MSTΨһ���
*/
#define MAXN 101
#define MAXM 10000
struct edge{
   int u,v,w;
   int equal; //1��ʾ������ͬȨֵ�ı�
   int used;  //�ڵ�һ����õ�MST�У��Ƿ�����ñߣ�1��ʾ����
   int del;   //���Ƿ�ɾ����1ɾ��
}edges[MAXM];
int parent[MAXN];
int n,m;
bool first; //��һ��MST�ı�־����
void UFSet()
{
    for(int i=0;i<n;i++)parent[i]=-1;
}
int Find(int x)
{
    int s;
    for(s=x;parent[s]>=0;s=parent[s]);
    while(s!=x)
    {
        int tmp=parent[x];
        parent[x]=s;
        x=tmp;
    }
    return s;
}
void Union(int R1,int R2)
{
    int r1=Find(R1),r2=Find(R2);
    int tmp=parent[r1]+parent[r2];
    if(parent[r1]>parent[r2])
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
int cmp(const void *a,const void *b)
{
    edge aa=*(const edge *)a;
    edge bb=*(const edge *)b;
    return aa.w-bb.w;
}
int Kruskal()
{
    int sumweight=0,num=0;
    int u,v;
    UFSet();
    for(int i=0;i<m;i++)
    {
        if(edges[i].del==1)continue;//����ȥ���ı�
        u=edges[i].u;
        v=edges[i].v;
        if(Find(u)!=Find(v))
        {
            sumweight+=edges[i].w;
            num++;
            Union(u,v);
            if(first)
                edges[i].used=1;
        }
        if(num>=n-1)break;
    }
    return sumweight;
}
int main()
{
    int u,v,w;
    int t,i,j,k;
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%d%d",&n,&m);
        for(j=0;j<m;j++)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[j].u=u-1;
            edges[j].v=v-1;
            edges[j].w=w;
            edges[j].equal=0;
            edges[j].del=0;
            edges[j].used=0;
        }
        for(j=0;j<m;j++)//���Ȩֵ��ͬ�ı�
        {
            for(k=0;k<m;k++)
            {
                if(k==j)
                    continue;
                if(edges[k].w==edges[j].w)
                    edges[j].equal=1;
            }
        }
        //�����Ȩֵ����С����
        qsort(edges,m,sizeof(edges[0]),cmp);
        first=true;
        int weight1,weight2;
        weight1=Kruskal();//��һ����MST
        first=false;
        for(j=0;j<m;j++)
        {
            //����ȥ��ԭMST����ͬȨֵ�ı�,ִ���㷨�ĵ�����
            if(edges[j].used&&edges[j].equal)
            {
                edges[j].del=1;
                weight2=Kruskal();
                if(weight1==weight2)
                {
                    printf("Not Unique!\n");
                    break;
                }
                edges[j].del=0;
            }
        }
        if(j>=m)
            printf("%d\n",weight1);

    }
    return 0;
}
