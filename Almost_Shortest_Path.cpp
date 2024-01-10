// UVA12144 Almost Shortest Path
// Accepted 100
// Author: 0Arctic0 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
using namespace std;
const int N=100001;
const int INF=2147483647;
int head1[N],ver1[N],edge1[N],nxt1[N],tot1,d1[N];bool vis1[N];
int head2[N],ver2[N],edge2[N],nxt2[N],tot2,d2[N];bool vis2[N];
set<pair<pair<int,int>,int > >se;
//三个参数分别为:从<1>到<2>的边,边权为<3>. 
void add(int x,int y,int z)
{
    ver1[++tot1]=y;
    edge1[tot1]=z;
    nxt1[tot1]=head1[x];
    head1[x]=tot1;
}
void add2(int x,int y,int z)
{
    ver2[++tot2]=y;
    edge2[tot2]=z;
    nxt2[tot2]=head2[x];
    head2[x]=tot2;
}
int n,m,s,d;
void dj(int s)//正图
{
    priority_queue<pair<int,int> >q;
    for(int i=0;i<=n;i++) d1[i]=INF;
    memset(vis1,0,sizeof(vis1));
    d1[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        if(vis1[x]) continue;
        vis1[x]=1;
        for(int i=head1[x];i;i=nxt1[i])
        {
            int y=ver1[i],z=edge1[i];
            if(d1[y]>d1[x]+z)
            {
                d1[y]=d1[x]+z;
                q.push(make_pair(-d1[y],y));
            }
        }
    }
}
void dj2(int s)//反图 
{
    priority_queue<pair<int,int> >q;
    for(int i=0;i<=n;i++) d2[i]=INF;
    memset(vis2,0,sizeof(vis2));
    d2[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        if(vis2[x]) continue;
        vis2[x]=1;
        for(int i=head2[x];i;i=nxt2[i])
        {
            int y=ver2[i],z=edge2[i];
            if(d2[y]>d2[x]+z)
            {
                d2[y]=d2[x]+z;
                q.push(make_pair(-d2[y],y));
            }
        }
    }
}
void dj3(int s)//打过标记的原图 注意不要跑成反图 
{
    priority_queue<pair<int,int> >q;
    for(int i=0;i<=n;i++) d1[i]=INF;
    memset(vis1,0,sizeof(vis1));
    d1[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int x=q.top().second;q.pop();
        if(vis1[x]) continue;
        vis1[x]=1;
        for(int i=head1[x];i;i=nxt1[i])
        {
            int y=ver1[i],z=edge1[i];
            if(se.count(make_pair(make_pair(x,y),z))) continue;
            //set的其中一个用法就是统计元素个数,很好理解也很好实现. 
            if(d1[y]>d1[x]+z)
            {
                d1[y]=d1[x]+z;
                q.push(make_pair(-d1[y],y));
            }
        }
    }
}
signed main()
{
    while(true)
    {
        memset(head1,0,sizeof(head1));
        memset(head2,0,sizeof(head2));
        tot1=tot2=0;se.clear();//初始化.  trick:邻接表初始化仅需重置head. 

        scanf("%d%d",&n,&m);
        if(n==0 && m==0) break;
        scanf("%d%d",&s,&d);
        for(int i=1,a,b,c;i<=m;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
            add2(b,a,c);//正反图 
        }
        dj(s);dj2(d);
        if(d1[d]==INF)//特判: 原图即无法到达直接输出-1 
        {
            puts("-1");
            continue;
        }
        for(int i=0;i<n;i++)//打标记:set使用. 注意数据存在0号点 
        {
            for(int j=head1[i];j;j=nxt1[j])
            {
                int y=ver1[j],z=edge1[j];
                if(d1[i]+d2[y]+z==d1[d])
                    se.insert(make_pair(make_pair(i,y),z));
                //由于没有重边,所以可以不存边权,但是为了保险还是加上了
                //不存边权也能AC. 
            }
        }
        dj3(s);
        printf("%d\n",d1[d]==INF?-1:d1[d]);
    }
    return 0;
}