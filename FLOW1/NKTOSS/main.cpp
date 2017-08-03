#include <bits/stdc++.h>

using namespace std;

struct BigNum {
    static const long long base = 1e18;
    static const long long nDigits = 18;
    long long digit[400];

    void print() {
        int t = 399;
        while (digit[t] == 0) t--;
        cout<<digit[t--];
        for (; t >= 0; t--) {
            int cs = log10(digit[t]) + 1;
            for (int z = 0; z < 18 - cs;z++) cout<<0;
            cout<<digit[t];
        }
    }
};

void operator += (BigNum &a, const BigNum &b) {
    for (int i = 0; i<400; i++) {
            a.digit[i] += b.digit[i];
            if (a.digit[i] >= a.base) {
                a.digit[i] -= a.base;
                a.digit[i + 1]++;
            }
        }
}
void operator -= (BigNum &a, const BigNum &b) {
    for (int i = 0; i<400; i++) {
            a.digit[i] -= b.digit[i];
            if (a.digit[i] < 0) {
                a.digit[i] += a.base;
                a.digit[i + 1]--;
            }
        }
}
#define N 10001
BigNum f[N], POW[N];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>n>>k;
    for (int i = 0; i<400; i++) f[0].digit[i] = 0;
    for (int i = 0; i<=k; i++) f[i] = f[0];
    f[k].digit[0] = 1;
    POW[0] = f[k];
    for (int i = 1; i<=n; i++) {
        POW[i] = POW[i - 1];
        POW[i] += POW[i - 1];
    }

    for (int i = k + 1; i<=n; i++) {
        f[i] = f[i - 1];
        f[i] += f[i - 1];
        f[i] += POW[i - k - 1];
        f[i] -= f[i - k - 1];
    }
    f[n].print();
}
