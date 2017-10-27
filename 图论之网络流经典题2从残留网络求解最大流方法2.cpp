#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���������
  POJ1273 ��ˮ��
  ��ȫ��������ģ�⣬��������
*/
#define MAXN 210
struct Matrix{
  int c,f;//����������
};
Matrix Edge[MAXN][MAXN];//������������
int M,N;//���ͽڵ�
int s,t;//Դ��ͻ��
int residual[MAXN][MAXN]; //��������
int qu[MAXN*MAXN],qs,qe;//���У���ͷ�Ͷ�β
int pre[MAXN]; //����·�϶���i��ǰһ��
int vis[MAXN]; //���ʱ��
int maxflow,min_augment;//������͸Ľ���
void find_argument_path()//BFS�������·
{
    int i,cu;
    memset(vis,0,sizeof(vis));
    memset(residual,0,sizeof(residual));
    memset(pre,0,sizeof(pre));
    //��Ԫ�ؽ���
    qs=0;
    qu[qs]=s;
    pre[s]=s;
    vis[s]=1;
    qe=1;
    while(qs<qe&&pre[t]==0)
    {
        cu=qu[qs];
        for(i=1;i<=N;i++)
        {
            if(vis[i]==0)
            {
               if(Edge[cu][i].c-Edge[cu][i].f>0)//�����
               {
                   residual[cu][i]=Edge[cu][i].c-Edge[cu][i].f;//��������
                   pre[i]=cu;
                   qu[qe++]=i;
                   vis[i]=1;
               }
               else if(Edge[i][cu].f>0)//�����
               {
                   residual[cu][i]=Edge[i][cu].f;
                   pre[i]=cu;
                   vis[i]=1;
                   qu[qe++]=i;
               }
            }
        }
        qs++;
    }
}
void augment_flow()//����ɸĽ���
{
    int i=t,j;
    if(pre[i]==0)//��㲻�ɸĽ�
    {
        min_augment=0;
        return;
    }
    j=0x7fffffff;
    while(i!=s)//��ɸĽ�����Сֵ
    {
        if(residual[pre[i]][i]<j)
            j=residual[pre[i]][i];
        i=pre[i];
    }
    min_augment=j;
}
void update_flow()//��������
{
     int i=t;
     if(pre[i]==0)return;
     while(i!=s)
     {
         if(Edge[pre[i]][i].c-Edge[pre[i]][i].f>0)
            Edge[pre[i]][i].f+=min_augment;
         else if(Edge[i][pre[i]].f>0)
            //Edge[pre[i]][i].f+=min_augment;�������Ǿ䶼����ac,Ч��һ���������Ƿ��������������൱��ͬ��������������������ȼ۵ģ���
            Edge[i][pre[i]].f-=min_augment;
         i=pre[i];
     }
}
void solve()//���
{
    s=1;
    t=N;
    maxflow=0;
    while(true)
    {
        find_argument_path();
        augment_flow();
        maxflow+=min_augment;
        if(min_augment>0)
            update_flow();
        else
            return;
    }
}
int main()
{
    int i;
    int u,v,c;
    while(scanf("%d%d",&M,&N)!=EOF)
    {
        memset(Edge,0,sizeof(Edge));
        for(i=0;i<M;i++)
        {
            scanf("%d%d%d",&u,&v,&c);
            Edge[u][v].c+=c;
        }
        solve();
        printf("%d\n",maxflow);
    }
    return 0;
}
