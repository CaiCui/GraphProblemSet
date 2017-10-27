#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮�����Ա���ŷ����·����·�����---Fleury�㷨
  �������㷨--����ŷ��ͼ �漰�������߼�(��)
  ģ�壺�����ж��Ƿ����ŷ����·��ͨ·��Ȼ����ڵĻ���ѡ��һ����ȷ�ĵ�
  ���ո������㷨���ŷ����·��ͨ·
  ���㷨ʵ�����ϸ�ڽ��Ϳɲο�"Fleury�㷨ͼ��.docx"
*/
#define MAXN 200
struct Stack{
   int top;
   int node[MAXN];
}s;//����ջ
int Edge[MAXN][MAXN];//����ͼ���ڽӾ���
int n;
void dfs(int x)//һ�ѵ��ף�Ѱ����ͨ�Ӽ�
{
    int i;
    s.top++;
    s.node[s.top]=x;
    for(i=0;i<n;i++)
    {
        if(Edge[i][x]>0)
        {
            Edge[i][x]=Edge[x][i]=0;//ɾ���˱ߣ��ҳ��ŵ�
            dfs(i);
            break;//////����һ����break����һ���������ͬ
        }
    }
}
void Fleury(int x)
{
    int i,b;
    s.top=0;
    s.node[s.top]=x;//��ջ
    while(s.top>=0)
    {
        b=0;
        for(i=0;i<n;i++)
        {
            if(Edge[s.node[s.top]][i]>0)
            {
                b=1;
                break;
            }
        }
        if(b==0)//�޶��������չ���������ջ,��������൱���ҵ����ŵ㣬���ŵ�����������������ڲ�Ӧ�������ţ������ȰѲ��ò����űߵĵ��ҵ����꣬
                //���ߵĵ��ߵľͲ����ű���(��Ϊ����ѡ���ű��Ѿ�������Ҫ���űߵĵ���߹��ˣ���ɾ���ˣ��ǳ������)���൱�����ų�����������˵��ÿ���㶼�жϵ�ǰ���Ƿ����űߣ����������Ӹ�Ч���
        {
            printf("%d",s.node[s.top]+1);
            s.top--;
        }
        else//˵���õ㲻���ű��Ͽ��Լ�����չ���µ���ͨ�Ӽ�
        {
            s.top--;
            dfs(s.node[s.top+1]);//����о�dfs
        }
    }
    printf("\n");
}

int main()
{
    int i,j;
    int m,s,t;
    int degree,num,start;
    scanf("%d%d",&n,&m);
    memset(Edge,0,sizeof(Edge));
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&s,&t);
        Edge[s-1][t-1]=1;
        Edge[t-1][s-1]=1;
    }
    num=0;
    start=0;
    for(i=0;i<n;i++)//�ж��Ƿ����ŷ����·
    {
        degree=0;
        for(j=0;j<n;j++)
            degree+=Edge[i][j];
        if(degree%2==1)
        {
            start=i;
            num++;
        }
    }
    if(num==0||num==2)
        Fleury(1);
    else
        printf("No Euler path\n");
    return 0;
}
