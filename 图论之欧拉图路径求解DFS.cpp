#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮�����Ա���ŷ����·����---ŷ����·���
  ����һ DFS
  ����ŵ���� �ⲻΨһ
  1.��ͼ(�ڽӱ���ƽ�б�����)
  2.����
*/
#define VNUM 6 //6������
#define MAXN 101 //������Ŀ
struct EdgeNode{
    int adjvex;
    int EdgeNo;
    int flag;  //1����-1����
    EdgeNode *nextedge;
};
EdgeNode *EdgeLink[VNUM+1];//����ͷ����0,1,2...6
int visited[MAXN]; //�߷��ʱ�־
//ŷ��ͨ·�ϸ��ߵ����
int path[MAXN]; //path[i]=j��i��Ϊ��j�����-j��ʾ��ת
int pi;  //path[]�������±�
int N;
void CreateG()//�ڽӱ�ͼ
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
void DFSL(int start)//DFS����,д�ĺܰ�
{
    while(pi<=N)//���б�δ����
    {
        EdgeNode *p;
        p=EdgeLink[start];
        while(p!=NULL)
        {
            if(!visited[p->EdgeNo])
            {
                //ͬһ�ߵ������������ڽӵ�EdgeNo��ͬ����֤������ͬһ��·
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
void Domino()//���
{
    int JDNum=0;//������������
    int start1,start2; //��������ʼ����
    EdgeNode *p;
    int i,j;
    for(i=1;i<=6;i++)
    {
        int DNum=0; //�������
        p=EdgeLink[i];
        while(p!=NULL)
        {
            DNum++;
            p=p->nextedge;
        }
        if(DNum%2!=0)
        {
            start1=i;//��¼�������
            JDNum++;
        }
        if(DNum!=0)start2=i;//��¼ż�����
    }
    if(JDNum!=0&&JDNum!=2)
    {
        printf("No Solution!\n");
        return;
    }
    pi=1;
    //����ŷ����·(ͨ·)ѡ���
    if(JDNum==2)
        DFSL(start1);//ͨ·
    else
        DFSL(start2);//��·

    char flag1='+',flag2='-';
    for(i=1;i<=N;i++)
    {
        if(path[i]>0)
            printf("%d%c\n",path[i],flag1);
        else
            printf("%d%c\n",-path[i],flag2);
    }

}
void DeleteLG()//�ͷſռ�
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
