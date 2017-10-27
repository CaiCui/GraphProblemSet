#include<bits/stdc++.h>
using namespace std;
/*
  图论之AOE网络--拓扑排序
  ZOJ1060
  对于N个大写字母，给定它们的一些偏序关系，要求判断出经过多少个偏序关系之后可以确定它们的排序或者存在冲突，或者所有的偏序关系用上之后依旧无法确定唯一的排序。
  这道题有隐含这一信息，每输入一对关系，如果判定有结果，则可以忽略后面输入数据，即使后面输入数据能改变结果，也不用管。
  所以应该每输入一个关系就去更新当前的图，然后进行一趟拓扑排序。一旦产生结果，再对后面的数据处理下，就可以输出结果。

  分析：
  利用拓扑排序即可解决这个问题，但由于题目要求的是经过多少个关系之后就可以确定答案，因此每读入一个关系，就要进行一次拓扑排序，
  如果某一次拓扑排序之后可以确定它们的唯一排序或者发现冲突存在，则后面的直接略过。若读入所有关系之后依然无法确定唯一关系，同时也没有冲突，
  则输出不能确定唯一排序。若拓扑排序的过程中每次仅有一个点入度为0，则该排序是可以确定的排序，
  否则若多个点入度为0，则不知道哪个点先哪个点后。若拓扑排序进行到某一步之后无法再继续，则说明存在回路，此时说明存在冲突。
*/
int Count[26]; //入边表，记录顶点的入度
int temp[26];
char relation[3],seq[26];//关系读入和序列存储
char reseq[26];
bool alpha[26];//bool数组判断字符是否被记录
int n,m;
vector<vector<char> >v; //使用stl的vector存放图
//返回拓扑排序后的序列中元素个数，若发现矛盾则返回-1，无法判断返回0
int topsort(int s)
{
    int i,j,r,cnt;//cnt表示入度为0的顶点个数；r表示得到序列中元素的个数
    bool flag; //标记变量,表示拓扑排序后是否可以得到序列
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
            //cnt=1表示有且仅有一个入度为0的点，改点必然处于序列最前端
            if(cnt>1)//由于是求出所有元素的一个关系序列，所以理论上生成的图的入度应该只有最前端为0，所以如果cnt>1,说明要么元素还没完全加入图，
			 flag=0;  //即后面要输入的序列还没输入，要么元素都输完了但图中存在多个入度为0的点，即无法判断所有元素的大小关系。
            for(i=0;i<v[j].size();i++)
              temp[v[j][i]]--;//处理完后删除该顶点及出边(即相应顶点的入边)
            seq[r++]=j+'A';
            temp[j]=-1; //拓扑排序中去掉的点标为-1
            seq[r]=0;//seq序列结尾标识符

        }
        else if(cnt==0)//没有入度为0的点，必然存在环
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
    int determined;//标志变量，-1表示关系矛盾，0表示无法得到序列，1表示可以得到序列
    while(scanf("%d%d",&n,&m)!=EOF && n!=0 && m!=0)
    {
        memset(Count,0,sizeof(Count));
        memset(alpha,false,sizeof(alpha));
        v.clear();
        v.resize(n);//调整大小
        c=0;
        determined = 0;
        for(i=0;i<m;i++)//输入关系组
        {
            scanf("%s",relation);//读入数据
            Count[relation[2]-'A']++; //入度
            v[relation[0]-'A'].push_back(relation[2]-'A');//出边表建立
            if(!alpha[relation[0]-'A'])//记录读入的对象个数
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
                    memcpy(reseq,seq,sizeof(seq));//这里不备份，后面输出seq会变为0，怀疑是局部函数返回值的问题
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
