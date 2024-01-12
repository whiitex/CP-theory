// Created by Pasquale on 12/01/2024.

#include <bits/stdc++.h>
using namespace std;

string KMP_raw (string s) {

// ------------------------ INTRODUCTION ----------------------- //
/* The purpose of this algorithm, proposed by three people, so
 * Knuth, Pratt and independently by Morris in 1977, aim to find
 * the solution to the prefix function. Given a string s, we want
 * to build an array pref where, at each position i, pref[i]
 * contains the longest prefix that is also a suffix of s.
 *
 *  e.g. s = "aabaaab", pref = {0,1,2,0,1,2,2,3}
 *  e.g. s = "bassba", pref = {0,0,0,0,1,2}
 */

    int n = (int) s.length();
    vector<int> pref(n);


// ----------------------- IMPLEMENTATION ---------------------- //
/* So, let's analyze how the prefix array is built and, at the same
 * time, let's try to optimize it. At least, we need to iterate through
 * the string, starting form position 1 (because, by definition,
 * pref[0] = 0). Moreover, if you maintain a counter for the current
 * longest prefix/suffix (of the previous iteration), you know for sure
 * that, if s[count+1] = s[i], then pref[i] = count+1 or, more
 * formally, if s[pref[i-1]] = s[i], then pref[i] = pref[i-1]+1. It means
 * that the next element of the previously computed prefix is equal of
 * the last element of the array, that is also the next element of
 * the longest suffix previously computed. Here the string is
 * 0-based indexed.
 */

    pref[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[pref[i - 1]] == s[i])
            pref[i] = pref[i - 1] + 1;

// ---------------------- NON EQUALITY CASE -------------------- //
/* When the following element differ, we also have to update the
 * counter of the longest current array. At this point, the next
 * longest substring will be the one having the element at position
 * at most pref[count-1].
 *  e.g.           count                 i-1   i
 *      s0, s1, s2, s3, s4 ... s-4, s-3, s-2, s-1
 *      s-1 != s4 (s4 = s[pref[count]]
 *  so update max counter to s3: s[pref[count-1]] and compare
 */

        else {
            int count = pref[i - 1];
            while (count > 0 and s[count] != s[i])
                count = pref[count - 1];

            // increase if they are the same
            if (s[count] == s[i]) ++count;
            pref[i] = count;
        }
    }

    // take the longest substring considering the
    // whole string for the suffix substring
    return s.substr(0, pref[n - 1]);
}

// -------------------- OPTIMIZED ALGORITHM -------------------- //
/* Here a less readable, but more efficient implementation of the
 * same algorithm proposed above.
 */

string KMP (string s) {

    int n = (int) s.length();
    vector<int> pref(n);

    int count = 0;
    for (int i = 1; i < n; ++i) {

        while (count > 0 and s[count] != s[i])
            count = pref[count - 1];

        if (s[count] == s[i]) ++count;
        pref[i] = count;
    }

    return s.substr(0, pref[n - 1]);
}
