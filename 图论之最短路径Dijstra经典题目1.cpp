#include<iostream>
#include<cstdio>
using namespace std;
/*
  ͼ��֮����Ȩֵ�Ǹ����εĵ�Դ���·--Dijkstra�㷨
   ZOJ 1298 ����ŵ����ЧӦ
   ����
   ������
   �����������
   ��һ��������µ��ǹؼ��ƣ���ʱֻ��Ҫ�����һ���Ƶ�ÿ���ؼ��Ƶ����·������ô����Ǹ����·�����ǽ����
   �ڶ���������µ������Źؼ���֮�����ͨ�ƣ���ʱʱ��Ϊ�������Źؼ��Ƶ�ʱ���һ�룬�ټ��������������֮�������ʱ���һ�룻
   ����ж�����������أ�
   ��ʵ���������һ���Ƶ�ÿ���ؼ��Ƶ����·����Ȼ���ҳ����·�������ļ�ΪMx1,
   Ȼ�����ÿ����ͨ�ƣ�Ҳ����ÿ������ȫ������Ҫ��ʱ�䣬���㷽����(time[i]+time[j]+Edge[i][j])/2������time[i]��ʾ�ӵ�һ���Ƶ��˹ؼ���
   i�����·�����ȣ�Edge[][]�ͱ�ʾ�ؼ���i��j֮���ʱ��(����������ͨ����ȫ����ʱ�䣬Ҳ���Ǳ�<i,j>��Ȩֵ),��ΪMx2;
   ���Mx2>Mx1��˵���ǵڶ��������ԭ���Զ��׼���Mx2>Mx1˵���յ㲻�ǹؼ��ƣ�˵��������ͨ��Ҳ����ĳ�ؼ���i,j֮�仹�б�û���꣬
   ���Լ��Ϻ�Ŵ��ڵ������ؼ��Ƶ����·�������ֵ.
*/
#define MAXN 500
#define INF 100000
int n,m;
int Edge[MAXN][MAXN]; //ͼ���ڽӾ���
int caseno=1; //�������ݵ����
int time[MAXN]; //��i���ƣ�����i���ڵ㵹�µ�ʱ��
int S[MAXN]; //S[]��ʾ�ؼ���i����ʱ���Ƿ��Ѿ����㣬��Dijkstra�㷨�е���������·���ڵ�ļ���
void solve_case()
{
    int i,j,k;
    //Dijkstra
    for(i=0;i<n;i++)
    {
        time[i]=Edge[0][i];
        S[i]=0;
    }
    time[0]=0;
    S[0]=1;
    for(i=0;i<n-1;i++)
    {
        int min=INF,u=0;
        for(j=0;j<n;j++)
        {
            if(!S[j] &&time[j]<min)
            {
                u=j;
                min=time[j];
            }
        }
        S[u]=1;
        for(k=0;k<n;k++)//����time[]
        {
            if(!S[k] && Edge[u][k]<INF && time[u]+Edge[u][k]<time[k])
                {
                    time[k] = time[u] + Edge[u][k];
                }
        }
    }
    double maxtime1=-INF;
    int pos;//���λ��
    for(i=0;i<n;i++)//�������maxtime1
    {
        if(time[i]>maxtime1)
        {
            maxtime1=time[i];
            pos=i;
        }
    }

    double maxtime2=-INF,t; //ÿ����ͨ�Ƶ��µ�ʱ�䣬��ÿ������ȫ���µ�ʱ��,������ֵ��λ��
    int pos1,pos2;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        t = (time[i]+time[j]+Edge[i][j])/2.0;
        if(Edge[i][j]<INF && t>maxtime2)
        {
            maxtime2 = t;
            pos1 = i;
            pos2 = j;
        }
    }
    printf("System #%d\n",caseno++); //���
    printf("The last domino falls after ");
    if(maxtime2 > maxtime1)
            printf("%.1f seconds,between the key dominoes %d and %d. \n\n",maxtime2,pos1+1,pos2+1);
    else
        printf("%.1f seconds, at key domino %d. \n\n",maxtime1,pos);
}
int read_case()//��������
{
    int i,j;
    int v1,v2,t;
    scanf("%d%d",&n,&m);
    if(n==0&&m==0)return 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            Edge[i][j]=INF;//������
    }
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&v1,&v2,&t);
        v1--;
        v2--;
        Edge[v1][v2]=Edge[v2][v1]=t; //��������ͼ
    }
    return 1;
}
int main()
{
    while(read_case())
      solve_case();
    return 0;
}
