#include <bits/stdc++.h>
using namespace std;

template<typename T> struct RMQ {
    T n;
    vector<T> array;
    vector<vector<T>> memo;

    RMQ(vector<T>& input_array, T size) {
        array = input_array;
        n = size;
        int slots = ceil(log2(n));
        memo.resize(n, vector<T>(slots));

        // init
        for (int i = 0; i < n; ++i)
            memo[i][0] = array[i];

        // build
        for (int s = 1; s <= slots; ++s) {
            for (int i = 0; i < n; ++i) {

                int shift = (int) pow(2, s - 1);

                if (i + (int) pow(2, s - 1) >= n)
                    memo[i][s] = min(memo[i][s - 1], memo[n - shift][s - 1]);
                else
                    memo[i][s] = min(memo[i][s - 1], memo[i + shift][s - 1]);
            }
        }
    }

    T solve(int l, int r) { // l, r : 1-based indexing
        --l; --r;
        if (l == r) return array[l];

        int exp = (int) log2(r - l);

        int min1 = memo[l][exp];
        int min2 = memo[r + 1 - (int) pow(2, exp)][exp];
        return min(min1, min2);
    }

};