#include<bits/stdc++.h>
using namespace std;
/*
  图论之图的BFS遍历
  营救 ZOJ1649
  最少步数不一定是最优解，到达目标点后不能立即结束搜索，每个点可以重复搜索的BFS
*/
#define MAXMN 200
#define INF 1000000 //走到每个位置所需时间初始为无穷大

struct point{
 int x,y;
 int step;
 int time;
};
queue<point>Q;
int N,M;
char Map[MAXMN][MAXMN];
int mintime[MAXMN][MAXMN];//记录走到每个位置所需最少时间,同时可以保证在没有visited[]数组情况下，防止走重复的路造成死循环
int dir[4][2]={-1,0,0,1,1,0,0,-1};
int ax,ay;//终点

int BFS(point s)
{
    int i;
    Q.push(s);
    point hd;
    while(!Q.empty())
    {
        hd=Q.front();
        Q.pop();
        for(i=0;i<4;i++)
        {
            int x=hd.x+dir[i][0],y=hd.y+dir[i][1];
            if(x>=0 && x<=N-1 && y>=0 && y<=M-1 && Map[x][y]!='#')
            {
                point t;
                t.x=x;
                t.y=y;
                t.step=hd.step+1;
                t.time=hd.time+1;
                if(Map[x][y]=='x')
                    t.time++;
                if(t.time<mintime[x][y])//如果当前走法可以使到达改点的时间缩短，那么更新
                {
                    mintime[x][y]=t.time;
                    Q.push(t);
                }

            }
        }
    }
    return mintime[ax][ay];
}
int main()
{
    int i,j;
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        memset(Map,0,sizeof(Map));
        for(i=0;i<N;i++)scanf("%s",Map[i]);
        int sx,sy;
        point start;
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
        {
            mintime[i][j]=INF;
            if(Map[i][j]=='a'){ax=i;ay=j;}
            else if(Map[i][j]=='r'){sx=i;sy=j;}
        }
        start.x=sx;
        start.y=sy;
        start.step=0;
        start.time=0;
        mintime[sx][sy]=0;
        int mint=BFS(start);
        if(mint<INF) printf("%d\n",mint);
        else
            printf("No way!\n");
    }
    return 0;
}
