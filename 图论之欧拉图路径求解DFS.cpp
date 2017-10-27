#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之可行性遍历欧拉回路问题---欧拉回路求解
  方法一 DFS
  多米诺骨牌 解不唯一
  1.建图(邻接表解决平行边问题)
  2.搜索
*/
#define VNUM 6 //6个顶点
#define MAXN 101 //骨牌数目
struct EdgeNode{
    int adjvex;
    int EdgeNo;
    int flag;  //1正向，-1反向
    EdgeNode *nextedge;
};
EdgeNode *EdgeLink[VNUM+1];//链表头数组0,1,2...6
int visited[MAXN]; //边访问标志
//欧拉通路上各边的序号
int path[MAXN]; //path[i]=j第i条为第j块骨牌-j表示旋转
int pi;  //path[]边数组下标
int N;
void CreateG()//邻接表建图
{
    int i;
    EdgeNode *p1,*p2;
    int v1,v2;
    memset(visited,0,sizeof(visited));
    for(i=1;i<=6;i++)
        EdgeLink[i]=NULL;
    int number=1;
    for(i=1;i<=N;i++)
    {
        scanf("%d%d",&v1,&v2);
        p1=new EdgeNode;
        p2=new EdgeNode;
        p1->adjvex=v2;
        p1->EdgeNo=number;
        p1->flag=1;
        p1->nextedge=EdgeLink[v1];
        EdgeLink[v1]=p1;

        p2->adjvex=v1;
        p2->EdgeNo=number;
        p2->flag=-1;
        p2->nextedge=EdgeLink[v2];
        EdgeLink[v2]=p2;
        number++;
    }
}
void DFSL(int start)//DFS搜索,写的很棒
{
    while(pi<=N)//还有边未访问
    {
        EdgeNode *p;
        p=EdgeLink[start];
        while(p!=NULL)
        {
            if(!visited[p->EdgeNo])
            {
                //同一边的正向和逆向的邻接点EdgeNo相同，保证不会走同一条路
                visited[p->EdgeNo]=1;
                if(p->flag>0)
                    path[pi]=p->EdgeNo;
                else
                    path[pi]=-(p->EdgeNo);
                pi++;
                DFSL(p->adjvex);
            }
            else
                p=p->nextedge;
        }
    }
}
void Domino()//求解
{
    int JDNum=0;//奇数顶点数量
    int start1,start2; //搜索的起始顶点
    EdgeNode *p;
    int i,j;
    for(i=1;i<=6;i++)
    {
        int DNum=0; //顶点度数
        p=EdgeLink[i];
        while(p!=NULL)
        {
            DNum++;
            p=p->nextedge;
        }
        if(DNum%2!=0)
        {
            start1=i;//记录奇数起点
            JDNum++;
        }
        if(DNum!=0)start2=i;//记录偶数起点
    }
    if(JDNum!=0&&JDNum!=2)
    {
        printf("No Solution!\n");
        return;
    }
    pi=1;
    //存在欧拉回路(通路)选起点
    if(JDNum==2)
        DFSL(start1);//通路
    else
        DFSL(start2);//回路

    char flag1='+',flag2='-';
    for(i=1;i<=N;i++)
    {
        if(path[i]>0)
            printf("%d%c\n",path[i],flag1);
        else
            printf("%d%c\n",-path[i],flag2);
    }

}
void DeleteLG()//释放空间
{
    int i;
    EdgeNode *pi;
    for(i=1;i<=6;i++)
    {
        pi=EdgeLink[i];
        while(pi!=NULL)
        {
            EdgeLink[i]=pi->nextedge;
            delete pi;
            pi=EdgeLink[i];
        }
    }
}
int main()
{
    while(scanf("%d",&N)&&N!=0)
    {
        CreateG();
        Domino();
        DeleteLG();
    }
    return 0;
}
