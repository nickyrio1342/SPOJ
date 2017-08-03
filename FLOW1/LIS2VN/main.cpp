#include <bits/stdc++.h>

using namespace std;

#define pp pair<int, int>
#define N 100001
#define x first
#define y second

set<pp> s[N];
set<pp> ::iterator it, it2;
int n, ans;
const int inf = 1e9 + 7;

void insert(const pp &t, int pos) {
    it = s[pos].lower_bound(t);
    if (it != s[pos].begin()) {
        it2 = it;
        it2--;
        if (it2 -> x == t.x && it2 -> y <= t.y) return;
    }
    for (; it != s[pos].end() && it -> y >= t.y;) s[pos].erase(it++);
    s[pos].insert(t);
}

bool check(const pp &t, int m) {
    it = s[m].lower_bound(pp(t.x, -inf));
    if (it == s[m].begin()) return false;
    it--;
    if (it -> y < t.y) return true;
    return false;
}

void solve(const pp &t) {
    int l = 0; int r = ans;
    int cur = -1;
    while (l <= r) {
        int m = (l + r)>> 1;
        if (check(t, m)) {
            cur = m;
            l = m + 1;
        } else r = m - 1;
    }
    ans = max(ans, cur + 1);
    insert(t, cur + 1);
}
int main() {
    freopen("E:\\input.txt","r",stdin);
    freopen("E:\\output.txt","w",stdout);
    cin.tie(NULL);cout.tie(NULL);
    scanf("%d", &n);
    pp t;
    insert(pp(-inf, -inf), 0);
    ans = 0;
    for (int i = 0; i<n; i++) {
        scanf("%d%d", &t.x, &t.y);
        solve(t);
    }
    cout<<ans;
}
