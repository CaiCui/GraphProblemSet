#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮BFS:
  2002 �ߺ����ӵ���Ϸ ����BFS˼��ľ�����Ŀ
  ˼�룺����BFS��α�����˼�룬ֻ����ͼ�Ľڵ�״̬�ı仯�������˽ڵ����չ�����Ľ����˿ռ临�Ӷ�
*/
#define NMAX 20
#define SLMAX 200
struct SnakeAndLadder{//�ߺ�����
 int from,to;
};
int main()
{
    int D;
    int N,S,L;
    int grid[NMAX*NMAX+1]; //���̣���Ŵ�1��ʼ
    int gridbak[NMAX*NMAX+1];//������һ�ε�����״̬
    SnakeAndLadder obstacle[2*SLMAX];//�ϰ���
    int i,j,k,m;
    int step;//Ͷ�����ӵĴ���
    int deal;
    scanf("%d",&D);
    for(i=0;i<D;i++)
    {
        scanf("%d%d%d",&N,&S,&L);
        for(j=0;j<S+L;j++)
            scanf("%d%d",&obstacle[j].from,&obstacle[j].to);
        memset(grid,0,sizeof(grid));
        grid[1]=1;
        step=0;
        //ֻҪ��N^2������û�е���1״̬���ͼ���BFS
        while(grid[N*N]==0){
            memcpy(gridbak,grid,sizeof(grid));//������һ��״̬
            memset(grid,0,sizeof(grid));
            for(j=1;j<=N*N-1;j++)//���һ����
            {
                if(gridbak[j]==0)
                    continue;
                for(k=1;k<=6;k++)//6�����
                {
                    deal=0;
                    if(j+k>N*N)break;//Խ��
                    for(m=0;m<S+L;m++)//j+k��λ�öԿ������߻�����ö�ٲ���
                    {
                        if(obstacle[m].from==j+k)
                        {
                            grid[obstacle[m].to]=1;
                            deal=1;
                            break;
                        }
                    }
                    //�������ߺ�����
                    if(deal==0 && grid[j+k]==0)grid[j+k]=1;
                }
            }
          step++;//������1
        }
        printf("%d\n",step);
    }
    return 0;
}
