/*
 * LINEAR SIEVE — O(N), gives SMALLEST PRIME FACTOR of every number
 * ----------------------------------------------------------------
 * spf[i]  = smallest prime factor of i  (spf[i] == i  <=>  i is prime)
 * primes  = ALL primes < N (complete list, unlike plain sieve variant).
 *
 * WHY LINEAR: each composite x is crossed out EXACTLY ONCE, by (its smallest
 * prime p) * (x/p) — that's what the `primes[j] <= spf[i]` cutoff guarantees.
 *
 * THE KILLER FEATURE — factorize any x < N in O(log x):
 *   while (x > 1) {
 *       int p = spf[x], cnt = 0;
 *       while (x % p == 0) x /= p, cnt++;
 *       // (p, cnt) is one prime-power of x
 *   }
 *   -> lets you factorize MANY numbers fast (vs trial division O(sqrt x) each).
 *
 * ALSO GOOD FOR multiplicative functions (phi, mobius, #divisors) computed for
 * ALL i < N inside this same loop — ask for the extended version if needed.
 */
int spf[N];
vector<int> primes;

void LinearSieve() {
    for (int i=2; i<N; i++) {
        if (!spf[i]) {              // nothing crossed i yet -> prime
            spf[i] = i;
            primes.pb(i);
        }

        // cross i * p for primes p <= spf[i]; p becomes the smallest factor of i*p
        for (int j=0; j<sz(primes) && i * primes[j]<N && primes[j] <= spf[i]; j++) {
            spf[i*primes[j]] = primes[j];
        }
    }
}
