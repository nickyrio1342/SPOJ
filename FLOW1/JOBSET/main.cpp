#include <bits/stdc++.h>

using namespace std;

#define N 510
#define FOR(i, a, b) for (int i = a; i<b; i++)

int n, m, a[N];

struct Edge {
    int u, v, cap, flow;
};
struct Dinic {
    int n, s, t;
    vector<int> q, d, ptr;
    vector<Edge> e;
    vector< vector<int> > g;
    const int inf = 1e9;

    Dinic (int n) :n(n), q(n), d(n), ptr(n), g(n) {
        e.clear();
        FOR(i, 0, n) g[i].clear();
    }

    void addEdge(int u, int v, int cap) {
        Edge e1 = {u, v, cap, 0};
        Edge e2 = {v, u, 0, 0};
        g[u].push_back((int) e.size());
        e.push_back(e1);
        g[v].push_back((int) e.size());
        e.push_back(e2);
    }

    int getMaxFlow(int ss, int tt) {
        s = ss; t = tt;
        int flow = 0;
        while (bfs()) {
            while(int pushed = sendFlow(s, inf)) {
                flow += pushed;
            }
        }
        return flow;
    }

private:
    bool bfs() {
        int start = 0, last = 0;
        FOR(i, 0, n) {
            d[i] = -1;
            ptr[i] = 0;
        }
        d[s] = 0;
        q[last++] = s;
        while (start < last) {
            int u = q[start++];
            if (u == t) return true;
            for (int id : g[u]) {
                int v = e[id].v;
                if (d[v] == -1 && e[id].cap > e[id].flow) {
                    q[last++] = v;
                    d[v] = d[u] + 1;
                }
            }
        }
        return false;
    }

    int sendFlow(int u, int flow) {
        if (!flow) return 0;
        if (u == t) return flow;
        for(; ptr[u] < (int)g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] != d[u] + 1) continue;
            if (int x = sendFlow(v, min(flow, e[id].cap - e[id].flow))) {
                e[id].flow += x;
                e[id ^ 1].flow -= x;
                return x;
            }
        }
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    Dinic D(n + 2);
    int maxA = 0;
    int s = 0; int t = n + 1;
    FOR(i, 1, n + 1) {
        cin>>a[i];
        if (a[i] > 0) {
            maxA += a[i];
            D.addEdge(s, i, a[i]);
        } else D.addEdge(i, t, -a[i]);
    }
    cin>>m;
    int u, v;
    FOR(i, 0, m) {
        cin>>u>>v;
        D.addEdge(u, v, maxA + 1);
    }
    cout<<maxA - D.getMaxFlow(s, t);
}
