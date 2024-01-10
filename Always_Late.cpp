#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define int long long
#define MAXN 120
#define INF 2100000000
using namespace std;
struct Edge{ // 我們使用 Edge struct 實做 (root, cost)
    int v, c;
    Edge(): v(0), c(0) {}
    Edge(int _v, int _c): v(_v), c(_c) {}
};
struct Status{ // 我們使用 Status struct 實做 priority_queue (root, cost)
    int v, c; //v 節點, c 成本
    Status(): v(0), c(0) {}
    Status(int _v, int _c): v(_v), c(_c) {}

    bool operator < (const Status& other) const{
        return c < other.c; //遞減排序，決定 priority_queue 的方式
        //return c > other.c; //遞增排序
    }
};

int kase = 1;
int n, r, q, start, destination;
int a, b, c;
vector<Edge> edge[MAXN];
int dist[MAXN][2];
int visit[MAXN];

void dijkstra(int root){
    //because dijkstra find second shortest path,which push duplicate node
    //priority_queue<Status> q; //TLE
    deque<Status> q;
    q.push_back({root,0}); //初始放入開始點
    dist[root][0] = 0; //自己到自己成本為零

    int cost;
    while(!q.empty()){
        Status node = q.front(); q.pop_front();
        //cout << node.v << " " << node.c << "\n";

        visit[node.v] = 0; //分析 2-5 可以再次經過他，因為不會使 deque 節點中資料在裡面 circle
        for(auto it: edge[node.v]){
            cost = dist[node.v][0] + it.c;
            if(cost != dist[it.v][0] && cost != dist[it.v][1]){ //分析 2-2
                if(cost < dist[it.v][1]){ //分析 2-3
                    dist[it.v][1] = cost;
                    //分析 2-4
                    if(cost < dist[it.v][0]) swap(dist[it.v][0], dist[it.v][1]); 
                    if(!visit[it.v]){ //分析 2-5
                        visit[it.v] = 1;
                        q.push_back({it.v, cost});
                    }

                }

            }

            cost = dist[node.v][1] + it.c; 
            if(cost != dist[it.v][0] && cost != dist[it.v][1]){ //分析 2-2
                if(cost < dist[it.v][1]){  //分析 2-3
                    dist[it.v][1] = cost;
                    //分析 2-4
                    if(cost < dist[it.v][0]) swap(dist[it.v][0], dist[it.v][1]);
                    if(!visit[it.v]){ //分析 2-5
                        visit[it.v] = 1;
                        q.push_back({it.v, cost});
                    }
                }
            }


        }
    }
}

int32_t main()
{
#ifdef LOCAL
    freopen("in1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif // LOCAL
    while(cin >> n >> r){
        for(int i = 0; i < n; i++) edge[i].clear();
        for(int i = 0; i < r; i++){
            cin >> a >> b >> c;
            edge[a].push_back({b,c});
            edge[b].push_back({a,c});
        }

        cin >> q;
        cout << "Set #" << kase++ << "\n";
        while(q--){
            for(int i = 0; i < n; i++){
                dist[i][0] = INF;
                dist[i][1] = INF;
            }
            memset(visit, 0, sizeof(visit));

            cin >> start >> destination;
            dijkstra(start);
            if(dist[destination][1] == INF) cout << "?\n";
            else cout << dist[destination][1] << "\n";
        }
    }

    return 0;
}