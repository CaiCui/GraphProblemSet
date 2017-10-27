#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮���ܶ��ٻ�·����
  ���ܶ��ٻ�·��������һ����·������ͼ��ÿ������һ���ҽ�һ�Σ����Ϊ���ܶ��ٻ�·
  û����Ч�ķ��������ж���ֻ�г���������Ҫ�������е��ж�
  �������һ�����ܶ��ٻ�·�������⡣
  ZOJ2398 ������� ״̬ѹ��dp���(״ѹdpͨ������np�����С��ģ���)
  ����һ�����⣬���������ؿ����������״ѹdp���np�����⣬ͬʱҲ���Կ��������⺺�ܶ��ٻ�·����
*/
#define MAXN 13  //���������Ŀ
#define MAXSTATUS 1<<13 //״̬�������Ŀ
__int64 dp[MAXSTATUS][MAXN][MAXN]; //״̬ת�Ʒ��̣���һά��ʾ״̬������ʹ����״̬ѹ���ķ�������һλ��������ʾ�߹��ĵ�ļ���(6:0110��ʾ�߹�1,2������)��DP�����б���������[row][col]��Ϊ���ж��¼���ĵ��Ƿ��ܺ��������㹹�������Σ��Ӷ��������������
__int64 ways[MAXSTATUS][MAXN][MAXN]; //·����
int value[MAXN];  //�����ֵ��¼
bool link[MAXN][MAXN]; //ͼ
int nislands; //������Ŀ
__int64 maxvalue; //��õĺ��ܶ���·����Ȩֵ
__int64 maxways; //��õĺ��ܶ���·������Ŀ
void initial()
{
    int nbridges;
    int i;
    int row,col;
    scanf("%d%d",&nislands,&nbridges);
    for(i=0;i<nislands;i++)
    {
        scanf("%d",value+i);
    }
    if(nislands==1)return;
    memset(dp,-1,sizeof(dp));//ע���ʼ������Ϊ0���������û��·����ʱ���0�������ֵ
    memset(ways,0,sizeof(ways));
    memset(link,0,sizeof(link));
    for(i=0;i<nbridges;i++)
    {
        scanf("%d%d",&row,&col);
        row--;
        col--;
        link[row][col]=1;
        link[col][row]=1;
        dp[(1<<row)|(1<<col)][row][col]=value[row]*value[col]+value[row]+value[col];
        dp[(1<<row)|(1<<col)][col][row]=value[row]*value[col]+value[row]+value[col];
        ways[(1<<row)|(1<<col)][row][col]=1,ways[(1<<row)|(1<<col)][col][row]=1;
    }
}
void compute()
{
    int i,j,k,s;
    __int64 temp;
    int nextstatus;
    if(nislands==1)//ֻ��һ������
    {
        maxvalue=value[0];
        maxways=1;
        return;
    }
    for(s=0;s<(1<<nislands);s++)//��С�������״̬ת�ƣ�����·��ѹ�����൱���Ȱ�����״̬��ö�ٳ���(�����Ʊ�ʾ״̬)��Ȼ���ٴ�״̬���ϳ��������
    {
        for(i=0;i<nislands;i++)
        {
            if(s&(1<<i))//���߹��ļ���s�еĵ�����&���㣬���ĳ����1<<i��s�У���s&(1<<i)==1��ʾ�õ��ڼ�����
            {
                for(j=0;j<nislands;j++)
                {
                    if(i!=j && (s&(1<<j)) && dp[s][i][j]>-1)//���i,j����״̬����s�У�˵���ñ��߹��ˣ�����dp[][][]���¹�
                    {
                        for(k=0;k<nislands;k++)
                        {
                            if(!(s&(1<<k)) && link[i][k]==1)//ö���µ�δ���߹�����������ֹ��ĵ�
                               {
                                   nextstatus=s|(1<<k);//����õ���״̬����
                                   //�ۼӵ���Ȩֵ�ͱ�Ȩֵ
                                   temp=dp[s][i][j]+value[k]+value[k]*value[i];
                                   //����������������ۼ�����Ȩֵ
                                   if(link[j][k]==1)
                                    temp+=value[k]*value[i]*value[j];
                                  if(dp[nextstatus][k][i]==temp)//����õ����󣬷���֮ǰҲ���ֹ����ֽ������ֻ��Ҫ�����µ�·���߷���������˵��֮ǰû���ֹ����ֽ���������Ϊ��ǰ���ŵĽ�����µ�·���߷�
                                  {
                                      ways[nextstatus][k][i]+=ways[s][i][j];
                                  }
                                  else if(dp[nextstatus][k][i]<temp)
                                  {
                                      ways[nextstatus][k][i]=ways[s][i][j];
                                      dp[nextstatus][k][i]=temp;
                                  }
                               }
                        }
                    }
                }
            }
        }
    }
    maxvalue=-1;
    maxways=0;
    s=(1<<nislands)-1;//����ȫ��11111...11
    //ͳ����õ����Ǻ��ܶ���·����Ȩֵ����Ŀ
    for(i=0;i<nislands;i++)
    {
        for(j=0;j<nislands;j++)
        {
            if(!link[i][j])continue;
            if(dp[s][i][j]==maxvalue)
                maxways+=ways[s][i][j];
            else if(dp[s][i][j]>maxvalue)
            {
                maxvalue =dp[s][i][j];
                maxways=ways[s][i][j];
            }
        }

    }
    maxways=maxways/2;
}
int main()
{
    int i;
    int cases;
    scanf("%d",&cases);
    for(i=0;i<cases;i++)
    {
        initial();
        compute();
        if(maxvalue==-1)
            printf("0 0\n");
        else
            printf("%I64d %I64d\n",maxvalue,maxways);
    }
    return 0;
}
