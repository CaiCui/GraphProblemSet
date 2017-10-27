#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮BFS����
  ZOJ2913:��������ͨƱ
  ������һ���������еļ���,������Ŀ,ֵ�÷���˼��
  ������
  �����Ŀ�����ҵ�һ������Z,ʹ���������й�����·�ϵĵ����Զ���뾡������С����Ҫ�������еĹ���վ�㣬����ʹZ������Զ���Ǹ�վ��ľ��뾡������С��
  Ҳ�����ҵ�һ����ν�Ĺ�����·����ġ����ĵ㡰��
  ���Կ�����ô�ɣ�
  �Թ�����·�ϵ�ÿ��վ�����BFS����������ÿ�ζ�Ҫ�ڱ������ĵ�j�ϼ�¼������ǰ����վ��ľ���res[j]����BFS�Ĳ�Σ�Ȼ������ÿ��վ��BFS�����Ľ��У�Ҫһֱ���ָ���
  ÿ���������ĵ�j����ǰ����BFS�����Ĺ���վ��ľ��룬ʹÿ���������ĵ�j��res[j]�������ǵ�ǰ�Ѿ���������վ�������µ����ֵ(�������Ա�֤��ǰ��վ��Ҳ�ᱻ����������ͬʱ��ǰվ��Ҳ�ᱻ��������)��
  ����վ�����BFS�󣬶��Ÿ��½�����res[]��������ȡ����С���Ǹ���������Ҫ��Ľ������Ϊ�����Ĳ��������ͳ��ÿ�����򵽰���ÿ��վ��ľ������Сֵ�����������н����Сֵ���ҳ���Сֵ����
  ���յ���Сֵ�⡣

*/
#define ZMAX 10000 //������ŵ����ֵ
#define INF 100000 //һ������ֵ
int nz,nr;//������Ŀ��������·��Ŀ
int mz[ZMAX]; //mz[i]Ϊ���i���������ڵĵ�����Ŀ

int Edge[ZMAX][10];//���Ϊi�ĵ����ĵ�j�����ڵ����ı��
int res[ZMAX]; //ÿ����·�ϵ�ÿ������������i�ľ����е����ֵ
int cur; //��¼��ǰ������վ�����,cur==0��ʾ��һվ
int reach[ZMAX]; //reach[s]=cur,��ʾ����s�ڵ�cur+1վ�Ѿ����ʹ�
int Max(int x,int y)
{
    return (x>y)?x:y;
}
void BFS(int s)
{
    int i,a,b;
    int val,att;//val ��¼�㣬�����롣att ��ʾ��ǰ�ڵ�
    queue<int>q[2];
    a=0,b=1,val=0;
    if(reach[s]<cur)
    {
      q[b].push(s);
      reach[s]=cur;
      res[s]=Max(res[s],val+1);
    }
    while(!q[b].empty())
    {
        swap(a,b);//�������У�����洢��1���Ԫ�أ��ڶ����Ԫ�أ������㡣������
        val++;
        while(!q[a].empty())//�������е�ǰ�ڵ�
        {
            att=q[a].front();
            q[a].pop();
            for(i=0;i<mz[att];i++)
            {
                if(reach[Edge[att][i]]<cur)
                {
                    q[b].push(Edge[att][i]);
                    reach[Edge[att][i]]=cur;
                    res[Edge[att][i]]=Max(res[Edge[att][i]],val+1);
                }
            }
        }
    }
}

int main()
{
    int T;
    int i,j,t;
    int id;
    int mr;
    int ret,center;
    scanf("%d",&T);
    for(t=0;t<T;t++)
    {
        memset(reach,-1,sizeof(reach));
        memset(res,0,sizeof(res));
        cur=0;
        scanf("%d%d",&nz,&nr);
        for(i=0;i<nz;i++)
        {
            scanf("%d",&id);
            scanf("%d",&mz[id]);
            for(j=0;j<mz[id];j++)scanf("%d",&Edge[id][j]);
        }
        for(i=0;i<nr;i++)//��ÿ����·�ϵ�ÿ������bfs����
        {
            scanf("%d",&mr);
            for(j=0;j<mr;j++)
            {
                scanf("%d",&id);
                BFS(id);//��ÿ��������·��ÿ��������id��������bfs����
                cur++;
            }
        }
        ret=INT_MAX;
        center=-1;
        for(i=0;i<10000;i++)//�����С��
        {
            if(reach[i]==cur-1 &&res[i]<ret)//cur-1==reach[i]��ʾ�ǹ������ϵ����һ����Ҫ������վ����������������������ֵ�ĸ��£�ѡ�����ֵ�б��е���Сֵ��������Ǵ�
            {
                ret=res[i];
                center=i;
            }
        }
        printf("%d %d\n",ret,center);
    }
    return 0;
}
