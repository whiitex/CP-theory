// Created by Pasquale on 01/01/2024.

#include <bits/stdc++.h>
using namespace std;

template<typename T> struct RMQ {

// ------------------------ INTRODUCTION ----------------------- //
/* RMQ is the acronym of 'Range Minimum Query'. In this
 * class of problems the task is to answer q question about
 * the minimum (or maximum) value in a slice of an array
 * having n elements. The slice you are supposed to compute
 * is addressed by two values: l (left bound) and r (right bound).
 * Constraints are 0 < n,q <= 1e5.
 */

    T n;
    vector<T> array;

// ---------------------- 1st observation ---------------------- //
/* Obviously, thinking of computing minimum/maximum value for
 * each query would have a time complexity of O(nq) = O(1e10) and
 * a memory complexity of O(1); but it is too expensive in time.
 * At the same time, computing in advance (before queries) all
 * possible ranges, would require a time complexity of O(1) and
 * a memory complexity of O(nn) = O(1e10), so exceeding limits.
 */

// ---------------------- 2nd observation ---------------------- //
/* So an idea to solve this problem is to find way in between
 * time complexity and memory complexity, which is, in this case,
 * time O(q) and memory O(n logn).
 */

// -------------------------- MEMORY --------------------------- //
/* The idea is to build a matrix memo[n][logn] where for each
 * couple of index i,j 0<=i<n and 0<=j<=logn, the cell memo[i][j]
 * contains the minimum/maximum element in the range [i, i-1 + 2^j].
 * It can be built by initializing the first n elements memo[i][0] to
 * the element of the array (because they are already the min/max
 * element in the range consisting of only them. Then, it can be
 * finished using a dp approach.
 */

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


// --------------------- ANSWERING QUERIES --------------------- //
/* A query can be answered using a complexity O(1), so by quering
 * the memo matrix built before only two times. If we consider the
 * two bounds l and r given in input, we can get the solution from
 * the following two partial solution:
 * 1- from memo[l][exp], where the second index is the maximum
 *    exp such that the range [l, l-1 + 2^exp] is contained in [l,r]
 * 2- from memo[r+1 - 2^exp][exp], that is the second slice, which
 *    can or cannot overlap with the previous one; but this is not
 *    a problem, since min/max function doesnt change their
 *    outcome if an input is considered multiple times.
 * Finally, the complete solution is the min/max function of the
 * previously calculated partial solutions.
 */

    T solve(int l, int r) { // here l and r are 1 based indexing
        --l; --r;
        if (l == r) return array[l];

        int exp = (int) log2(r - l);

        int min1 = memo[l][exp];
        int min2 = memo[r + 1 - (int) pow(2, exp)][exp];
        return min(min1, min2);
    }

};
