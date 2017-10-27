#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮�ڽӱ�: �����������ͼ���رߵ�ͼ���ʺϱ�ϡ���ͼ����ʡ�洢�ռ�
  ���ڽӱ�洢����ͼ�������������ĳ��Ⱥ����
*/
#define MAXN 100
//�ڵ㣬�������ͼһ���ߵ���һ���ڽӵ���ţ�����һ���ڵ��ָ��
struct node{
    int adjvex;
    node *next;
};
//ÿ���ڵ�洢����Ϣ�ṹ�������ýڵ�ı�ź���ýڵ������ĳ��ߺ����
struct VNode{
  int data;//������
  node *head1;//���߱��ͷ
  node *head2;//��߱��ͷ
};
struct Graph{
  VNode vertex[MAXN];//ͼ�Ķ�������
  int vexnum,arcnum;//�������ͱ���
};
Graph lg;
//��ͼ
void CreateG()
{
   int i=0;
   node *pi;
   int v1,v2;
   for(i=0;i<lg.vexnum;i++)//��ʼ��ÿ���ڵ��˫���ͷָ��
   {
       lg.vertex[i].head1=lg.vertex[i].head2=NULL;
   }
   for(i=0;i<lg.arcnum;i++)//����ߣ�����ͷ�巨�����ڽӱ�
   {
       scanf("%d%d",&v1,&v2);
       v1--;
       v2--;
       //���߱�
       pi=new node();
       pi->adjvex=v2;
       pi->next=lg.vertex[v1].head1;
       lg.vertex[v1].head1=pi;

       //��߱�
       pi=new node();
       pi->adjvex=v1;
       pi->next=lg.vertex[v2].head2;
       lg.vertex[v2].head2=pi;

   }
}

//�ͷ�ͼ
void DeleteG()
{
   int i;
   node *pi;
   for(i=0;i<lg.vexnum;i++)
   {
       pi=lg.vertex[i].head1;
       //�ͷ�ÿ�����head1
       while(pi!=NULL)
       {
           lg.vertex[i].head1=pi->next;
           free((void *)pi);
           pi= lg.vertex[i].head1;
       }

       pi=lg.vertex[i].head2;
       //�ͷ�ÿ�����head2
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
