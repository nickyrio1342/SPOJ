#include <bits/stdc++.h>

using namespace std;
#define N 1050
int BIT[N][N], now[N][N];

class FenwickTree2D {
private:
    int n;
public:
    void clear(int nn) {
        n = nn;
        for (int i = 0; i<=n; i++) {
            for (int j = 0; j<=n; j++) BIT[i][j] = now[i][j] = 0;
        }
    }
    void update(int u, int v, int val) {
        for(; u <= n; u += u&-u) {
            for(int vv = v; vv<= n; vv += vv&-vv)
                BIT[u][vv] += val;
        }
    }

    int get(int u, int v) {
        int ans = 0;
        for (; u > 0; u -= u&-u) {
            for(int vv = v; vv > 0; vv -= vv&-vv) ans += BIT[u][vv];
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;
    cin>>test;
    int n, x, y, val, xx, yy;
    string s;
    FenwickTree2D FT;
    while (test--) {
        cin>>n;
        FT.clear(n + 1);
        while (true) {
            cin>>s;
            if (s == "END") break;
            if (s == "SET") {
                cin>>x>>y>>val;
                FT.update(x + 1, y + 1, val - now[x][y]);
                now[x][y] = val;
                continue;
            }
            if (s != "SUM") continue;
            cin>>x>>y>>xx>>yy;
            int ans = FT.get(xx + 1, yy + 1) - FT.get(xx + 1, y) - FT.get(x, yy + 1) + FT.get(x, y);
            cout<<ans<<'\n';
        }
        cout<<'\n';

    }
}
