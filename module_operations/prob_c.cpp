/*      Problem C
 * In this problem there are n lamps that turn on at time li
 * and they turn off at ri. We want to compute how many
 * possible composition of lamp are able to make possible to
 * have exactly k lamp on at a certain time.
 * problem: https://codeforces.com/problemset/problem/1420/D
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

const int MAX_N = 3e5 + 5;
const ll MOD = 998244353;

ll powlogn(ll b, ll exp) {
    ll mul = b;
    ll res = 1;
    while (exp) {
        if (exp & 1) res *= mul;
        if (res > MOD) res %= MOD;
        mul = (mul * mul) % MOD;
        exp /= 2;
    }
    return res;
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<pair<int,int>> vec(n);
    for (int i=0; i<n; ++i) {
        cin >> vec[i].first;
        cin >> vec[i].second;
        vec[i].second++;
    }
    std::sort(vec.begin(), vec.end());

    // coordinate compression
    set<int> comp;
    for(auto p: vec) {
        comp.insert(p.first);
        comp.insert(p.second);
    }
    map<int, int> mcomp;
    int ind=1;
    for (auto val: comp) {
        mcomp.insert({val, ind});
        ++ind;
    }
    for (int i=0; i<n; ++i) {
        vec[i].first = mcomp[vec[i].first];
        vec[i].second = mcomp[vec[i].second];
    }

    // suffix and prefix
    int slot = (int)comp.size();

    vector<int> vstart(slot+1,0), vend(slot+1,0);
    for (auto p: vec) {
        vstart[p.first]++;
        vend[p.second]++;
    }

    vector<int> start(slot,0), end(slot,0);
    start[0] = vstart[0];
    end[0] = vend[0];

    for (int i=1; i<slot; ++i) {
        start[i] = start[i-1] + vstart[i];
        end[i] = end[i-1] + vend[i];
    }

    // 1/k! (MOD)
    ll div = 1;
    int kk = k;
    while (kk) div = (div * kk--) % MOD;
    div = powlogn(div, MOD-2) % MOD;

    // preprocessing
    vector<ll> num(MAX_N);
    vector<ll> den(MAX_N);
    num[0] = 1, den[0] = 1;
    for (ll i=1; i<MAX_N; ++i) {
        num[i] = num[i-1] * i;
        if (num[i] > MOD) num[i] %= MOD;
        den[i] = den[i-1] * powlogn(i, MOD-2);
        if (den[i] > MOD) den[i] %= MOD;
    }

    // solving
    ll res = 0;
    for (int i=1; i<slot; ++i) {

        int delta = start[i] - start[i-1];
        int tot = start[i] - end[i];
        if (tot-delta >= k) {
            res += ((num[tot] * den[tot-k]) % MOD * div) % MOD;
            res -= ((num[tot-delta] * den[tot-delta-k]) % MOD * div) % MOD;
            res = (res + MOD) % MOD;
        }
        else if (tot >= k) {
            res += ((num[tot] * den[tot-k]) % MOD * div) % MOD;
            if (res > MOD) res %= MOD;
        }

    }

    cout << res % MOD;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t=1;
//    cin >> t;
    while (t--) {
        solve();
    }
}



/*  NAIVE
 *  sort(vec.begin(), vec.end());

    ll res = 0;
    for (int i=0; i<n-k+1; ++i) {
        int limit = vec[i].second;

        int l=i+1, r=(int)n-1;
        while (l<r) {
            int mid = l+r+1 >> 1;
            if (vec[mid].first >= limit)
                r = mid-1;
            else l = mid;
        }

        if (l-i+1 >= k) res += triangle(l-i+1, k);
    }
    cout << res;
*/

/*
10 3
1 4
1 4
1 4
1 4
2 6
2 6
2 6
2 6
2 6
5 10
*/