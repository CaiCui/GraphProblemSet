#include<bits/stdc++.h>
using namespace std;
/*
  图论之图的DFS遍历
  ZOJ2110 骨头的诱惑 这个题目易TLE，奇数剪枝是个难点
*/
char Map[9][9];
int n,m,t;
int di,dj;
bool escape;
int dir[4][2]={0,-1,0,1,1,0,-1,0};
void dfs(int si,int sj,int cnt)
{
    int i,temp;
    if(si>n||sj>m||si<=0||sj<=0)return;
    if(si==di&&sj==dj&&cnt==t)
    {
        escape=1;return;
    }
    //剪枝,temp%2 判定举例： 比如a-b可以走1步，也可以走3步，即二者等价，即剩余步数(t-cnt)和剩余最短距离fabs(si-di)+fabs(sj-dj)的奇偶性是一样的，任何数+一个偶数该数本身性质不变
    //奇数+偶数=奇数，偶数+偶数=偶数，也就是剩余步数和剩余最短距离必须奇偶性一致才可能有解，当它们一致时，二者是等价的，可以这么想，比如剩余3步，剩余最短距离1，那么走三步和走一步，都有机会到达终点，也就是矩形的
    //两部分。
    /* 图示：
       a--b
       |  |  a-b：可以直接a走到b,也可以a-c-d-b，两种走法都可能存在解，即它们在可解性上是等价的，所以这种情况需要继续搜索。若是相减为奇数，比如5-2=3，则5步无论怎么走也等价不了2步，即不可能到达终点！
       c--d
    */
    temp=(t-cnt)-fabs(si-di)-fabs(sj-dj);
    if(temp<0||temp%2)return;
    for(i=0;i<4;i++)
    {
        if(Map[si+dir[i][0]][sj+dir[i][1]]!='X')
        {
            Map[si+dir[i][0]][sj+dir[i][1]]='X';
            dfs(si+dir[i][0],sj+dir[i][1],cnt+1);
            if(escape)return;
            Map[si+dir[i][0]][sj+dir[i][1]]='.';
        }
    }
    return;
}
int main()
{
    int i,j;
    int si,sj;
    while(scanf("%d%d%d",&n,&m,&t))
    {
        if(n==0&&m==0&&t==0)break;
        int wall=0;
        char temp;
        scanf("%c",&temp);//读掉换行符，容易出错，或者用getchar()
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
              scanf("%c",&Map[i][j]);
              if(Map[i][j]=='S'){si=i;sj=j;}
              else if(Map[i][j]=='D'){di=i;dj=j;}
              else if(Map[i][j]=='X')wall++;
            }
            scanf("%c",&temp);
        }
        if(n*m-wall<=t)
        {
            printf("NO\n");
            continue;
        }
        escape=0;
        Map[si][sj]='X';
        dfs(si,sj,0);
        if(escape)
          printf("YES\n");
        else
          printf("NO\n");

    }
    return 0;
}
