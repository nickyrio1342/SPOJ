#include <bits/stdc++.h>

using namespace std;
#define N 300

struct HopcroftKarp {
    int n = 120, match[N], d[N];
    vector<int> e[N];
    const int inf = 1e9;
    int NIL = 0;

    void enter() {
        for (int i = 0; i<N; i++) e[i].clear();
        memset(match, 0, sizeof match);
        int k, u, v;
        scanf("%d", &k);
        while (k--) {
            scanf("%d%d", &u, &v);
            v += n;
            v++; u++;
            e[u].push_back(v);
            e[v].push_back(u);
        }
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
                d[i] = 0;
                q.push(i);
            }else d[i] = inf;
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
#define testcase int test; scanf("%d", &test); while (test--)
int main() {
    cin.tie(NULL);cout.tie(NULL);
    testcase {
        HopcroftKarp Graph;
        Graph.enter();
        printf("%d\n",Graph.getMaxMatching());
    }
}
