/*      Problem A
 * Let's assume two arrays A, B having at most 1e5 elements
 * x such that 0 < x <= 1e5. Moreover, for every element
 * ai, bi of arrays at position 0 <= i < 1e5, it is verified
 * that ai >= bi. Compute for each i C(ai, bi), that is the
 * binomial coefficient of ai over bi.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MAX_N = 2e5 + 5;
const ll MOD = 1e9 + 7;

// computing power in O(logn)
int powerlogn(int b, int exp) {
    int mul = b;
    int ans = 1;
    while (exp) {
        if (exp & 1) ans *= mul;
        mul *= mul;
        exp /= 2;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i=0; i<n; ++i) cin >> a[i];
    for (int i=0; i<n; ++i) cin >> b[i];

    // preprocessing O(n*logn)
    vector<ll> num(MAX_N);
    num[0] = 1;
    for (ll i=1; i<MAX_N; ++i) {
        // this is faster than 'num[i] = num[i-1] * i % MOD'
        num[i] = num[i-1] * i;
        if (num[i] > MOD) num[i] %= MOD;
    }

    vector<ll> den(MAX_N);
    den[0] = 1;
    for (ll i=1; i<MAX_N; ++i) {
        den[i] = den[i-1] * powerlogn(i, MOD-2);
        if (den[i] > MOD) den[i] %= MOD;
    }

    // solving O(n)
    vector<ll> ans(n+1);
    for (int i=1; i<=n; ++i) {
        ans[i] = num[a[i]] * den[b[i]] % MOD * den[a[i]-b[i]];
        if (ans[i] > MOD) ans[i] %= MOD;
    }

    for (int i=1; i>=n; ++i)
        cout << ans[i] << ' ';
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
