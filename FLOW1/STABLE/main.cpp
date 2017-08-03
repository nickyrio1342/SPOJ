#include <bits/stdc++.h>

using namespace std;

#define N 100001
#define pp pair<int, int>

vector<pp> edge;
vector<int> e[N];
int f[N], g[N], n, m, s;
bool fr[N];
queue<int> q;

void bfs(int s) {
    for (int i = 1; i<=n; i++) {
        f[i] = 1e9;
        g[i] = 0;
        fr[i] = true;
    }
    f[s] = 0;
    g[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        fr[u] = false;
        for (int v : e[u]) {
            if (!fr[v]) continue;
            if (f[v] == f[u] + 1) g[v] += g[u];
            else {
                if (f[v] > f[u] + 1) {
                    f[v] = f[u] + 1;
                    g[v] = g[u];
                    q.push(v);
                }
            }
        }
    }
}
int main() {
    cin.tie(NULL);cout.tie(NULL);
    int u, v;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i<m; i++) {
        scanf("%d%d", &u, &v);
        edge.push_back(pp(u, v));
    }
    sort(edge.begin(), edge.end());
    e[edge[0].first].push_back(edge[0].second);
    for (int i = 1; i<m; i++) {
        //pp bef = edge[i - 1];
        //pp now = edge[i];
        if (edge[i] == edge[i - 1]) continue;
        e[edge[i].first].push_back(edge[i].second);
    }
    bfs(s);int ans = 0;
    for (int i = 1; i<=n; i++) {
        if (g[i] > 1) ans++;
    }
    printf("%d", ans);
}
