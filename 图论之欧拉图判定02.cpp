#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之可行性遍历欧拉回路问题---欧拉回路(欧拉图)的判定
  ZOJ2016 词迷游戏 有向欧拉通路+并查集判断基图连通性
*/
#define MAXN 1000001
#define INF 100000000
int T;
int N;
char word[1001];
int od[26],id[26];//每个字母的出度和入度
int bused[26];//第i个字母在这组单词中是否作为首尾字母
int parent[26];//i所在集合对应的树中的根结点
struct edge{
 int u,v;
}edges[MAXN];
//并查集操作
void UFset()
{
    for(int i=0;i<26;i++)
        parent[i]=-1;
}
int Find(int x)//返回x所属的集合的根结点
{
    int s;
    for(s=x;parent[s]>=0;s=parent[s]);
    while(s!=x)
    {
        int tmp=parent[x];
        parent[x]=s;
        x=tmp;
    }
    return s;
}
//合并集合
void Union(int R1,int R2)
{
    int r1=Find(R1);
    int r2=Find(R2);
    int tmp=parent[r1]+parent[r2];
    if(parent[r1]>parent[r2])
    {
        parent[r1]=r2;
        parent[r2]=tmp;
    }
    else
    {
        parent[r2]=r1;
        parent[r1]=tmp;
    }
}
bool bconnect()//判断有向图的基图是否连通
{
    int u,v,i;
    UFset();
    for(i=0;i<N;i++)//判断每条边，不属于同一连通分量则合并
    {
        u=edges[i].u;
        v=edges[i].v;
        if(u!=v&&Find(u)!=Find(v))//u==v则按一个点计算不计入并查集
            Union(u,v);
    }
    int first=-1;//
    for(i=0;i<26;i++)
    {
        if(bused[i]==0)continue;
        if(first==-1)first=i;
        else if(Find(i)!=Find(first))
            break;//不连通
    }
    if(i<26)return false;
    return true;
}
int main()
{
    int u,v;
    int i,j;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        memset(od,0,sizeof(od));
        memset(id,0,sizeof(id));
        memset(bused,0,sizeof(bused));
        scanf("%d",&N);
        for(j=0;j<N;j++)
        {
            scanf("%s",word);
            u=word[0]-'a';
            v=word[strlen(word)-1]-'a';
            od[u]++;
            id[v]++;
            bused[u]=bused[v]=1;
            edges[j].u=u;
            edges[j].v=v;
        }
        bool Euler=true;
        int one=0;
        int none=0;
        //出入度判定
        for(j=0;j<26;j++)
        {
            if(bused[j]==0)continue;
            if(od[j]-id[j]>=2||id[j]-od[j]>=2)
            {
                Euler=false;
                break;
            }
            if(od[j]==0&&id[j]==0){
                Euler=false;
                break;
            }
            if(od[j]-id[j]==1)
            {
                one++;
                if(one>1){
                    Euler=false;
                    break;
                }
            }
            if(id[j]-od[j]==1)
            {
                none++;
                if(none>1){
                    Euler=false;
                    break;
                }
            }
        }

        if(one!=none)Euler=false;
        if(!bconnect())Euler=false;
        if(Euler)
            printf("Ordering is possible.\n");
        else
            printf("The door cannot be opened.\n");
    }
    return 0;
}
