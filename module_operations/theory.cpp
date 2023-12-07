// Created by Pasquale on 06/12/2023.

#include <bits/stdc++.h>

const int MOD = 1e9 + 7;

using namespace std;

// computing power in O(logn)
int powerlogn(int b, int exp) {
    int mul = b;
    int ans = 1;
    while (exp) {
        if (exp & 1) ans *= mul;
        mul *= mul;
        exp /= 2;
    }
}

// ------------------------ADDITION------------------------ //
/* Addition module a large number is trivial, because:
 *      a + b (mod m) = (a (mod m) + b (mod m)) (mod m)
 */
int modadd(int a, int b, int mod) {
    return ((a % mod) + (b % mod)) % mod;
}


// ---------------------MULTIPLICATION--------------------- //
/* Multiplication is trivial too, because:
 *      a * b (mod m) = (a (mod m) * b (mod m)) (mod m)
 */
int modmul(int a, int b, int mod) {
    return ((a % mod) * (b % mod)) % mod;
}


// -----------------------SUBTRACTION---------------------- //
/* Subtraction may be a little tricky, since it is not true
 * that the module of a subtraction is equal to subtraction
 * of modules: a negative result may come out.
 *      a - b (mod m) = (a (mod m) - b(mod m)) (mod m)
 * Mathematically talking:
 *      -a ≡ m-a (mod m)
 */
int modsub(int a, int b, int mod) {
    int ans = (a - b) % mod;
    if (ans < 0) ans += mod;
    return ans;
}


// ------------------------DIVISION------------------------ //
/* In order to compute
 *      x = a/b (mod m)
 * splitting the operation in the following way is possible:
 *      x = a (mod m) * 1/b (mod m)
 * This is a tricky task to achieve, since it apparently
 * makes no sense to compute the reminder of a dividend.
 * But, according to Fermat's Little Theorem:
 *      a^p ≡ a (mod p) -> a^p-1 ≡ 1 (mod p), p prime
 * Hence:   a^p-2 ≡ 1/a (mod p)
 * So, the initial computation becomes as below:
 *      x = a (mod p) * b^p-2
 */
int modfract(int a, int b, int mod) {
    return a * (powerlogn(b, mod-2) % mod) % mod;
}

/* It is possible also to generalize the constraint to p.
 * In particular, if m is any number > 2, considering the
 * phi φ function that returns the amount of co-prime
 * numbers, it is:
 *      a^φ(m) ≡ 1 (mod m) -> a^(φ(m)-1) ≡ 1/a (mod m)
 *  But, for CP purpose, since the mainly used module is
 *  1e9 + 7, that is a prime number, this problem is limited.
 */