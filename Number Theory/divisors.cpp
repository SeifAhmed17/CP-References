/*
 * NUMBER OF DIVISORS d(n) + SUM OF DIVISORS sigma(n) — trial division, O(sqrt n)
 * ------------------------------------------------------------------------------
 * RECALL — both come straight from the prime factorization n = p1^e1 * p2^e2 * ...
 *   d(n)     = (e1+1) * (e2+1) * ...          (pick each prime's exponent independently)
 *   sigma(n) = prod over p of (1 + p + p^2 + ... + p^e)   (geometric sum per prime)
 *
 * FACTS WORTH REMEMBERING:
 *   - d(n) is ODD  <=>  n is a PERFECT SQUARE (divisors pair up except sqrt(n)).
 *   - d(n) is small: max 1344 for n <= 1e9, max 103680 for n <= 1e18
 *     -> "loop over all divisors" is usually fine after factorizing.
 *   - many queries with n < N? factorize with spf from linear-sieve.cpp in O(log n)
 *     and apply the same formulas.
 *   - sigma(n) can be ~6x n — near ll's limit for n ~ 1e18, careful.
 *   - perfect number: sigma(n) = 2n.
 */
long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;                    // exponent e contributes (e+1) choices
        }
    }
    if (num > 1) total *= 2;                   // leftover prime > sqrt: exponent 1
    return total;
}

long long SumOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;        // 1 + p + ... + p^e
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) total *= (1 + num);           // leftover prime p: (1 + p)
    return total;
}
