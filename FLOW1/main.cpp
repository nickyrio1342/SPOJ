#include <bits/stdc++.h>

#define FOR(i, a, b) for(int i = a; i<=b; i++)

using namespace std;

struct Edge {
    int u, v, cap, flow;
};

#define N 2001
struct Dinic {
    int n, s, t, m;
    int d[N], ptr[N], q[N];
    vector<Edge> e;
    vector<int> g[N];
    pair<int, int> f[N];
    const int inf = 1e9;

    Dinic(int n, int m, int s, int t) :m(m), n(n), s(s), t(t) {
        e.clear();
        FOR(i, 1, m) f[i].first = f[i].second = 0;
        FOR(i, 0, (n + m) * 2 + 1) {
            ptr[i] = 0;
            g[i].clear();
        }
    }

    void AddEdge(int u, int v) {
        Edge ee = {u, v, 1, 0};
        g[u].push_back((int) e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0};
        g[v].push_back((int) e.size());
        e.push_back(ee);
    }

    void getMaxFlow() {
        int flow = 0;
        while (bfs()) {
            while (sendFlow(s, inf))
                flow++;
        }
        //return;
    }

    void getInfo() {
        for(Edge ee : e ) {
            if (ee.u == 0 || ee.v > 2 * (n + m) || (ee.u > 2 * n && ee.u <= 2 * n + m) || ee.flow != 1) continue;
            if (ee.u <= n) {
                f[ee.v - 2 * n].first = ee.u;
            }
            if (ee.v <= 2 * n)
                f[ee.u - 2 * n - m].second = ee.v - n;
        }
        FOR(i, 1, m) {
            pair<int, int> z = f[i];
            cout<<f[i].first<<' '<<f[i].second<<'\n';
        }
        //return;
    }

private:
    bool bfs() {
        int start = 0, last = 0;
        FOR(i, 0, 2 * (m + n) + 1) {
            ptr[i] = 0;
            d[i] = -1;
        }
        d[s] = 0;
        q[last++] = s;
        while (start < last) {
            int u = q[++start];
            for(int id : g[u]) {
                int v = e[id].v;
                if (d[v] == -1 && e[id].flow < e[id].cap) {
                    d[v] = d[u] + 1;
                    q[++last] = v;
                }
            }
        }
        return d[t] != -1;
    }

    bool sendFlow(int u, int flow) {
        if (!flow) return false;
        if (u == t) return true;
        for(; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] != d[u] + 1) continue;
            if (sendFlow(v, min(flow, e[id].cap - e[id].flow))) {
                e[id].flow++;
                e[id ^ 1].flow--;
                return true;
            }

        }
        return false;
    }
};

int n, m;
string st;
int main() {
    freopen("input.txt","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n>>m;
    getline(cin, st);
    Dinic D(n, m, 0, 2 * (m + n) + 1);
    FOR(i, 1, m) D.AddEdge(2 * n + i, 2 * n + m + i);
    FOR(i, 1, n) {
        D.AddEdge(0, i);
        getline(cin, st);
        int x;
        stringstream ss(st);
        while (ss >> x) {
            D.AddEdge(i, 2 * n + x);
        }
    }
    FOR(i, 1, n) {
        D.AddEdge(i + n, 2 * (n + m) + 1);
        getline(cin, st);
        int x;
        stringstream ss(st);
        while (ss >> x) {
            D.AddEdge(x + 2 * n + m, i + n);
        }
    }
    D.getMaxFlow();
    D.getInfo();
}
