#include <bits/stdc++.h>
using namespace std;
/*
    �����㷨(�����㷨)ʵ��.cpp �������ͼ����С��������Ҳ����С����ͼ�����ȹ̶�һ�����������Ȩֵ��С������ͼ
    �ѵ㣺���Ĵ���
    ���⣺hdu2121 pku3164 Command Network(ģ����)
*/
const int MAXNODE=1010;
const int MAXEDGE=100010;
typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge{
    int u,v;
    Type dis;
    Edge(){}
    Edge(int u,int v,Type dis):u(u),v(v),dis(dis){}
};
struct Directed_MT{
    int n,m;//n:�� m:��
    Edge edges[MAXEDGE];
    int vis[MAXNODE];
    int pre[MAXNODE];
    int id[MAXNODE];
    Type in[MAXNODE];//��¼�����С��ȼ���

    void init(int n){
      this->n = n;
      m = 0;
    }

    void addEdge(int u,int v, Type dis){
     edges[m++]=Edge(u,v,dis);
    }

    Type DirMt(int root){//��������С����ͼ
        Type ans=0;
        int t=0;
        while(true){
            //��ʼ��

            for(int i=0;i<n;i++)
                in[i]=INF;
            //��in[]����
            for(int i=0;i<m;i++)
            {
                int u=edges[i].u;
                int v=edges[i].v;
                //Ѱ����С��ȱߣ�ɾ���Ի�
                if(edges[i].dis<in[v] && u!=v)
                {
                    in[v]=edges[i].dis;

                    pre[v]=u;

                }

            }
             for(int i=0;i<m;i++){
             cout<<edges[i].dis<<" ";

            }
            cout<<endl;
            //���ĳ����û����С��ߣ���ʾ�õ㲻��ͨ��ֱ��ʧ�ܣ�����С����ͼ
            for(int i=0;i<n;i++)
            {
                if(i==root)continue;
                if(in[i]==INF)return -1;
            }

            int cnt=0;//��¼������,ͬʱ������������ĵ�ı�Ÿ���
            memset(id,-1,sizeof(id));//���º�Ľڵ������д����id��
            memset(vis,-1,sizeof(vis));
            in[root]=0;//�����0
            //����·������
            for(int i=0;i<n;i++)
            {
                ans+=in[i];
                //Ϊʲô����Ҫ��in[i]����Ϊ�������е㶼����in[i],���Ժ���������ڻ�Ҫȥ��ĳЩ��in[i]�������൱���Ȳ��ܺû��ӽ������������ͼ�ı�Ȩʱ���ٰѻ�������µ����in[i]��ȥ,���൱��ȥ���˻�ֵ
                int v=i;
                //ͼ��Ѱ�һ��ļ���:�Ѵ�v��ʼ��������·�ϵĵ��vis[]�����Ϊͬһ��i��һ��ĳһ��ڶ��ν���while�жϾ�˵���ڸõ㴦��ʼ�����˻�
                while(vis[v]!=i && id[v]==-1&&v!=root)
                {
                    vis[v]=i;
                    v=pre[v];
                }//����޻����ͻ�һֱ�ҵ�����Ȼ�������һ��ѭ��

                //������cnt,id[v]==-1��֤�˻�ֻ������һ��
                if(v!=root &&id[v]==-1)
                {
                    //���ܴ�i��ʼ�ң���Ϊi���ܲ����Ի��ڣ�����4->3 3->4 3->2 2->1 1>0 i=0ʱ�����ͳ�����v==3�ĵط�
                    for(int u=pre[v];u!=v;u=pre[u])
                        id[u]=cnt;
                    id[v]=cnt++;
                    //ͬһ���ڵĵ��������һ������cnt
                }

            }
            //û�л���ֱ�ӳɹ�
            if(cnt==0)break;

            //�ҵ���Щ���ڻ��ڵĵ㣬���±����Щ��
            for(int i=0;i<n;i++)
                if(id[i]==-1)id[i]=cnt++;//������i=0�Ǹ�������ǡ��id[0]=2;
            //������ͼ��Ȩֵ�ͽڵ���
            for(int i=0;i<m;i++){
                int v=edges[i].v;
                edges[i].v=id[edges[i].v];
                edges[i].u=id[edges[i].u];
                if(edges[i].v!= edges[i].u)//��ʾ�ñ߲��ǻ��еı�,���Լ����µ����
                    {
                        edges[i].dis-=in[v];
                    }
            }

            //�����󣬵����������,��ı��Ҳ����
            n=cnt;
            root=id[root];


        }

        return ans;//��������id�����е�Ԫ��
    }
}MT;
int main()
{
    /*
    pku3164 Command Network ֱ�������Ϸ����뼴�ɼ���
    int a,b;
    int n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(int i=0;i<n;i++)
            scanf("%lf %lf",&p[i].x,&p[i].y);
        int mm=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            if(a==b)continue;
            a--,b--;
            e[mm++]=edge(a,b,dist(p[a],p[b]));
        }
        double ans=Directed_MST(0,n,mm);
        if(ans==-1)
            puts("poor snoopy");
        else printf("%.2f\n",ans);
    }*/
        MT.init(7);
        MT.addEdge(0,1,9);
        MT.addEdge(1,2,3);
        MT.addEdge(2,6,6);
        MT.addEdge(6,5,8);
        MT.addEdge(5,4,3);
        MT.addEdge(0,4,5);
        MT.addEdge(1,3,9);
        MT.addEdge(3,0,3);
        MT.addEdge(4,3,4);
        MT.addEdge(2,1,7);
        MT.addEdge(3,2,8);
        MT.addEdge(3,5,5);
        MT.addEdge(2,5,9);
        MT.addEdge(6,2,4);
        MT.addEdge(5,6,4);
        cout<<MT.DirMt(0)<<endl;
      return 0;
}
