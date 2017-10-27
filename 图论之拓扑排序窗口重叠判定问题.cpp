#include<bits/stdc++.h>
using namespace std;
/*
  图论之AOE网络--拓扑排序
  ZOJ2193 窗口绘制
  经典题目:
  1.通过给定的屏幕窗口分布构造出有向图
  2.判断有向图是否带环，无则正常，有则为异常
*/
int screen[4][4];//屏幕快照最后显示的内容，即输入的内容
bool exist[10];//记录某个窗口是否在屏幕快照上出现
int id[10];//入度
bool g[10][10];//邻接表
const int n=4;
int t;//记录屏幕上出现的不同窗口的种类，以它们为顶点，构造有向图
string s;//读入字符串数据的临时变量
string cover[4][4];//表示能够覆盖(i.j)位置的窗口的集合
void calc()//统计能够覆盖(i,j)位置的窗口集合,利用string的字符串连接
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
        cover[i][j]+=char(k+'0');//第k个窗口左上角的位置
        cover[i][j+1]+=char(k+'0');//第k个窗口右上角的位置
        cover[i+1][j]+=char(k+'0');//第k个窗口左下角的位置
        cover[i+1][j+1]+=char(k+'0');//第k个窗口右下角的位置

    }
}
void init()//读取屏幕快照数据
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
void build()//构建有向图
{
    int i,j,p;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //screen[i][j]能够覆盖住cover[i][j]中除它本身外的每个窗口
            for(p=0;p<cover[i][j].length();p++)
            {
                if( (!g[screen[i][j]][cover[i][j][p]-'0'])&&(screen[i][j]!=cover[i][j][p]-'0') )
                {
                    g[screen[i][j]][cover[i][j][p]-'0']=true;
                    id[cover[i][j][p]-'0']++;//入度++
                }
            }
        }
    }
}
bool check() //拓扑排序判定环
{
    int k,j,i;
    for(k=0;k<t;k++)
    {
       i=1;
       //统计出现在屏幕快照中，入度不为0的窗口个数
       while(!exist[i]||(i<=9&&id[i]>0))//这一步判断包含了求出入度为0的i，然后进行后面的拓扑排序，也包含了对于不在图中的点通过和有环的点的判断，
           i++;                         //因为入度为0的点在后面会exist[i]=false,所以越往后本循环可通过的条件越松，
                                        //即i更容易++，如果图中有环则必可通过该判断(可以手动实验)，所以当去掉不在图中的即exist[]=false，和处理过的入度为0的，如果有环那么i++将会增加到10>9，最后返回false
       
       if(i>9)//所有窗口入度均不为0，则必然存在环
        return false;
       //处理编号为i的窗口，删除该窗口以及其相应的出边
       exist[i]=false;
       for(j=1;j<=9;j++)
       {
           //删除相应顶点入边
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
        init();//读入数据
        cin>>s;
        build();//构造有向图
        if(check())cout<<"THESE WINDOWS ARE CLEAN\n"<<endl;
        else
            cout<<"THESE WINDOWS ARE BROKEN\n"<<endl;
        cin>>s;
    }
    return 0;
}
