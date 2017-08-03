#include <bits/stdc++.h>

using namespace std;

#define N 310
struct HopcroftKarp {
    int n, m, x, y;
    vector<int> e[N * N], match, d;
    int dd[N][N];
    char a[N][N];
    const int inf = 1e9;
    int NIL = 0;
    void go1(int &u, int &v) {
        if (u == x || v == y) return;
        if (a[u][v] == 'A') {
            v++;
            return;
        }
        dd[u][v] = m; v++;
        go1(u, v);
    }

    void go2(int &u, int &v) {
        if (u == x || v == y) return;
        if (a[u][v] == 'A') {
            u++;
            return;
        }
        if (a[u][v] != 'D') {
            e[dd[u][v]].push_back(m);
        }
        u++;
        go2(u, v);
    }

    void enter() {
        n = m = 0;
        cin>>x>>y;
        for (int i = 0; i<x; i++)
            for (int j = 0; j<y; j++)
                cin>>a[i][j];
        memset(dd, 0, sizeof dd);
        for (int i = 0; i<x;i++) {
            for (int j = 0; j<y;) {
                if (a[i][j] == 'A') {j++;continue;}
                m++; go1(i, j);
            }
        }
        n = m;
        for (int j = 0; j<y;j++) {
            for (int i = 0; i<x;) {
                if (a[i][j] == 'A') {
                    i++;continue;
                }
                m++; go2(i, j);
            }
        }
        match.resize(m + 1);
        d.resize(m + 1);
    }

    int getMaxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 1; i<=n; i++) {
                while (match[i] == NIL && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
private:
    bool bfs() {
        queue<int> q;
        for (int i = 1; i<=n; i++) {
            if (match[i] == NIL) {
                q.push(i);
                d[i] = 0;
            } else d[i] = inf;
        }
        d[NIL] = inf;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == NIL) continue;
            for (int v : e[u]) {
                if (d[match[v]] == inf) {
                    d[match[v]] = d[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return d[NIL] != inf;
    }

    bool dfs(int u) {
        if (u == NIL) return true;
        for (int v : e[u]) {
            if (d[match[v]] == d[u] + 1) {
                if (dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
};

#define testcase int test; cin>>test ; while(test--)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    testcase{
        HopcroftKarp Graph;
        Graph.enter();
        cout<<Graph.getMaxMatching()<<endl;
    }
}
