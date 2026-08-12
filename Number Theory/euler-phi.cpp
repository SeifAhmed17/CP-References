/*
 * EULER'S TOTIENT phi(n) — # of 1..n coprime with n
 * -------------------------------------------------
 * Formula: phi(n) = n * prod over prime p|n of (1 - 1/p)
 *   -> implemented as res -= res/p per distinct prime (order doesn't matter).
 * phi(single n): O(sqrt n).  phi for ALL 1..N: sieve version, O(N log log N).
 *
 * THE FACTS YOU ACTUALLY USE:
 *   - EULER'S THEOREM: a^phi(m) ≡ 1 (mod m)   when gcd(a, m) = 1.
 *     (generalizes Fermat: phi(prime) = prime-1)
 *   - HUGE EXPONENT REDUCTION (power towers, exponent given as giant number):
 *       a^b ≡ a^( b mod phi(m) + phi(m) )   (mod m)    valid for b >= log2(m),
 *     and this one works EVEN IF gcd(a, m) != 1 (the +phi(m) is what makes it safe —
 *     don't drop it unless you know gcd = 1!).
 *   - phi is multiplicative: phi(a*b) = phi(a)*phi(b) when gcd(a,b) = 1.
 *   - sum of phi(d) over all divisors d of n  =  n.
 *   - # of fractions k/n in lowest terms, cycle structures, "count coprime pairs".
 */
ll phi(ll n) {                       // O(sqrt n), single value
    ll res = n;
    for (ll p=2; p*p<=n; p++) if (n % p == 0) {
        while (n % p == 0) n /= p;
        res -= res / p;              // res *= (1 - 1/p)
    }
    if (n > 1) res -= res / n;       // leftover prime factor > sqrt
    return res;
}

int phiAll[N];                       // phi for every 1..N-1 (sieve style)
void phiSieve() {
    iota(phiAll, phiAll+N, 0);
    for (int i=2; i<N; i++)
        if (phiAll[i] == i)          // untouched -> i is prime
            for (int j=i; j<N; j+=i)
                phiAll[j] -= phiAll[j] / i;
}
