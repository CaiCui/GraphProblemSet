#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之所有顶点间的最短路径--Floyd算法
  ZOJ1967 光纤网络
  递推公式：
  1.A(0)[i][j]=提供i到j直接相连的公司集合
  2.A(k)[i][j]=或运算{A(k-1)[i][j],与运算(A(k-1)[i][k],A(k-1)[k][j])k=0,1,..n}=m[i][j]|=m[i][k]&m[k][j]
  利用Flyod的递推变形求出所有路线，同时运用了二进制的位运算实现递推集合的或和与运算
*/
#define MAXN 201
int main()
{
    int m[MAXN][MAXN];
    int n;
    int A,B;
    int i,j,k;
    char str[27];
    char ch;
    while(scanf("%d",&n)&&n)
    {
        memset(m,0,sizeof(m));
        while(scanf("%d%d",&A,&B))//提供直连AB的公司
        {
            if(A==0&&B==0)break;
            scanf("%s",str);
            for(i=0;str[i];i++)
            {
                m[A][B]|=1<<(str[i]-'a');
            }
        }
        //Flyod
        for(k=1;k<=n;k++)
        {
            for(i=1;i<=n;i++)
            {
                for(j=1;j<=n;j++)
                {
                    m[i][j]|=m[i][k]&m[k][j];
                }
            }
        }
        //查询
        while(scanf("%d%d",&A,&B))
        {
            if(A==0&&B==0)break;
            for(ch='a';ch<='z';++ch)
            {
                if(m[A][B]&(1<<ch-'a'))
                    putchar(ch);
            }
            if(!m[A][B])putchar('-');
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}
