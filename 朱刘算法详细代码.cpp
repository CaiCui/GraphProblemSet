#include <bits/stdc++.h>
using namespace std;
/*
    朱刘算法(论文算法)实现.cpp 求解有向图的最小生成树，也叫最小树型图，它先固定一个根，再求出权值最小的树形图
    难点：环的处理
    例题：hdu2121 pku3164 Command Network(模板题)
*/
const int MAXNODE=1010;
const int MAXEDGE=100010;
typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge{
    int u,v;
    Type dis;
    Edge(){}
    Edge(int u,int v,Type dis):u(u),v(v),dis(dis){}
};
struct Directed_MT{
    int n,m;//n:点 m:边
    Edge edges[MAXEDGE];
    int vis[MAXNODE];
    int pre[MAXNODE];
    int id[MAXNODE];
    Type in[MAXNODE];//记录点的最小入度集合

    void init(int n){
      this->n = n;
      m = 0;
    }

    void addEdge(int u,int v, Type dis){
     edges[m++]=Edge(u,v,dis);
    }

    Type DirMt(int root){//定根的最小树型图
        Type ans=0;
        int t=0;
        while(true){
            //初始化

            for(int i=0;i<n;i++)
                in[i]=INF;
            //求in[]集合
            for(int i=0;i<m;i++)
            {
                int u=edges[i].u;
                int v=edges[i].v;
                //寻找最小入度边，删除自环
                if(edges[i].dis<in[v] && u!=v)
                {
                    in[v]=edges[i].dis;

                    pre[v]=u;

                }

            }
             for(int i=0;i<m;i++){
             cout<<edges[i].dis<<" ";

            }
            cout<<endl;
            //如果某个点没有最小入边，表示该点不连通，直接失败，无最小树型图
            for(int i=0;i<n;i++)
            {
                if(i==root)continue;
                if(in[i]==INF)return -1;
            }

            int cnt=0;//记录缩点编号,同时用于缩点以外的点的编号更新
            memset(id,-1,sizeof(id));//更新后的节点编号序列存放在id中
            memset(vis,-1,sizeof(vis));
            in[root]=0;//根入度0
            //计算路径代价
            for(int i=0;i<n;i++)
            {
                ans+=in[i];
                //为什么后面要减in[i]，因为这里所有点都加了in[i],所以后面可能由于环要去掉某些边in[i]，所以相当于先不管好坏加进结果，最后更新图的边权时候再把坏的情况下的入度in[i]减去,即相当于去掉了环值
                int v=i;
                //图上寻找环的技巧:把从v开始的所有线路上的点的vis[]都标记为同一个i，一旦某一点第二次进入while判断就说明在该点处开始出现了环
                while(vis[v]!=i && id[v]==-1&&v!=root)
                {
                    vis[v]=i;
                    v=pre[v];
                }//如果无环，就会一直找到根，然后进行下一次循环

                //求缩点cnt,id[v]==-1保证了环只被计算一次
                if(v!=root &&id[v]==-1)
                {
                    //不能从i开始找，因为i可能不在自环内，比如4->3 3->4 3->2 2->1 1>0 i=0时，环就出现在v==3的地方
                    for(int u=pre[v];u!=v;u=pre[u])
                        id[u]=cnt;
                    id[v]=cnt++;
                    //同一环内的点的缩点编号一样都是cnt
                }

            }
            //没有环，直接成功
            if(cnt==0)break;

            //找到那些不在环内的点，重新标记这些点
            for(int i=0;i<n;i++)
                if(id[i]==-1)id[i]=cnt++;//本题中i=0是根，所以恰好id[0]=2;
            //更新新图边权值和节点编号
            for(int i=0;i<m;i++){
                int v=edges[i].v;
                edges[i].v=id[edges[i].v];
                edges[i].u=id[edges[i].u];
                if(edges[i].v!= edges[i].u)//表示该边不是环中的边,可以计算新的入度
                    {
                        edges[i].dis-=in[v];
                    }
            }

            //缩完点后，点的数量变了,点的编号也变了
            n=cnt;
            root=id[root];


        }

        return ans;//遍历最终id集合中的元素
    }
}MT;
int main()
{
    /*
    pku3164 Command Network 直接套入上方代码即可计算
    int a,b;
    int n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(int i=0;i<n;i++)
            scanf("%lf %lf",&p[i].x,&p[i].y);
        int mm=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            if(a==b)continue;
            a--,b--;
            e[mm++]=edge(a,b,dist(p[a],p[b]));
        }
        double ans=Directed_MST(0,n,mm);
        if(ans==-1)
            puts("poor snoopy");
        else printf("%.2f\n",ans);
    }*/
        MT.init(7);
        MT.addEdge(0,1,9);
        MT.addEdge(1,2,3);
        MT.addEdge(2,6,6);
        MT.addEdge(6,5,8);
        MT.addEdge(5,4,3);
        MT.addEdge(0,4,5);
        MT.addEdge(1,3,9);
        MT.addEdge(3,0,3);
        MT.addEdge(4,3,4);
        MT.addEdge(2,1,7);
        MT.addEdge(3,2,8);
        MT.addEdge(3,5,5);
        MT.addEdge(2,5,9);
        MT.addEdge(6,2,4);
        MT.addEdge(5,6,4);
        cout<<MT.DirMt(0)<<endl;
      return 0;
}
