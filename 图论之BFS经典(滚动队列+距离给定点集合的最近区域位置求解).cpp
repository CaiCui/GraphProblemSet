#include<bits/stdc++.h>
using namespace std;
/*
  图论之BFS遍历
  ZOJ2913:公共汽车通票
  运用了一个滚动队列的技巧,经典题目,值得反复思考
  解析：
  本题的目的是找到一个区域Z,使它距离所有公交线路上的点的最远距离尽可能最小，即要包含所有的公交站点，并且使Z距离最远的那个站点的距离尽可能最小。
  也就是找到一个所谓的公交线路网络的”中心点“。
  所以可以这么干：
  对公交线路上的每个站点进行BFS遍历，并且每次都要在遍历到的点j上记录它到当前公交站点的距离res[j]，即BFS的层次，然后随着每个站点BFS遍历的进行，要一直保持更新
  每个遍历到的点j到当前进行BFS遍历的公交站点的距离，使每个遍历到的点j的res[j]都保持是当前已经遍历过的站点情形下的最大值(这样可以保证以前的站点也会被包含进来，同时当前站点也会被包含进来)，
  所有站点完成BFS后，对着更新结束的res[]数组排序，取出最小的那个就是我们要求的结果，因为上述的操作完成了统计每个区域到包含每个站点的距离的最小值，所以在所有结果最小值中找出最小值就是
  最终的最小值解。

*/
#define ZMAX 10000 //地区编号的最大值
#define INF 100000 //一个极大值
int nz,nr;//地区数目，公交线路数目
int mz[ZMAX]; //mz[i]为与第i个地区相邻的地区数目

int Edge[ZMAX][10];//编号为i的地区的第j个相邻地区的编号
int res[ZMAX]; //每个线路上的每个地区到地区i的距离中的最大值
int cur; //记录当前公交的站点次序,cur==0表示第一站
int reach[ZMAX]; //reach[s]=cur,表示地区s在第cur+1站已经访问过
int Max(int x,int y)
{
    return (x>y)?x:y;
}
void BFS(int s)
{
    int i,a,b;
    int val,att;//val 记录层，即距离。att 表示当前节点
    queue<int>q[2];
    a=0,b=1,val=0;
    if(reach[s]<cur)
    {
      q[b].push(s);
      reach[s]=cur;
      res[s]=Max(res[s],val+1);
    }
    while(!q[b].empty())
    {
        swap(a,b);//滚动队列，交替存储第1层的元素，第二层的元素，第三层。。。。
        val++;
        while(!q[a].empty())//处理所有当前节点
        {
            att=q[a].front();
            q[a].pop();
            for(i=0;i<mz[att];i++)
            {
                if(reach[Edge[att][i]]<cur)
                {
                    q[b].push(Edge[att][i]);
                    reach[Edge[att][i]]=cur;
                    res[Edge[att][i]]=Max(res[Edge[att][i]],val+1);
                }
            }
        }
    }
}

int main()
{
    int T;
    int i,j,t;
    int id;
    int mr;
    int ret,center;
    scanf("%d",&T);
    for(t=0;t<T;t++)
    {
        memset(reach,-1,sizeof(reach));
        memset(res,0,sizeof(res));
        cur=0;
        scanf("%d%d",&nz,&nr);
        for(i=0;i<nz;i++)
        {
            scanf("%d",&id);
            scanf("%d",&mz[id]);
            for(j=0;j<mz[id];j++)scanf("%d",&Edge[id][j]);
        }
        for(i=0;i<nr;i++)//对每条线路上的每个区域bfs遍历
        {
            scanf("%d",&mr);
            for(j=0;j<mr;j++)
            {
                scanf("%d",&id);
                BFS(id);//从每条公交线路上每个地区的id出发进行bfs遍历
                cur++;
            }
        }
        ret=INT_MAX;
        center=-1;
        for(i=0;i<10000;i++)//求出最小的
        {
            if(reach[i]==cur-1 &&res[i]<ret)//cur-1==reach[i]表示是公交线上的最后一个需要遍历的站，至此已完成所有区域最大值的更新，选出最大值列表中的最小值的区域就是答案
            {
                ret=res[i];
                center=i;
            }
        }
        printf("%d %d\n",ret,center);
    }
    return 0;
}
