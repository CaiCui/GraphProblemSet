#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮AOE����--��������
  ZOJ2193 ���ڻ���
  ������Ŀ:
  1.ͨ����������Ļ���ڷֲ����������ͼ
  2.�ж�����ͼ�Ƿ��������������������Ϊ�쳣
*/
int screen[4][4];//��Ļ���������ʾ�����ݣ������������
bool exist[10];//��¼ĳ�������Ƿ�����Ļ�����ϳ���
int id[10];//���
bool g[10][10];//�ڽӱ�
const int n=4;
int t;//��¼��Ļ�ϳ��ֵĲ�ͬ���ڵ����࣬������Ϊ���㣬��������ͼ
string s;//�����ַ������ݵ���ʱ����
string cover[4][4];//��ʾ�ܹ�����(i.j)λ�õĴ��ڵļ���
void calc()//ͳ���ܹ�����(i,j)λ�õĴ��ڼ���,����string���ַ�������
{
    int k,i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            cover[i][j].erase();
    }
    for(k=1;k<=9;k++)
    {
        i=(k-1)/3;
        j=(k-1)%3;
        cover[i][j]+=char(k+'0');//��k���������Ͻǵ�λ��
        cover[i][j+1]+=char(k+'0');//��k���������Ͻǵ�λ��
        cover[i+1][j]+=char(k+'0');//��k���������½ǵ�λ��
        cover[i+1][j+1]+=char(k+'0');//��k���������½ǵ�λ��

    }
}
void init()//��ȡ��Ļ��������
{
    int i,j,k;
    memset(exist,0,sizeof(exist));
    memset(id,0,sizeof(id));
    memset(g,0,sizeof(g));
    t=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>k;
            screen[i][j]=k;
            if(!exist[k])t++;
            exist[k]=true;
        }
    }
}
void build()//��������ͼ
{
    int i,j,p;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //screen[i][j]�ܹ�����סcover[i][j]�г����������ÿ������
            for(p=0;p<cover[i][j].length();p++)
            {
                if( (!g[screen[i][j]][cover[i][j][p]-'0'])&&(screen[i][j]!=cover[i][j][p]-'0') )
                {
                    g[screen[i][j]][cover[i][j][p]-'0']=true;
                    id[cover[i][j][p]-'0']++;//���++
                }
            }
        }
    }
}
bool check() //���������ж���
{
    int k,j,i;
    for(k=0;k<t;k++)
    {
       i=1;
       //ͳ�Ƴ�������Ļ�����У���Ȳ�Ϊ0�Ĵ��ڸ���
       while(!exist[i]||(i<=9&&id[i]>0))//��һ���жϰ�����������Ϊ0��i��Ȼ����к������������Ҳ�����˶��ڲ���ͼ�еĵ�ͨ�����л��ĵ���жϣ�
           i++;                         //��Ϊ���Ϊ0�ĵ��ں����exist[i]=false,����Խ����ѭ����ͨ��������Խ�ɣ�
                                        //��i������++�����ͼ���л���ؿ�ͨ�����ж�(�����ֶ�ʵ��)�����Ե�ȥ������ͼ�еļ�exist[]=false���ʹ���������Ϊ0�ģ�����л���ôi++�������ӵ�10>9����󷵻�false
       
       if(i>9)//���д�����Ⱦ���Ϊ0�����Ȼ���ڻ�
        return false;
       //������Ϊi�Ĵ��ڣ�ɾ���ô����Լ�����Ӧ�ĳ���
       exist[i]=false;
       for(j=1;j<=9;j++)
       {
           //ɾ����Ӧ�������
           if(exist[j]&&g[i][j])
            id[j]--;
       }
    }
    return true;
}
int main()
{
    calc();
    while(cin>>s)
    {
        if(s=="ENDOFINPUT")break;
        init();//��������
        cin>>s;
        build();//��������ͼ
        if(check())cout<<"THESE WINDOWS ARE CLEAN\n"<<endl;
        else
            cout<<"THESE WINDOWS ARE BROKEN\n"<<endl;
        cin>>s;
    }
    return 0;
}
