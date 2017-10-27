#include<bits/stdc++.h>
using namespace std;
/*
1.2 蛤蛤的邻居 POJ1659
思路：根据Havel-Hakimi定理判断给定序列是否可图(无向图)，可图则打印结果
      两种不合理情形：1.某次对剩下的序列排序后，出现了最大的度数超过了剩余的顶点数；
                      2.对最大度数(d1)后面的d1个度数各减1后，出现了负数，代码中是出现了非正数。
*/
#define MAXN 100
struct vertex{
  int degree;//顶点的度
  int index;//顶点序号
}v[MAXN];
int cmp(const void *a,const void *b)
{
    return ((vertex *)b)->degree-((vertex*)a)->degree;//逆序
}
int main()
{
    int T,p,q,n,i,j,r,k;
    int Edge[MAXN][MAXN];
    int flag;
    int d1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d",&v[i].degree);
            v[i].index=i;
        }
        memset(Edge,0,sizeof(Edge));
        flag=1;
        for(k=0;k<n&&flag;k++)//Havel-hakimi
        {
            //对数组的后n-k个元素排序，非递增顺序
            qsort(v+k,n-k,sizeof(vertex),cmp);
            i=v[k].index;
            d1=v[k].degree;
            if(d1>n-k-1) {flag=0;break;}
            for(r=1;r<=d1&&flag;r++)
            {
                j=v[r+k].index;
                if(v[r+k].degree<=0)flag=0;//这里必须是<=，不能是<，因为我们先判定了d1与剩余数的数量关系，又判定了r与d1的关系，并且r初始为1，若这里用<，则序列中出现0时也会绕过判定成为合理解。
                                           //也就是说能进入该循环的d1一定是>=1的，所以如果此时被减序列中有0，那么肯定就不符合条件了，可以直接退出循环了、结束程序。
                v[r+k].degree--;
                Edge[i][j]=Edge[j][i]=1;
            }
        }
        if(flag)
        {
            puts("YES");
            for(p=0;p<n;p++)
            {
                for(q=0;q<n;q++)
                {
                    if(q) printf(" ");
                    printf("%d",Edge[p][q]);
                }
                puts("\n");
            }

        }
        else
            puts("NO\n");
    }

    return 0;
}
