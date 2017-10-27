#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮Dijstra�㷨
  ZOJ2750 ���������Ϸ
  ˼·�����������ͼ������ӵ�0����N-1�����·������������ڣ��򷵻�-1
*/
#define INF 10000000
#define MAXN 1000
struct idiom{ //����ڵ�
  char front[5],back[5];//��ŵ�һ�������һ������
  int T;//ʱ�䣬��Ȩ
};
idiom dic[MAXN];  //�ֵ�
int Edge[MAXN][MAXN];
int dist[MAXN];  //���·������
int S[MAXN]; //���·���㼯��
int N;
int main()
{
    int i,j,k;
    char s[100];
    int len;
    while(scanf("%d",&N)!=EOF)
    {
        if(!N)break;
        for(k=0;k<N;k++)
        {
            scanf("%d%s",&dic[k].T,s);
            len=strlen(s);
            for(i=0,j=len-1;i<4;i++,j--)//ȡ��β��4���ַ�
            {
                dic[k].front[i]=s[i];
                dic[k].back[3-i]=s[j];
            }
            dic[k].front[4]=dic[k].back[4]='\0';
        }
        for(i=0;i<N;i++)//��ͼ
        {
            for(j=0;j<N;j++)
            {
                Edge[i][j]=INF;
                if(i==j)continue;
                if(strcmp(dic[i].back,dic[j].front)==0)
                    Edge[i][j]=dic[i].T;
            }
        }
        //DijKstra
        for(i=0;i<N;i++)
        {
            dist[i]=Edge[0][i];
            S[i]=0;
        }
        S[0]=1;
        dist[0]=0;
        for(i=0;i<N-1;i++)
        {
            int min=INF,u=0;
            for(j=0;j<N;j++)
            {
                if(!S[j]&&dist[j]<min)
                {
                    u=j;
                    min=dist[j];
                }
            }
            S[u]=1;
            for(k=0;k<N;k++)
            {
                if(!S[k]&&Edge[u][k]<INF&&dist[u]+Edge[u][k]<dist[k])
                    dist[k]=dist[u]+Edge[u][k];
            }
        }
        if(dist[N-1]==INF)printf("-1\n");
        else
            printf("%d\n",dist[N-1]);
    }
    return 0;
}
