/*
 * SIEVE OF ERATOSTHENES — O(N log log N)
 * --------------------------------------
 * prime[i] = is i prime;  primes = list of all primes < N.
 * Call Sieve() once at startup.
 *
 * NOTES:
 *   - Inner loop starts at i*i: smaller multiples were already crossed by smaller primes.
 *     i is ll precisely so i*i can't overflow int when N is large (N > ~46341).
 *   - WARNING: the outer loop stops at i*i < N, so `primes` only receives primes
 *     up to sqrt(N)! prime[] itself IS correct for all i < N. If you need the full
 *     primes list, collect it afterwards:
 *         for (int i=2; i<N; i++) if (prime[i]) primes.pb(i);
 *     (or use linear-sieve.cpp, which collects all of them by construction)
 *   - Rough counts: #primes below 1e6 ~ 78498, below 1e7 ~ 620k, below 1e8 ~ 5.7M.
 *
 * VARIANT — smallest prime factor / O(log) factorization: see linear-sieve.cpp.
 * VARIANT — count divisors / sum of divisors for all i: loop j += i from i (not i*i)
 *   and do cnt[j]++ — that harmonic double loop is O(N log N).
 */
bool prime[N];
vector<int> primes;

void Sieve()
{
    fill(prime,prime+N,true);
    prime[0] = prime[1] = false;

    for (ll i=2; i*i<N; i++) {       // ll so i*i can't overflow
        if (prime[i]) {
            primes.pb(i);            // WARNING: only primes up to sqrt(N)! see header
            for (ll j=i*i; j<N; j+=i) {
                prime[j] = false;
            }
        }
    }
}
