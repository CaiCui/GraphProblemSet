#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���ж��������·��--Floyd�㷨
  ZOJ1967 ��������
  ���ƹ�ʽ��
  1.A(0)[i][j]=�ṩi��jֱ�������Ĺ�˾����
  2.A(k)[i][j]=������{A(k-1)[i][j],������(A(k-1)[i][k],A(k-1)[k][j])k=0,1,..n}=m[i][j]|=m[i][k]&m[k][j]
  ����Flyod�ĵ��Ʊ����������·�ߣ�ͬʱ�����˶����Ƶ�λ����ʵ�ֵ��Ƽ��ϵĻ��������
*/
#define MAXN 201
int main()
{
    int m[MAXN][MAXN];
    int n;
    int A,B;
    int i,j,k;
    char str[27];
    char ch;
    while(scanf("%d",&n)&&n)
    {
        memset(m,0,sizeof(m));
        while(scanf("%d%d",&A,&B))//�ṩֱ��AB�Ĺ�˾
        {
            if(A==0&&B==0)break;
            scanf("%s",str);
            for(i=0;str[i];i++)
            {
                m[A][B]|=1<<(str[i]-'a');
            }
        }
        //Flyod
        for(k=1;k<=n;k++)
        {
            for(i=1;i<=n;i++)
            {
                for(j=1;j<=n;j++)
                {
                    m[i][j]|=m[i][k]&m[k][j];
                }
            }
        }
        //��ѯ
        while(scanf("%d%d",&A,&B))
        {
            if(A==0&&B==0)break;
            for(ch='a';ch<='z';++ch)
            {
                if(m[A][B]&(1<<ch-'a'))
                    putchar(ch);
            }
            if(!m[A][B])putchar('-');
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}
