#include<bits/stdc++.h>
using namespace std;
/*
  图论之图的DFS遍历
  ZOJ1709 油田 简单的DFS
  图的连通子图计数
*/
char grid[101][101];
int m,n;
int dir[8][2]={-1,-1,-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1};
void dfs(int x,int y)
{
    int i,xx,yy;
    grid[x][y]='*';
    for(i=0;i<8;i++)
    {
        xx=x+dir[i][0];
        yy=y+dir[i][1];
        if(xx<0||yy<0||xx>=m||yy>=n)continue;
        if(grid[xx][yy]=='@')
            dfs(xx,yy);
    }
}
int main()
{
    int i,j;
    int count;
    while(true)
    {
        scanf("%d%d",&m,&n);
        if(m==0)break;
        for(i=0;i<m;i++)
            scanf("%s",grid[i]);
        count=0;
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
        {
            if(grid[i][j]=='@')
            {
                dfs(i,j);
                count++;
            }
        }
        printf("%d\n",count);
    }
    return 0;
}
