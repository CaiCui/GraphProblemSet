#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮AOE����--��������
  ZOJ1060
  ����N����д��ĸ���������ǵ�һЩƫ���ϵ��Ҫ���жϳ��������ٸ�ƫ���ϵ֮�����ȷ�����ǵ�������ߴ��ڳ�ͻ���������е�ƫ���ϵ����֮�������޷�ȷ��Ψһ������
  �������������һ��Ϣ��ÿ����һ�Թ�ϵ������ж��н��������Ժ��Ժ����������ݣ���ʹ�������������ܸı�����Ҳ���ùܡ�
  ����Ӧ��ÿ����һ����ϵ��ȥ���µ�ǰ��ͼ��Ȼ�����һ����������һ������������ٶԺ�������ݴ����£��Ϳ�����������

  ������
  �����������򼴿ɽ��������⣬��������ĿҪ����Ǿ������ٸ���ϵ֮��Ϳ���ȷ���𰸣����ÿ����һ����ϵ����Ҫ����һ����������
  ���ĳһ����������֮�����ȷ�����ǵ�Ψһ������߷��ֳ�ͻ���ڣ�������ֱ���Թ������������й�ϵ֮����Ȼ�޷�ȷ��Ψһ��ϵ��ͬʱҲû�г�ͻ��
  ���������ȷ��Ψһ��������������Ĺ�����ÿ�ν���һ�������Ϊ0����������ǿ���ȷ��������
  ��������������Ϊ0����֪���ĸ������ĸ����������������е�ĳһ��֮���޷��ټ�������˵�����ڻ�·����ʱ˵�����ڳ�ͻ��
*/
int Count[26]; //��߱���¼��������
int temp[26];
char relation[3],seq[26];//��ϵ��������д洢
char reseq[26];
bool alpha[26];//bool�����ж��ַ��Ƿ񱻼�¼
int n,m;
vector<vector<char> >v; //ʹ��stl��vector���ͼ
//��������������������Ԫ�ظ�����������ì���򷵻�-1���޷��жϷ���0
int topsort(int s)
{
    int i,j,r,cnt;//cnt��ʾ���Ϊ0�Ķ��������r��ʾ�õ�������Ԫ�صĸ���
    bool flag; //��Ǳ���,��ʾ����������Ƿ���Եõ�����
    r=0,cnt=0;
    for(i=0;i<n;i++)temp[i]=Count[i];
    flag=1;
    while(s--)
    {
        cnt=0;
        for(i=0;i<n;i++)
        {
            if(temp[i]==0)
            {
                j=i;
                cnt++;
            }
        }
        if(cnt>=1)
        {
            //cnt=1��ʾ���ҽ���һ�����Ϊ0�ĵ㣬�ĵ��Ȼ����������ǰ��
            if(cnt>1)//�������������Ԫ�ص�һ����ϵ���У��������������ɵ�ͼ�����Ӧ��ֻ����ǰ��Ϊ0���������cnt>1,˵��ҪôԪ�ػ�û��ȫ����ͼ��
			 flag=0;  //������Ҫ��������л�û���룬ҪôԪ�ض������˵�ͼ�д��ڶ�����Ϊ0�ĵ㣬���޷��ж�����Ԫ�صĴ�С��ϵ��
            for(i=0;i<v[j].size();i++)
              temp[v[j][i]]--;//�������ɾ���ö��㼰����(����Ӧ��������)
            seq[r++]=j+'A';
            temp[j]=-1; //����������ȥ���ĵ��Ϊ-1
            seq[r]=0;//seq���н�β��ʶ��

        }
        else if(cnt==0)//û�����Ϊ0�ĵ㣬��Ȼ���ڻ�
        {
            return -1;
        }
    }
    if(flag)return r;
    else return 0;
}
int main()
{
    int i,j,t,k,c;
    int determined;//��־������-1��ʾ��ϵì�ܣ�0��ʾ�޷��õ����У�1��ʾ���Եõ�����
    while(scanf("%d%d",&n,&m)!=EOF && n!=0 && m!=0)
    {
        memset(Count,0,sizeof(Count));
        memset(alpha,false,sizeof(alpha));
        v.clear();
        v.resize(n);//������С
        c=0;
        determined = 0;
        for(i=0;i<m;i++)//�����ϵ��
        {
            scanf("%s",relation);//��������
            Count[relation[2]-'A']++; //���
            v[relation[0]-'A'].push_back(relation[2]-'A');//���߱���
            if(!alpha[relation[0]-'A'])//��¼����Ķ������
            {
                c++;
                alpha[relation[0]-'A'] = true;
            }
            if(!alpha[relation[2]-'A'])
            {
                c++;
                alpha[relation[2]-'A'] = true;
            }
            if(determined == 0)
            {
                t = topsort(c);
                if(t == -1)
                {
                    determined = -1;
                    k = i+1;

                }
                else if(t==n)
                {
                    determined =1;
                    k = i+1;
                    memcpy(reseq,seq,sizeof(seq));//���ﲻ���ݣ��������seq���Ϊ0�������Ǿֲ���������ֵ������
                }
            }
        }
        if(determined == -1)
        {
            printf("Inconsistency found after %d relations. \n",k);
        }
        else if(determined==0)
        {
            printf("Sorted sequence cannot be determined.\n");
        }
        else
        {
            printf("Sorted sequence determined after %d relations: %s.\n",k,reseq);
        }

    }

    return 0;
}
