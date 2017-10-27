#pragma comment(linker,"/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
/*
  图论之可行性遍历欧拉回路问题---欧拉回路(欧拉图)的判定
  欧拉回路：从一个顶点出发不重复的遍历完所有边并回到起始点的问题
  欧拉图：具有欧拉回路的无向图，充要条件是图G为无奇度结点的连通图
  有向欧拉回路：欧拉回路的有向图形式
  ZOJ1395 庄园管家
  难点：输入空行的处理
*/
int readLine(char *s)//以字符串形式读入每行数据并返回字符串长度
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
            sscanf(buf,"%*s %d %d",&M,&N);//字符串读入变量,加入*表示不读此数据
            for(i=0;i<N;i++)
                door[i]=0;
            int doors=0;
            for(i=0;i<N;i++)
            {
                readLine(buf);
                int k=0;
                while(sscanf(buf+k,"%d",&j)==1)//返回从buf+k位置开始的按照格式说明成功转换并分配的字段数，转换时忽略前后空格，比如输入  2   3，scanf("%d%d",&a,&b)时，a,b依然是2和3，ssscanf()类似
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
