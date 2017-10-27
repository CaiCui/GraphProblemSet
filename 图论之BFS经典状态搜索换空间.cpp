#include<bits/stdc++.h>
using namespace std;
/*
  图论之BFS:
  2002 蛇和梯子的游戏 利用BFS思想的经典题目
  思想：利用BFS层次遍历的思想，只考虑图的节点状态的变化，避免了节点的扩展，大大的降低了空间复杂度
*/
#define NMAX 20
#define SLMAX 200
struct SnakeAndLadder{//蛇和梯子
 int from,to;
};
int main()
{
    int D;
    int N,S,L;
    int grid[NMAX*NMAX+1]; //棋盘，序号从1开始
    int gridbak[NMAX*NMAX+1];//备份上一次的棋盘状态
    SnakeAndLadder obstacle[2*SLMAX];//障碍物
    int i,j,k,m;
    int step;//投掷骰子的次数
    int deal;
    scanf("%d",&D);
    for(i=0;i<D;i++)
    {
        scanf("%d%d%d",&N,&S,&L);
        for(j=0;j<S+L;j++)
            scanf("%d%d",&obstacle[j].from,&obstacle[j].to);
        memset(grid,0,sizeof(grid));
        grid[1]=1;
        step=0;
        //只要第N^2个格子没有到达1状态，就继续BFS
        while(grid[N*N]==0){
            memcpy(gridbak,grid,sizeof(grid));//备份上一次状态
            memset(grid,0,sizeof(grid));
            for(j=1;j<=N*N-1;j++)//最后一格不搜
            {
                if(gridbak[j]==0)
                    continue;
                for(k=1;k<=6;k++)//6个情况
                {
                    deal=0;
                    if(j+k>N*N)break;//越界
                    for(m=0;m<S+L;m++)//j+k的位置对可能有蛇或梯子枚举测试
                    {
                        if(obstacle[m].from==j+k)
                        {
                            grid[obstacle[m].to]=1;
                            deal=1;
                            break;
                        }
                    }
                    //不利用蛇和梯子
                    if(deal==0 && grid[j+k]==0)grid[j+k]=1;
                }
            }
          step++;//步数加1
        }
        printf("%d\n",step);
    }
    return 0;
}
