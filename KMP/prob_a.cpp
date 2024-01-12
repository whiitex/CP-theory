/*      Problem A
 * In this problem, given a string s having at most length 1e6,
 * we want to find the longest substring t, made of the
 * concatenation of two (possibly empty) substrings a, b:
 * prefix a suffix of string s. The final length of t cannot
 * be greater than the length ofstring s and a, b.
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
const int MOD = 998244353;

string KMP(string& s) {
    vector<int> pref;
    int n = (int) s.length();
    pref.resize(n);

    int mlen = 0;
    for (int i = 1; i < n; ++i) {
        while (mlen > 0 and s[mlen] != s[i])
            mlen = pref[mlen - 1];

        if (s[mlen] == s[i]) ++mlen;
        pref[i] = mlen;
    }
    return s.substr(0, pref[n - 1]);
}

void solve() {
    string s; cin >> s;
    int n = (int)s.length();

    if (n == 1) {
        cout << s[0] << '\n';
        return;
    }

    // starting equality to take the left most and
    // the right most equal elements of the string
    string dupStart = "";
    int k = 0;
    while (s[k] == s[n-1-k] and k<n/2) ++k;
    dupStart = s.substr(0,k);
    string dupEnd = dupStart;
    std::reverse(dupEnd.begin(), dupEnd.end());

    // inner sub-string -> KMP algorithm
    s = s.substr(k, n-2*k);
    string sreverse = s;
    std::reverse(sreverse.begin(), sreverse.end());

    string sl = s + '_' + sreverse;
    string middleL = KMP(sl);

    string sr = sreverse + '_' + s;
    string middleR = KMP(sr);

    string middle;
    if (middleL.length() > middleR.length())
        middle = middleL;
    else middle = middleR;

    cout << dupStart << middle << dupEnd << '\n';
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


/* TLE
void solve() {
    string s; cin >> s;
    int n = s.length();

    if (n == 1) {
        cout << s[0] << '\n';
        return;
    }

    // initial equality
    string dupStart = "";
    int k = 0;
    while (s[k] == s[n-1-k] and k<n/2) ++k;
    dupStart = s.substr(0,k);
    string dupEnd = dupStart;
    std::reverse(dupEnd.begin(), dupEnd.end());

    // biggest inner palindrome
    string middleL;
    for (int r=n-k-1; r>=k; --r) {
        bool found = true;
        for (int i=0; i<(r-k+1)/2; ++i) {
            if (s[k+i] != s[r-i]) {
                found = false;
                break;
            }
        }
        if (found) {
            middleL = s.substr(k, r-k+1);
            break;
        }
    }

    string middleR;
    for (int l=k; l<n-k; ++l) {
        bool found = true;
        for (int i=0; i<(n-l-k)/2; ++i) {
            if (s[l+i] != s[n-k-1-i]) {
                found = false;
                break;
            }
        }
        if (found) {
            middleR = s.substr(l, n-l-k);
            break;
        }
    }

    string middle;
    if (middleL.length() > middleR.length())
        middle = middleL;
    else middle = middleR;

    cout << dupStart  + middle + dupEnd << '\n';
}
 */