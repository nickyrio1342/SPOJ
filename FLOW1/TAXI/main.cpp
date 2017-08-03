#include <bits/stdc++.h>

using namespace std;

#define testcase int test; scanf("%d", &test); while(test--)
#define N 606

struct HopcroftKarp {
    int n, m, s, c, match[N], d[N], y[N], x[N];
    const int inf = 1e9;
    int NIL = 0;
    vector<int> e[N];

    bool dis(int i, int j) {
        long long dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
        if (double(dist * 200ll) / s > c) return false;
        return true;
    }

    void enter() {
        scanf("%d%d%d%d", &n, &m, &s, &c);
        for (int i = 1; i<=n + m; i++) {
            e[i].clear();
            match[i] = 0;
        }
        for (int i = 1; i<=n + m; i++) {
            scanf("%d%d", &x[i], &y[i]);
        }
        for (int i = 1; i<=n; i++) {
            for (int j = n + 1; j<=n + m; j++) {
                if (dis(i, j)) {
                    e[i].push_back(j);
                    e[j].push_back(i);
                }
            }
        }
    }

    int getMaxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 1; i<=n; i++)
                while (match[i] == NIL && dfs(i))
                    matching++;
        }
        return matching;
    }
private:
    bool bfs() {
        queue<int> q;
        for (int i = 1; i<=n; i++) {
            if (match[i] == NIL) {
                d[i] = 0;
                q.push(i);
            } else d[i] = inf;
        }
        d[NIL] = inf;
        while (!q.empty() && d[NIL] == inf) {
            int u = q.front();q.pop();
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
        if (u != NIL) {
            for (int v : e[u]) {
                if (d[match[v]] == d[u] + 1) {
                    if (dfs(match[v])) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                }
            }
            d[u] = inf;
            return false;
        }
        return true;
    }

};
int main() {
    freopen("E:\\input.txt","r",stdin);
    freopen("E:\\output.txt","w",stdout);
    cin.tie(NULL);cout.tie(NULL);
    HopcroftKarp Graph;
    testcase {
        Graph.enter();
        printf("%d\n",Graph.getMaxMatching());
    }
}
