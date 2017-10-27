#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  ͼ��֮�����Ա���ŷ����·����---ŷ����·(ŷ��ͼ)���ж�
  ZOJ2016 ������Ϸ ����ŷ��ͨ·+���鼯�жϻ�ͼ��ͨ��
*/
#define MAXN 1000001
#define INF 100000000
int T;
int N;
char word[1001];
int od[26],id[26];//ÿ����ĸ�ĳ��Ⱥ����
int bused[26];//��i����ĸ�����鵥�����Ƿ���Ϊ��β��ĸ
int parent[26];//i���ڼ��϶�Ӧ�����еĸ����
struct edge{
 int u,v;
}edges[MAXN];
//���鼯����
void UFset()
{
    for(int i=0;i<26;i++)
        parent[i]=-1;
}
int Find(int x)//����x�����ļ��ϵĸ����
{
    int s;
    for(s=x;parent[s]>=0;s=parent[s]);
    while(s!=x)
    {
        int tmp=parent[x];
        parent[x]=s;
        x=tmp;
    }
    return s;
}
//�ϲ�����
void Union(int R1,int R2)
{
    int r1=Find(R1);
    int r2=Find(R2);
    int tmp=parent[r1]+parent[r2];
    if(parent[r1]>parent[r2])
    {
        parent[r1]=r2;
        parent[r2]=tmp;
    }
    else
    {
        parent[r2]=r1;
        parent[r1]=tmp;
    }
}
bool bconnect()//�ж�����ͼ�Ļ�ͼ�Ƿ���ͨ
{
    int u,v,i;
    UFset();
    for(i=0;i<N;i++)//�ж�ÿ���ߣ�������ͬһ��ͨ������ϲ�
    {
        u=edges[i].u;
        v=edges[i].v;
        if(u!=v&&Find(u)!=Find(v))//u==v��һ������㲻���벢�鼯
            Union(u,v);
    }
    int first=-1;//
    for(i=0;i<26;i++)
    {
        if(bused[i]==0)continue;
        if(first==-1)first=i;
        else if(Find(i)!=Find(first))
            break;//����ͨ
    }
    if(i<26)return false;
    return true;
}
int main()
{
    int u,v;
    int i,j;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        memset(od,0,sizeof(od));
        memset(id,0,sizeof(id));
        memset(bused,0,sizeof(bused));
        scanf("%d",&N);
        for(j=0;j<N;j++)
        {
            scanf("%s",word);
            u=word[0]-'a';
            v=word[strlen(word)-1]-'a';
            od[u]++;
            id[v]++;
            bused[u]=bused[v]=1;
            edges[j].u=u;
            edges[j].v=v;
        }
        bool Euler=true;
        int one=0;
        int none=0;
        //������ж�
        for(j=0;j<26;j++)
        {
            if(bused[j]==0)continue;
            if(od[j]-id[j]>=2||id[j]-od[j]>=2)
            {
                Euler=false;
                break;
            }
            if(od[j]==0&&id[j]==0){
                Euler=false;
                break;
            }
            if(od[j]-id[j]==1)
            {
                one++;
                if(one>1){
                    Euler=false;
                    break;
                }
            }
            if(id[j]-od[j]==1)
            {
                none++;
                if(none>1){
                    Euler=false;
                    break;
                }
            }
        }

        if(one!=none)Euler=false;
        if(!bconnect())Euler=false;
        if(Euler)
            printf("Ordering is possible.\n");
        else
            printf("The door cannot be opened.\n");
    }
    return 0;
}
