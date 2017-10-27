#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮AOV�����--��������
  DAG�������޻�ͼ
  ����AOV������Ҫ�ж��Ƿ���DAGͼ�������ǹ������������������У�������������,ע��һ��AOV����������������п��ܲ�Ψһ
  �㷨��
  1.��AOV��ѡ��һ�����Ϊ0�ĵ㲢���
  2.��AOV��ɾ���õ㼰�Ӹõ㷢�������б�
  3.�ظ�����1,2��ֱ���Ҳ������Ϊ0�ĵ�
  �жϣ������е�����ˣ����޻�������ʣ�����ж���û�������˵���л�
  ʵ�֣����ö���ջ�ͳ��߱�ʹ�ö���Ҳ����ȷ��
  ����˼·�����Ƚ�������ı�����ͷָ������List���飬Ȼ��ͳ��ÿ��������ȣ�����count���飬
  ����ʱ������ɨ��count���飬�����Ϊ0�Ķ�����ջ������Ϊ�˽�ʡ�ڴ棬count���鱾�����ջ��ֻ��Ҫά��һ��
  topָ�룬ÿ�μ�¼ջ��Ԫ�ص�λ�ã�Ȼ���ջ�����ε���ջ�������������ɨ��ö���ĳ��߱���ÿ���߽ڵ��
  �յ����ȼ�1���������0�ˣ���ô���ö�����ջ����n���㶼��ջ�󣬼����ж����޻����ڡ�
*/
#define MAXN 10
struct Arcnode{
  int to;
  struct Arcnode *next;
}; //�ڵ�����
int n,m;
Arcnode* List[MAXN];//ÿ������ı������ͷָ��
int Count[MAXN];//������ȱ�(ͬʱ��Ϊջ)
char output[100];//�������

void TopSort()//��������
{
    int i,top=-1;
    Arcnode *temp=NULL;
    bool bcycle=false;//����־
    int pos=0;//д��output�����λ��
    for(i=0;i<n;i++)//���Ϊ0�Ķ�����ջ
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
            bcycle = true;//ջΪ���ˣ���������
            break;
        }
        else
        {
            int j=top;
            top=Count[top];//ջ������j��ջ

            pos+=sprintf(output+pos,"%d ",j+1);

            temp = List[j];
            //��������j�ı�����ÿ�����ߵ��յ����ȼ�1
            while(temp!=NULL)
            {
                int k=temp->to;
                if(--Count[k]==0)//��ջ
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
        output[len-1] = 0;//ȥ�����Ŀո�'\0'
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
        for(i=0;i<m;i++)//���������
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
                List[u]=temp; //ͷ�巨
            }
        }
        TopSort();
        for(i=0;i<n;i++)//�ͷſռ�
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
