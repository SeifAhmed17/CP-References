ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;
}
ull powmod(ull a, ull b, ull m) {
    ull res = 1; a %= m;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
    }
    return res;
}
bool millerRabin(ull n, ull a) {
    if (n % a == 0) return n == a;
    ull d = n - 1; int r = 0;
    while (d % 2 == 0) d /= 2, r++;
    ull x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}
bool isPrime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ull a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL})
        if (!millerRabin(n, a)) return false;
    return true;
}