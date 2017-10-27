#include<bits/stdc++.h>
using namespace std;
/*
  图论之AOV活动网络--拓扑排序
  DAG：有向无环图
  对于AOV网络先要判断是否是DAG图，方法是构造它的拓扑有序序列，进行拓扑排序,注意一个AOV网络的拓扑有序序列可能不唯一
  算法：
  1.在AOV中选出一个入度为0的点并输出
  2.从AOV中删除该点及从该点发出的所有边
  3.重复步骤1,2，直到找不到入度为0的点
  判断：若所有点输出了，则无环，否则剩下仍有顶点没被输出，说明有环
  实现：利用顶点栈和出边表，使用队列也是正确的
  基本思路：首先将各顶点的边链表头指针存放在List数组，然后统计每个顶点入度，存入count数组，
  排序时，首先扫描count数组，将入度为0的顶点入栈，这里为了节省内存，count数组本身就是栈，只需要维持一个
  top指针，每次记录栈中元素的位置，然后从栈中依次弹出栈顶顶点输出，并扫描该顶点的出边表，把每个边节点的
  终点的入度减1，如果减至0了，那么将该顶点入栈；当n个点都出栈后，即可判断有无环存在。
*/
#define MAXN 10
struct Arcnode{
  int to;
  struct Arcnode *next;
}; //节点数组
int n,m;
Arcnode* List[MAXN];//每个顶点的边链表表头指针
int Count[MAXN];//顶点入度表(同时作为栈)
char output[100];//输出内容

void TopSort()//拓扑排序
{
    int i,top=-1;
    Arcnode *temp=NULL;
    bool bcycle=false;//环标志
    int pos=0;//写入output数组的位置
    for(i=0;i<n;i++)//入度为0的顶点入栈
    {
        if(Count[i]==0)
        {
            Count[i] = top;
            top = i;
        }
    }
    for(i=0;i<n;i++)
    {
        if(top==-1)
        {
            bcycle = true;//栈为空了，存在有向环
            break;
        }
        else
        {
            int j=top;
            top=Count[top];//栈顶顶点j出栈

            pos+=sprintf(output+pos,"%d ",j+1);

            temp = List[j];
            //遍历顶点j的边链表，每条出边的终点的入度减1
            while(temp!=NULL)
            {
                int k=temp->to;
                if(--Count[k]==0)//入栈
                {
                    Count[k]=top;
                    top=k;
                }
                temp=temp->next;
            }
        }
    }
    if(bcycle) puts("Network has a cycle!\n");
    else
    {
        int len = strlen(output);
        output[len-1] = 0;//去掉最后的空格'\0'
        printf("%s\n",output);

    }
}
int main()
{
    int i,u,v;
    while(true)
    {
        scanf("%d%d",&n,&m);
        if(n==0 && m==0)break;
        memset(List,0,sizeof(List));
        memset(Count,0,sizeof(Count));
        memset(output,0,sizeof(output));
        Arcnode *temp=NULL;
        for(i=0;i<m;i++)//构造边链表
        {
            scanf("%d%d",&u,&v);
            u--;v--;
            Count[v]++;
            temp = new Arcnode;
            temp->to = v;
            temp->next = NULL;
            if(List[u]==NULL)
                List[u]=temp;
            else
            {
                temp->next = List[u];
                List[u]=temp; //头插法
            }
        }
        TopSort();
        for(i=0;i<n;i++)//释放空间
        {
            temp = List[i];
            while(temp!=NULL)
            {
                List[i]=temp->next;
                delete temp;
                temp=List[i];
            }
        }
    }
    return 0;
}
