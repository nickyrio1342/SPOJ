#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b; i++)

using namespace std;
#define N 201
int c[N][N];

struct HopcroftKarp {
    int n;
    vector< vector<int> > e;
    vector<int> match, d;
    const int inf = 1e9;
    int NIL = 0;

    HopcroftKarp(int n) :n(n), e(2 * n + 2), match(2 * n + 2), d(2 * n + 2) {
        FOR(i, 1, 2 * n + 1) {
            e[i].clear();
            match[i] = d[i] = 0;
        }
    }

    void enter(int m) {
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if (c[i][j] <= m) {
                    e[i].push_back(j + n);
                    e[j + n].push_back(i);
                }
            }
        }
    }

    int getMaxMatching() {
        int matching = 0;
        while (bfs()) {
            FOR(i, 1, n) {
                if (match[i] == NIL && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
private:
    bool bfs() {
        queue<int> q;
        FOR(i, 1, n) {
            if (match[i] == NIL) {
                d[i] = 0;
                q.push(i);
            } else d[i] = inf;
        }
        d[NIL] = inf;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
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
            if (d[match[v]] != d[u] + 1) continue;
            if (dfs(match[v])) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }
};
int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    FOR(i, 1, n) FOR(j, 1, n) cin>>c[i][j];
    int l = 0;
    int r = 1e9;
    int cur = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        HopcroftKarp HK(n);
        HK.enter(m);
        if (HK.getMaxMatching() == n) {
            cur = m;
            r = m - 1;
        } else l = m + 1;
    }
    cout<<cur;
}