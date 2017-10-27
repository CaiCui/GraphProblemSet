#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之活动网络AOE网络
  计算关键路径的算法：
  1.建立邻接表结构
  2.从源点E0出发，按拓扑有序计算出每个顶点的Ee[i]，同时判环
  3.从汇点En-1出发，按逆拓扑有序计算出各顶点El[i].
  4.根据2,3结果计算各有向边的e[k],l[k]
  5.对网络中每条边判断e[k]==l[k],则是关键活动，求出所有关键活动
  关键路径上所有活动都是关键活动，所以求出所有关键活动就得到了关键路径
  关键路径求解模板
*/
#define MAXN 100 //顶点个数最大值
#define MAXM 200 //边数的最大值
struct ArcNode{
  int to,dur,no;//边的另一个顶点，边权(活动持续时间)，活动序号(边编号)
  ArcNode *next;
};
int n,m;//顶点数量，边数量
ArcNode* List1[MAXN];//出边表
ArcNode* List2[MAXN];//入边表
int count1[MAXN];//各顶点的入度
int count2[MAXN];//各顶点的出度
int Ee[MAXN];//各事件最早可能开始时间，事件对应节点
int El[MAXN];//各事件最迟允许开始时间，事件对应节点
int e[MAXN];//各活动最早可能开始时间，活动对应边节点
int L[MAXN];//各活动最迟允许开始时间，活动对应边节点
void CriticalPath() //求出关键路径
{
    //拓扑排序求Ee
    int i,j,k;
    int top1=-1;
    ArcNode *temp1;
    memset(Ee,0,sizeof(Ee));
    for(i=0;i<n;i++)
    {
        if(count1[i]==0)
        {
            count1[i]=top1;
            top1=i;
        }
    }
    for(i=0;i<n;i++)
    {
        if(top1==-1)
        {
            puts("Network has a cycle!\n");
            return;
        }
        else
        {
            j=top1;
            top1=count1[top1];
            temp1=List1[j];//取出
            while(temp1!=NULL)
            {
                k=temp1->to;
                if(--count1[k]==0)
                {
                    count1[k]=top1;
                    top1=k;
                }
                //计算Ee
                if( Ee[j]+temp1->dur > Ee[k]) //有向边<j,k>，求出从E0到Ei的最长路径长度Ee[i]
                  Ee[k]=Ee[j]+temp1->dur;
                temp1=temp1->next;
            }
        }
    }

    //逆拓扑排序求El
    int top2=-1;
    ArcNode *temp2;
    for(i=0;i<n;i++)
    {
        El[i]=Ee[n-1];
        if(count2[i]==0)
        {
            count2[i]=top2;
            top2=i;
        }
    }
    for(i=0;i<n;i++)
    {
        j=top2;
        top2=count2[top2];
        temp2=List2[j];
        while(temp2!=NULL)
        {
            k=temp2->to;
            if(--count2[k]==0)
            {
                count2[k]=top2;
                top2=k;
            }
            if( El[j]-temp2->dur <El[k] )   //有向边<j,k>
             El[k]= El[j]-temp2->dur;
            temp2=temp2->next;
        }
    }

    //求出e[k]和L[k]
    memset(e,0,sizeof(e));
    memset(L,0,sizeof(L));
    printf("The critical activities are:\n");
    for(i=0;i<n;i++)
    {
        temp1=List1[i];
        while(temp1!=NULL)
        {
            j=temp1->to;//有向边<i,j>
            k=temp1->no;
            e[k]=Ee[i];
            L[k]=El[j]-temp1->dur;
            if(e[k]==L[k])
                printf("a%d : %d->%d\n",k,i,j);
            temp1=temp1->next;
        }
    }

}
int main()
{
    int i,u,v,w;
    scanf("%d%d",&n,&m);
    memset(List1,0,sizeof(List1));
    memset(List2,0,sizeof(List2));
    memset(count1,0,sizeof(count1));
    memset(count2,0,sizeof(count2));
    ArcNode *temp1,*temp2;
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        //构造入边表
        count1[v]++;
        temp1=new ArcNode;
        temp1->to=v;
        temp1->dur=w;
        temp1->no=i+1;
        temp1->next=NULL;
        if(List1[u]==NULL)
            List1[u]=temp1;
        else
        {
            temp1->next=List1[u];
            List1[u]=temp1;
        }
        //构造入边表
        count2[u]++;
        temp2=new ArcNode;
        temp2->to=u;
        temp2->dur=w;
        temp2->no=i+1;
        temp2->next=NULL;
        if(List2[v]==NULL)
            List2[v]=temp2;
        else
        {
            temp2->next=List2[v];
            List2[v]=temp2;
        }
    }
      CriticalPath();
        for(i=0;i<n;i++) //释放操作
        {
            temp1=List1[i];
            temp2=List2[i];
            while(temp1!=NULL)
            {
                List1[i]=temp1->next;
                delete temp1;
                temp1=List1[i];
            }
            while(temp2!=NULL)
            {
                List2[i]=temp2->next;
                delete temp2;
                temp2=List2[i];
            }
        }

    return 0;
}
