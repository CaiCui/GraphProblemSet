#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之Dijstra算法
  ZOJ2750 成语接龙游戏
  思路：构造好有向图，求出从点0到点N-1的最短路径，如果不存在，则返回-1
*/
#define INF 10000000
#define MAXN 1000
struct idiom{ //成语节点
  char front[5],back[5];//存放第一个和最后一个汉字
  int T;//时间，边权
};
idiom dic[MAXN];  //字典
int Edge[MAXN][MAXN];
int dist[MAXN];  //最短路径数组
int S[MAXN]; //最短路径点集合
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
            for(i=0,j=len-1;i<4;i++,j--)//取首尾各4个字符
            {
                dic[k].front[i]=s[i];
                dic[k].back[3-i]=s[j];
            }
            dic[k].front[4]=dic[k].back[4]='\0';
        }
        for(i=0;i<N;i++)//建图
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
