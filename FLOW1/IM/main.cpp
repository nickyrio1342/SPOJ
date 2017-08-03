#include <bits/stdc++.h>

using namespace std;
#define testcase int test; scanf("%d", &test); while (test--)

struct edge {
    int u, v, cap, flow;
};

struct Dinic {
    int n, s, t;
    const int inf = 1e9;
    vector<int> d, ptr, q;
    vector<edge> e;
    vector< vector<int> >g;

    Dinic(int n): n(n), g(n), d(n), ptr(n), q(n) {
        e.clear();
        for (int i = 0; i<n; i++) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int u, int v) {
        edge e1 = {u, v, 1, 0};
        edge e2 = {v, u, 0, 0};
        g[u].push_back((int) e.size());
        e.push_back(e1);
        g[v].push_back((int) e.size());
        e.push_back(e2);
    }

    int getMaxFlow(int ss, int tt) {
        s = ss; t = tt;
        int flow = 0;
        while (bfs()) {
            while (int x = sendFlow(s, inf)) flow += x;
        }
        return flow;
    }
private :
    bool bfs() {
        int start = 0, last = 0;
        for (int i = 0; i<n; i++) {
            ptr[i] = 0;
            d[i] = -1;
        }
        d[s] = 1;
        q[last++] = s;
        while (start < last) {
            int u = q[start++];
            for (int id: g[u]) {
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
        for (; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] != d[u] + 1 || e[id].cap <= e[id].flow) continue;
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
    int n, m, u, v;
    cin.tie(NULL);cout.tie(NULL);
    testcase {
        scanf("%d%d", &n, &m);
        Dinic D(2 * n + 1);
        while (m--) {
            scanf("%d%d", &u, &v);
            if (u > n || v > n) continue;
            if (u != 2 && v != 2) {
                D.addEdge(u, u + n);
                D.addEdge(v, v + n);
                D.addEdge(v + n, u);
                D.addEdge(u + n, v);
            }
            else {
                if (u == 2) D.addEdge(2, v);
                else D.addEdge(2, u);
            }
        }
        D.addEdge(1, 0);
        D.addEdge(3, 0);
        if (D.getMaxFlow(2, 0) == 2) {
            printf("YES\n");
        }else printf("NO\n");
    }
}
