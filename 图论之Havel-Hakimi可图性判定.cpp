#include<bits/stdc++.h>
using namespace std;
/*
1.2 �����ھ� POJ1659
˼·������Havel-Hakimi�����жϸ��������Ƿ��ͼ(����ͼ)����ͼ���ӡ���
      ���ֲ��������Σ�1.ĳ�ζ�ʣ�µ���������󣬳��������Ķ���������ʣ��Ķ�������
                      2.��������(d1)�����d1����������1�󣬳����˸������������ǳ����˷�������
*/
#define MAXN 100
struct vertex{
  int degree;//����Ķ�
  int index;//�������
}v[MAXN];
int cmp(const void *a,const void *b)
{
    return ((vertex *)b)->degree-((vertex*)a)->degree;//����
}
int main()
{
    int T,p,q,n,i,j,r,k;
    int Edge[MAXN][MAXN];
    int flag;
    int d1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d",&v[i].degree);
            v[i].index=i;
        }
        memset(Edge,0,sizeof(Edge));
        flag=1;
        for(k=0;k<n&&flag;k++)//Havel-hakimi
        {
            //������ĺ�n-k��Ԫ�����򣬷ǵ���˳��
            qsort(v+k,n-k,sizeof(vertex),cmp);
            i=v[k].index;
            d1=v[k].degree;
            if(d1>n-k-1) {flag=0;break;}
            for(r=1;r<=d1&&flag;r++)
            {
                j=v[r+k].index;
                if(v[r+k].degree<=0)flag=0;//���������<=��������<����Ϊ�������ж���d1��ʣ������������ϵ�����ж���r��d1�Ĺ�ϵ������r��ʼΪ1����������<���������г���0ʱҲ���ƹ��ж���Ϊ����⡣
                                           //Ҳ����˵�ܽ����ѭ����d1һ����>=1�ģ����������ʱ������������0����ô�϶��Ͳ����������ˣ�����ֱ���˳�ѭ���ˡ���������
                v[r+k].degree--;
                Edge[i][j]=Edge[j][i]=1;
            }
        }
        if(flag)
        {
            puts("YES");
            for(p=0;p<n;p++)
            {
                for(q=0;q<n;q++)
                {
                    if(q) printf(" ");
                    printf("%d",Edge[p][q]);
                }
                puts("\n");
            }

        }
        else
            puts("NO\n");
    }

    return 0;
}
