#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之可行性遍历欧拉回路问题路径求解---Fleury算法
  弗罗莱算法--无向欧拉图 涉及到概念：割边集(桥)
  模板：首先判断是否存在欧拉回路或通路，然后存在的话就选择一个正确的点
  按照弗罗莱算法输出欧拉回路或通路
  此算法实现巧妙，细节解释可参考"Fleury算法图解.docx"
*/
#define MAXN 200
struct Stack{
   int top;
   int node[MAXN];
}s;//顶点栈
int Edge[MAXN][MAXN];//无向图的邻接矩阵
int n;
void dfs(int x)//一搜到底，寻找联通子集
{
    int i;
    s.top++;
    s.node[s.top]=x;
    for(i=0;i<n;i++)
    {
        if(Edge[i][x]>0)
        {
            Edge[i][x]=Edge[x][i]=0;//删掉此边，找出桥点
            dfs(i);
            break;//////走完一条就break，与一般的搜索不同
        }
    }
}
void Fleury(int x)
{
    int i,b;
    s.top=0;
    s.node[s.top]=x;//入栈
    while(s.top>=0)
    {
        b=0;
        for(i=0;i<n;i++)
        {
            if(Edge[s.node[s.top]][i]>0)
            {
                b=1;
                break;
            }
        }
        if(b==0)//无顶点可以扩展，输出并出栈,逆序输出相当于找到了桥点，把桥点先依次输出来，由于不应优先走桥，所以先把不得不走桥边的点找到走完，
                //再走的点走的就不是桥边了(因为他可选的桥边已经被必须要走桥边的点给走过了，即删掉了，非常巧妙！！)，相当于用排除法，而不是说对每个点都判断当前边是否是桥边，这样做更加高效巧妙！
        {
            printf("%d",s.node[s.top]+1);
            s.top--;
        }
        else//说明该点不在桥边上可以继续扩展找新的联通子集
        {
            s.top--;
            dfs(s.node[s.top+1]);//如果有就dfs
        }
    }
    printf("\n");
}

int main()
{
    int i,j;
    int m,s,t;
    int degree,num,start;
    scanf("%d%d",&n,&m);
    memset(Edge,0,sizeof(Edge));
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&s,&t);
        Edge[s-1][t-1]=1;
        Edge[t-1][s-1]=1;
    }
    num=0;
    start=0;
    for(i=0;i<n;i++)//判断是否存在欧拉回路
    {
        degree=0;
        for(j=0;j<n;j++)
            degree+=Edge[i][j];
        if(degree%2==1)
        {
            start=i;
            num++;
        }
    }
    if(num==0||num==2)
        Fleury(1);
    else
        printf("No Euler path\n");
    return 0;
}
