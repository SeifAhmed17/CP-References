/*
 * MILLER-RABIN — deterministic primality test for ALL 64-bit numbers
 * ------------------------------------------------------------------
 * isPrime(n) for n up to ~1.8e19 (unsigned 64-bit), O(12 * log n) mulmods.
 * Use when n is way too big for a sieve (e.g. "is 1e18 + 9 prime?").
 *
 * RECALL — the test with base a:
 *   write n-1 = d * 2^r (d odd). n passes base a if
 *   a^d == 1 (mod n)  or  a^(d*2^i) == n-1 for some 0 <= i < r.
 *   Every prime passes every base; composites fail at least 3/4 of bases.
 *   With the FIXED base set {2,3,5,7,...,37} (first 12 primes) the test is
 *   PROVEN exact for all n < 3.3e24 -> covers the whole 64-bit range.
 *   (The old shorter set {2..13} is only safe below 3.47e12 — a real WA trap!)
 *
 * NOTES:
 *   - mulmod uses __uint128_t -> GCC/Clang only (fine on Codeforces/ECPC judges).
 *   - millerRabin(n, a) with n % a == 0 answers directly (handles small n / n == a).
 *   - Everything is unsigned long long (ull) — keep it that way, n-1 underflows otherwise...
 *     it doesn't since n >= 2, but signed overflow in mulmod WOULD break, hence ull.
 *
 * RELATED (not included): Pollard's rho for FACTORING 64-bit numbers — ask if needed.
 */
ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;      // 128-bit intermediate, no overflow
}
ull powmod(ull a, ull b, ull m) {
    ull res = 1; a %= m;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
    }
    return res;
}
bool millerRabin(ull n, ull a) {        // does n pass witness a?
    if (n % a == 0) return n == a;      // shares a factor with a -> prime only if n == a
    ull d = n - 1; int r = 0;
    while (d % 2 == 0) d /= 2, r++;     // n-1 = d * 2^r
    ull x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {   // keep squaring, look for n-1
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;                       // composite for sure
}
bool isPrime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // first 12 primes -> deterministic for ALL n < 2^64
    for (ull a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (!millerRabin(n, a)) return false;
    return true;
}
