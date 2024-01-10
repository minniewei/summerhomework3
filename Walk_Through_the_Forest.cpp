/*************************************************************************
  > File Name: 10917 - A Walk Through the Forest.cpp
  > Author: Samuel
  > Mail: enminghuang21119@gmail.com
  > Created Time: Tue Sep  4 12:04:50 2018
*************************************************************************/

#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> link[1001];
vector<int> rebuild[1001];
const int inf = 1 << 30;
int distant[1001];
int dp[1001];
bool visit[1001];
int n, m;

struct node {
    int dis, index;
    bool operator< (const node &b) const {
        return dis > b.dis;
    }
    node() {}
    node(int d, int i) : dis(d), index(i) {}
};
int dfs(int now) {
    if (now == 1)
        return 1;
    if (dp[now] == -1) {
        dp[now] = 0;
        for (auto i : rebuild[now])
            dp[now] += dfs(i);
    }
    return dp[now];
}
void dijkstra() {
    priority_queue<node> pq;
    pq.push(node(0, 1));
    int cur;
    distant[1] = 0;
    while (!pq.empty()) {
        cur = pq.top().index;
        pq.pop();
        if (visit[cur])
            continue;
        visit[cur] = 1;
        for (auto i : link[cur]) {
            int next = i.first;
            int dis = i.second;
            if (distant[next] > distant[cur] + dis) {
                distant[next] = distant[cur] + dis;
                pq.push(node(distant[next], next));
            }
        }
    }
}
void build() {
    memset(dp, -1, sizeof(dp));
    int next, dis;
    for (int i = 0; i < n; i++) {
        rebuild[i].clear();
        for (auto j : link[i])
            if (distant[i] > distant[j.first])
                rebuild[i].emplace_back(j.first);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a, b, c;
    while (cin >> n >> m && n) {
        memset(link, 0, sizeof(link));
        memset(visit, 0, sizeof(visit));
        for (int i = 0;i < n; i++)
            distant[i] = inf;
        while (m--) {
            cin >> a >> b >> c;
            link[--a].push_back({--b, c});
            link[b].push_back({a, c});
        }
        dijkstra();
        build();
        cout << dfs(0) << '\n';
    }
}