#include<bits/stdc++.h>
using namespace std;
/*
  图论之邻接表: 解决带自身环的图和重边的图，适合边稀疏的图，节省存储空间
  用邻接表存储有向图，并输出各顶点的出度和入度
*/
#define MAXN 100
//节点，存放有向图一条边的另一个邻接点序号，和下一个节点的指针
struct node{
    int adjvex;
    node *next;
};
//每个节点存储的信息结构，包括该节点的编号和与该节点相连的出边和入边
struct VNode{
  int data;//顶点标号
  node *head1;//出边表表头
  node *head2;//入边表表头
};
struct Graph{
  VNode vertex[MAXN];//图的顶点数组
  int vexnum,arcnum;//顶点数和边数
};
Graph lg;
//建图
void CreateG()
{
   int i=0;
   node *pi;
   int v1,v2;
   for(i=0;i<lg.vexnum;i++)//初始化每个节点的双表表头指针
   {
       lg.vertex[i].head1=lg.vertex[i].head2=NULL;
   }
   for(i=0;i<lg.arcnum;i++)//输入边，采用头插法建立邻接表
   {
       scanf("%d%d",&v1,&v2);
       v1--;
       v2--;
       //出边表
       pi=new node();
       pi->adjvex=v2;
       pi->next=lg.vertex[v1].head1;
       lg.vertex[v1].head1=pi;

       //入边表
       pi=new node();
       pi->adjvex=v1;
       pi->next=lg.vertex[v2].head2;
       lg.vertex[v2].head2=pi;

   }
}

//释放图
void DeleteG()
{
   int i;
   node *pi;
   for(i=0;i<lg.vexnum;i++)
   {
       pi=lg.vertex[i].head1;
       //释放每个点的head1
       while(pi!=NULL)
       {
           lg.vertex[i].head1=pi->next;
           free((void *)pi);
           pi= lg.vertex[i].head1;
       }

       pi=lg.vertex[i].head2;
       //释放每个点的head2
       while(pi!=NULL)
       {
           lg.vertex[i].head2=pi->next;
           free((void *)pi);
           pi= lg.vertex[i].head2;
       }

   }
}
int main()
{
    int i;
    int id,od;
    node *pi;
    while(true)
    {
        lg.vexnum=lg.arcnum=0;
        scanf("%d%d",&lg.vexnum,&lg.arcnum);
        if(lg.vexnum==0)break;
        CreateG();
        for(i=0;i<lg.vexnum;i++)
        {
            od=0;
            pi=lg.vertex[i].head1;
            while(pi!=NULL)
            {
                od++;
                pi=pi->next;
            }
            if(i==0)
                printf("%d",od);
            else
                printf(" %d",od);
        }
        printf("\n");

         for(i=0;i<lg.vexnum;i++)
        {
            id=0;
            pi=lg.vertex[i].head2;
            while(pi!=NULL)
            {
                id++;
                pi=pi->next;
            }
            if(i==0)
                printf("%d",id);
            else
                printf(" %d",id);
        }
        printf("\n");
        DeleteG();
    }
    return 0;
}
