#include <bits/stdc++.h>

using namespace std;

#define N 100001
int n;
long long a[N], f[N], MOD;
double p[N];
vector<int> e[N];

long long cal(const long long a, const long long b) {
    if (b == 0) return 0;
    if (b == 1) return a;
    long long t = cal(a, b >> 1);
    t = (t + t) % MOD;
    if (b % 2 == 1) t = (t + a) % MOD;
    return t;
}

void dfs(int u, int pa) {
    f[u] = a[u];
    p[u] = log10(a[u]);
    double mx = 0;
    long long ans = 1;
    for (int v : e[u]) {
        if (v != pa) {
            dfs(v, u);
            if (mx < p[v]) {
                ans = f[v];
                mx = p[v];
            }
        }
    }
    f[u] = cal(f[u], ans);
    p[u] += mx;
}
int main() {
    cin.tie(NULL);cout.tie(NULL);
    scanf("%d%lld", &n, &MOD);
    for (int i = 1; i<=n; i++) scanf("%lld", &a[i]);
    int u, v;
    for (int i = 1; i<n; i++) {
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, -1);
    printf("%lld", f[1]);
}
