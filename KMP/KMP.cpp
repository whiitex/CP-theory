#include <bits/stdc++.h>
using namespace std;

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