#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = a; i<=b; i++)

using namespace std;
#define N 501
#define M 10011
#define pp pair<int, int>
#define esp 1e-10
int n, m;
struct Data {
    int u, v, s, t;
};

double d[N];
const double oo = 1e18;
int cnt[N];
bool canReach[N];
vector<Data> e[N];

bool check(double mid) {
    FOR(i, 1, n) {
        cnt[i] = 0;
        d[i] = oo;
    }
    d[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();q.pop();
        ++cnt[u];
        if (cnt[u] > n) {
            if (canReach[u]) return true;
            continue;
        }
        for (Data id : e[u]) {
            int v = id.v;
            double new_d = d[u] + (double)id.s - (double)id.t * mid;
            if (esp <= d[v] - new_d) {
                d[v] = new_d;
                q.push(v);
                if (d[n] <=esp) return true;
            }
        }
    }
    return d[n] <= esp;
}
bool fr[N];

bool bfs(int s, int t) {
    memset(fr, true, sizeof fr);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();q.pop();
        for (Data id: e[u]) {
            int v = id.v;
            if (v == t) return true;
            if (fr[v]) {
                fr[v] = false;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n>>m;
    Data z;
    FOR(i, 1, m) {
        cin>>z.u>>z.v>>z.s>>z.t;
        e[z.u].push_back(z);
    }
    FOR(i, 1, n) canReach[i] = bfs(i, n);

    if (!canReach[1]) {
        cout<<-1;
        return 0;
    }
    double l = 0;
    double r = 2;
    double cur = 0;
    while (r - l >= esp) {
        double m = (l + r) / 2;
        if (check(m)) {
            cur = m;
            r = m;
        } else l = m;
    }
    cout<<fixed<<setprecision(10)<<cur;
}
