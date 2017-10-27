#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮ͼ��DFS����
  ZOJ2110 ��ͷ���ջ� �����Ŀ��TLE��������֦�Ǹ��ѵ�
*/
char Map[9][9];
int n,m,t;
int di,dj;
bool escape;
int dir[4][2]={0,-1,0,1,1,0,-1,0};
void dfs(int si,int sj,int cnt)
{
    int i,temp;
    if(si>n||sj>m||si<=0||sj<=0)return;
    if(si==di&&sj==dj&&cnt==t)
    {
        escape=1;return;
    }
    //��֦,temp%2 �ж������� ����a-b������1����Ҳ������3���������ߵȼۣ���ʣ�ಽ��(t-cnt)��ʣ����̾���fabs(si-di)+fabs(sj-dj)����ż����һ���ģ��κ���+һ��ż�������������ʲ���
    //����+ż��=������ż��+ż��=ż����Ҳ����ʣ�ಽ����ʣ����̾��������ż��һ�²ſ����н⣬������һ��ʱ�������ǵȼ۵ģ�������ô�룬����ʣ��3����ʣ����̾���1����ô����������һ�������л��ᵽ���յ㣬Ҳ���Ǿ��ε�
    //�����֡�
    /* ͼʾ��
       a--b
       |  |  a-b������ֱ��a�ߵ�b,Ҳ����a-c-d-b�������߷������ܴ��ڽ⣬�������ڿɽ������ǵȼ۵ģ��������������Ҫ�����������������Ϊ����������5-2=3����5��������ô��Ҳ�ȼ۲���2�����������ܵ����յ㣡
       c--d
    */
    temp=(t-cnt)-fabs(si-di)-fabs(sj-dj);
    if(temp<0||temp%2)return;
    for(i=0;i<4;i++)
    {
        if(Map[si+dir[i][0]][sj+dir[i][1]]!='X')
        {
            Map[si+dir[i][0]][sj+dir[i][1]]='X';
            dfs(si+dir[i][0],sj+dir[i][1],cnt+1);
            if(escape)return;
            Map[si+dir[i][0]][sj+dir[i][1]]='.';
        }
    }
    return;
}
int main()
{
    int i,j;
    int si,sj;
    while(scanf("%d%d%d",&n,&m,&t))
    {
        if(n==0&&m==0&&t==0)break;
        int wall=0;
        char temp;
        scanf("%c",&temp);//�������з������׳���������getchar()
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
              scanf("%c",&Map[i][j]);
              if(Map[i][j]=='S'){si=i;sj=j;}
              else if(Map[i][j]=='D'){di=i;dj=j;}
              else if(Map[i][j]=='X')wall++;
            }
            scanf("%c",&temp);
        }
        if(n*m-wall<=t)
        {
            printf("NO\n");
            continue;
        }
        escape=0;
        Map[si][sj]='X';
        dfs(si,sj,0);
        if(escape)
          printf("YES\n");
        else
          printf("NO\n");

    }
    return 0;
}
