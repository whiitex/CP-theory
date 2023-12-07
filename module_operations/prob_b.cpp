/*      Problem B
 * In input a big number x is given, such that 0 <= x <= 10^(10^5).
 * In one operation it is possible to erase any substring
 * of consecutive numbers from the array. We want to calculate the sum
 * of the remaing number obtained after every combination of the
 * operation above. Print the result module 1e9+7.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MAX_N = 2e5 + 5;
const ll MOD = 1e9 + 7;

void solve() {
    string s; cin >> s;
    ll n = (ll)s.length();
    vector<ll> vec(n);
    for (ll i=0; i<n; ++i)
        vec[i] = s[i] - '0';

    ll rx = 0, ans = 0, tenexp = 1;
    for (ll i=n-1; i>=0; --i) {
        ans = ans + ( ( (i * (i+1) >> 1) % MOD * tenexp) % MOD * vec[i] ) % MOD; // sx
        ans = ans + (vec[i] * rx ) % MOD; // rx

        // update dp vars
        rx = (rx + tenexp * (n-i) );
        if (rx > MOD) rx %= MOD; // faster
        tenexp = tenexp * 10;
        if (tenexp > MOD) tenexp %= MOD; // faster
    }

    cout << ans % MOD;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll t=1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
