#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, cap, flow;
};

struct Dinic {
    const int inf = 1e9;
    int n, s, t;
    vector<int> d, ptr, q;
    vector<edge> e;
    vector< vector<int> > g;

    Dinic(int n) : n(n), d(n), ptr(n), q(n), g(n) {
        e.clear();
        for (int i = 0; i<n; i++) {
            g[i].clear();
            ptr[i] = 0;
            //d.push_back(0);
        }
    }

    void addEdge(int u, int v, int cap) {
        edge e1 = {u, v, cap, 0};
        edge e2 = {v, u, 0, 0};
        g[u].push_back((int) e.size());
        e.push_back(e1);
        g[v].push_back((int) e.size());
        e.push_back(e2);
    }

    long long getMaxFlow(int ss, int tt) {
        s = ss; t = tt;
        long long flow = 0;
        while (bfs()) {
            for (int i = 0; i<n; i++) ptr[i] = 0;
            while (int pushed = sendFlow(s, inf)) {
                flow += pushed;
            }
        }
        return flow;
    }
private:
    bool bfs() {
        int start = 0, last = 0;
        q[last++] = s;
        for (int i = 0; i<n; i++) d[i] = -1;
        d[s] = 0;

        while (start < last && d[t] == -1) {
            int u = q[start++];
            for (int id : g[u]) {
                int v = e[id].v;
                if (d[v] == -1 && e[id].cap > e[id].flow) {
                    d[v] = d[u] + 1;
                    q[last++] = v;
                }
            }
        }
        return d[t] != -1;
    }

    int sendFlow(int u, int flow) {
        if (!flow) return 0;
        if (u == t) return flow;
        for (; ptr[u] <(int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] != d[u] + 1) continue;
            edge tmp = e[id];
            int pushed = sendFlow(v, min(flow, e[id].cap - e[id].flow));
            if (pushed > 0) {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};
#define N 5009
long long a[N][N];

int n, m, u, v, w;
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin.tie(NULL);cout.tie(NULL);
    scanf("%d%d", &n, &m);
    Dinic D(n);
    memset(a, 0, sizeof a);
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        a[u][v] += w;
        a[v][u] += w;
    }
    for (int u = 1; u<n; u++) {
        for (int v = u + 1; v<=n; v++) {
            if (a[u][v]) {
                D.addEdge(u - 1, v - 1, a[u][v]);
                D.addEdge(v - 1, u - 1, a[u][v]);
            }
        }
    }
    printf("%lld",D.getMaxFlow(0, n - 1));
}
