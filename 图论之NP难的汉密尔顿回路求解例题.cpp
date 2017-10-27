#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之汉密尔顿回路问题
  汉密尔顿回路：若存在一条回路，经过图中每个顶点一次且仅一次，则称为汉密尔顿回路
  没有有效的方法进行判定，只有充分条件或必要条件进行的判定
  下面给出一个汉密尔顿回路求解的例题。
  ZOJ2398 岛屿和桥 状态压缩dp求解(状压dp通常用于np问题的小规模求解)
  这是一道好题，可以清晰地看到如果运用状压dp求解np难问题，同时也可以看到如果求解汉密尔顿回路问题
*/
#define MAXN 13  //岛的最大数目
#define MAXSTATUS 1<<13 //状态的最大数目
__int64 dp[MAXSTATUS][MAXN][MAXN]; //状态转移方程，第一维表示状态，这里使用了状态压缩的方法，用一位整数来表示走过的点的集合(6:0110表示走过1,2两个点)，DP方程中保留两个点[row][col]是为了判断新加入的点是否能和这两个点构成三角形，从而满足第三个条件
__int64 ways[MAXSTATUS][MAXN][MAXN]; //路径数
int value[MAXN];  //岛屿的值记录
bool link[MAXN][MAXN]; //图
int nislands; //岛的数目
__int64 maxvalue; //最好的汉密尔顿路径的权值
__int64 maxways; //最好的汉密尔顿路径的数目
void initial()
{
    int nbridges;
    int i;
    int row,col;
    scanf("%d%d",&nislands,&nbridges);
    for(i=0;i<nislands;i++)
    {
        scanf("%d",value+i);
    }
    if(nislands==1)return;
    memset(dp,-1,sizeof(dp));//注意初始化不能为0，否则会在没有路径的时候把0当作最大值
    memset(ways,0,sizeof(ways));
    memset(link,0,sizeof(link));
    for(i=0;i<nbridges;i++)
    {
        scanf("%d%d",&row,&col);
        row--;
        col--;
        link[row][col]=1;
        link[col][row]=1;
        dp[(1<<row)|(1<<col)][row][col]=value[row]*value[col]+value[row]+value[col];
        dp[(1<<row)|(1<<col)][col][row]=value[row]*value[col]+value[row]+value[col];
        ways[(1<<row)|(1<<col)][row][col]=1,ways[(1<<row)|(1<<col)][col][row]=1;
    }
}
void compute()
{
    int i,j,k,s;
    __int64 temp;
    int nextstatus;
    if(nislands==1)//只有一个岛屿
    {
        maxvalue=value[0];
        maxways=1;
        return;
    }
    for(s=0;s<(1<<nislands);s++)//从小到大进行状态转移，并做路径压缩，相当于先把所有状态先枚举出来(二进制表示状态)，然后再从状态集合出发求解结果
    {
        for(i=0;i<nislands;i++)
        {
            if(s&(1<<i))//对走过的集合s中的岛进行&运算，如果某个岛1<<i在s中，则s&(1<<i)==1表示该岛在集合中
            {
                for(j=0;j<nislands;j++)
                {
                    if(i!=j && (s&(1<<j)) && dp[s][i][j]>-1)//如果i,j都在状态集合s中，说明该边走过了，并且dp[][][]更新过
                    {
                        for(k=0;k<nislands;k++)
                        {
                            if(!(s&(1<<k)) && link[i][k]==1)//枚举新的未在走过集合里面出现过的岛
                               {
                                   nextstatus=s|(1<<k);//加入该岛至状态集合
                                   //累加岛屿权值和边权值
                                   temp=dp[s][i][j]+value[k]+value[k]*value[i];
                                   //如果构成三角形则累加三角权值
                                   if(link[j][k]==1)
                                    temp+=value[k]*value[i]*value[j];
                                  if(dp[nextstatus][k][i]==temp)//如果该点加入后，发现之前也出现过这种结果，则只需要加上新的路径走法数，否则说明之前没出现过这种结果，则更新为当前更优的结果和新的路径走法
                                  {
                                      ways[nextstatus][k][i]+=ways[s][i][j];
                                  }
                                  else if(dp[nextstatus][k][i]<temp)
                                  {
                                      ways[nextstatus][k][i]=ways[s][i][j];
                                      dp[nextstatus][k][i]=temp;
                                  }
                               }
                        }
                    }
                }
            }
        }
    }
    maxvalue=-1;
    maxways=0;
    s=(1<<nislands)-1;//岛的全集11111...11
    //统计最好的三角汉密尔顿路径的权值与数目
    for(i=0;i<nislands;i++)
    {
        for(j=0;j<nislands;j++)
        {
            if(!link[i][j])continue;
            if(dp[s][i][j]==maxvalue)
                maxways+=ways[s][i][j];
            else if(dp[s][i][j]>maxvalue)
            {
                maxvalue =dp[s][i][j];
                maxways=ways[s][i][j];
            }
        }

    }
    maxways=maxways/2;
}
int main()
{
    int i;
    int cases;
    scanf("%d",&cases);
    for(i=0;i<cases;i++)
    {
        initial();
        compute();
        if(maxvalue==-1)
            printf("0 0\n");
        else
            printf("%I64d %I64d\n",maxvalue,maxways);
    }
    return 0;
}
