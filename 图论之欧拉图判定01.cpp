#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮�����Ա���ŷ����·����---ŷ����·(ŷ��ͼ)���ж�
  ŷ����·����һ������������ظ��ı��������б߲��ص���ʼ�������
  ŷ��ͼ������ŷ����·������ͼ����Ҫ������ͼGΪ����Ƚ�����ͨͼ
  ����ŷ����·��ŷ����·������ͼ��ʽ
  ZOJ1395 ׯ԰�ܼ�
  �ѵ㣺������еĴ���
*/
int readLine(char *s)//���ַ�����ʽ����ÿ�����ݲ������ַ�������
{
    int L;
    for(L=0;(s[L]=getchar())!='\n'&&s[L]!=EOF;L++);
    s[L]=0;
    return L;
}
int main()
{
    int i,j;
    char buf[128];
    int M,N;
    int door[20];
    while(readLine(buf))
    {
        if(buf[0]=='S')
        {
            sscanf(buf,"%*s %d %d",&M,&N);//�ַ����������,����*��ʾ����������
            for(i=0;i<N;i++)
                door[i]=0;
            int doors=0;
            for(i=0;i<N;i++)
            {
                readLine(buf);
                int k=0;
                while(sscanf(buf+k,"%d",&j)==1)//���ش�buf+kλ�ÿ�ʼ�İ��ո�ʽ˵���ɹ�ת����������ֶ�����ת��ʱ����ǰ��ո񣬱�������  2   3��scanf("%d%d",&a,&b)ʱ��a,b��Ȼ��2��3��ssscanf()����
                {
                    doors++;
                    door[i]++;
                    door[j]++;
                    while(buf[k]&&buf[k]!=' ')k++;
                    while(buf[k]&&buf[k]==' ')k++;

                }

            }
            readLine(buf);//END
            int odd=0,even=0;
            for(i=0;i<N;i++)
              if(door[i]%2==0)
                even++;
              else
                odd++;
            if(odd==0&&M==0)
                printf("YES %d\n",doors);
            else if(odd=2&&door[M]%2==1&&door[0]%2==1&&M!=0)
                printf("YES %d\n",doors);
            else
                printf("NO\n");
        }
        else if(!strcmp(buf,"ENDOFINPUT"))
            break;
    }
    return 0;
}
