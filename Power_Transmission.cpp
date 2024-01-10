#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define CLR(c) memset(c, 0, sizeof(c))

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

template <typename T>
T QPOP(queue<T>& q)
{
    T tmp = q.front();
    q.pop();
    return tmp;
}

const int INF = (int)1e9;
const int MXN = 205;

int S, T;
int rn[MXN][MXN];
int l[MXN];

int N;

void init()
{
    CLR(rn);
}

void read()
{
    FOR(i, 1, N + 1) cin >> rn[i][i + N];

    int u, v, w, m;
    cin >> m;
    while (m--) cin >> u >> v >> w, rn[u + N][v] = w;

    int I, O;
    T = 2 * N + 1;
    cin >> I >> O;
    while (I--) cin >> v, rn[S][v] = INF;
    while (O--) cin >> u, rn[u + N][T] = INF;
}

bool dinicBFS()
{
    CLR(l);

    queue<int> q;
    q.push(S);
    l[S] = 1;

    while (!q.empty())
    {
        int u = QPOP(q);

        FOR(v, 0, T + 1)
        {
            if (l[v] || !rn[u][v]) continue;
            l[v] = l[u] + 1;
            q.push(v);
        }
    }

    return l[T];
}

int dinicDFS(int u, int cp)
{
    if (u == T) return cp;

    int tmp = cp;

    FOR(v, 0, T + 1 && tmp)
    {
        if (l[v] != l[u] + 1 || !rn[u][v]) continue;
        int bt = dinicDFS(v, min(rn[u][v], tmp));
        rn[u][v] -= bt;
        rn[v][u] += bt;
        tmp -= bt;
    }

    return cp - tmp;
}

int maximumFlow()
{
    int mf = 0;
    while (dinicBFS()) mf += dinicDFS(S, INF);
    return mf;
}

void solve()
{
    cout << maximumFlow() << '\n';
}

int main()
{
    while (cin >> N)
    {
        init();
        read();
        solve();
    }
}