#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���������
  ��������������ж������������С��ԭ��
  ��⣺����·�㷨(AP)��Ԥ���ƽ��㷨(PP)
  1.����·�㷨֮һ������·����--Ford-Fulkerson��ŷ�
  �ؼ���Ѱ������·�͸Ľ�������
  Demo:ʹ�ñ�ŷ����ͼ�еĸ���������������õ����������
  ���̼���
*/
#define MAXN 1000 //������������ֵ
#define INF 9999999 //�����
#define MIN(a,b) ((a)<(b)?(a):(b))
struct ArcType{
  int c,f;//�ߵ�����������
};
ArcType Edge[MAXN][MAXN];//�ڽӾ���
int n,m;
int flag[MAXN]; //����״̬��-1δ��ţ�0���δ��飬1����Ѽ��
int prev[MAXN]; //��ŷ��б�ŵĵ�һ����������ʾ���ĸ�����õ������ڸĽ�����
int alpha[MAXN]; //��ŵĵڶ������������ڸĽ��İ���������
int Queue[MAXN]; //BFS
int v; //����
int qs,qe;//ָ��
int i,j;
void ford()
{
    while(true)//��ŵ������ڿɸĽ�·Ϊֹ
    {
        //����״̬�������ʼ��Ϊ-1
        memset(flag,0xff,sizeof(flag));
        memset(prev,0xff,sizeof(prev));
        memset(alpha,0xff,sizeof(alpha));
        //���Դ��Ϊ�ѱ��δ����
        flag[0]=0;
        prev[0]=0;
        alpha[0]=INF;
        qs=qe=0;
        Queue[qe]=0;
        qe++;
        while(qs<qe&&flag[n-1]==-1)//���в���ͬʱ���δ���
        {
            v=Queue[qs];
            qs++;
            for(i=0;i<n;i++)//���v������ͷ����ڽӡ�����
            {
                if(flag[i]==-1)//iδ���
                {
                    //����������<����
                    if(Edge[v][i].c<INF &&Edge[v][i].f<Edge[v][i].c)
                    {
                        flag[i]=0;//�ѱ��δ���
                        prev[i]=v;
                        alpha[i]=MIN(alpha[v],Edge[v][i].c-Edge[v][i].f);
                        Queue[qe]=i;
                        qe++;//���
                    }
                    //������������
                    else if(Edge[i][v].c<INF && Edge[i][v].f>0)
                    {
                        flag[i]=0;//�ѱ��δ���
                        prev[i]=-v;
                        alpha[i]=MIN(alpha[v],Edge[i][v].f);
                        Queue[qe]=i;
                        qe++;//���
                    }
                }
            }
            flag[v]=1;//����v�Ѿ�����Ҽ��
        }
        //�����û�л�ñ�ţ����߻�������Ϊ0��Ӧ���˳�whileѭ��
        if(flag[n-1]==-1 || alpha[n-1]==0)break;
        //�������
        int k1=n-1,k2=abs(prev[k1]);
        int a=alpha[n-1];//�Ľ���
        while(1)
        {
            if(Edge[k2][k1].f<INF)//����
                Edge[k2][k1].f=Edge[k2][k1].f+a;
            else//����
                Edge[k1][k2].f=Edge[k1][k2].f-a;
            if(k2==0)break;//��������
            k1=k2;
            k2=abs(prev[k2]);
        }
    }//end of while(true)
    //���
    int maxFlow=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==0 && Edge[i][j].f<INF)//��������
              maxFlow=maxFlow+Edge[i][j].f;
            if(Edge[i][j].f<INF)
                printf("%d->%d:%d\n",i,j,Edge[i][j].f);
        }
    }
    printf("maxFlow:%d\n",maxFlow);
}
int main()
{
    int u,v,c,f;//������㡢�յ㡢����������
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            Edge[i][j].c=Edge[i][j].f=INF;
    }
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d%d",&u,&v,&c,&f);
        Edge[u][v].c=c;
        Edge[u][v].f=f;
    }
    ford();
    return 0;
}
