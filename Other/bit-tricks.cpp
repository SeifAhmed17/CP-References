/*
 * BIT TRICKS — counting set bits in ranges + XOR prefix, O(1) each
 * ----------------------------------------------------------------
 * (the one-line bit identities live in NOTES.md; this file is the actual code)
 *
 * countSetBits(l, r, bit): how many numbers in [l, r] have `bit` set.
 * RECALL — bit b cycles with period 2^(b+1): first half off, second half on.
 * Count in [0, x] = full periods * half + the partial period's overlap; subtract prefixes.
 * Total set bits in a range: loop this over all 60 bits (still ~O(60)).
 * Typical use: sum/xor contributions bit by bit ("count pairs whose AND has bit b", ...).
 *
 * xorUpTo(n) = 1 ^ 2 ^ ... ^ n. RECALL — it's periodic with period 4:
 *   n % 4 == 0 -> n,  == 1 -> 1,  == 2 -> n+1,  == 3 -> 0
 * XOR of any range [l, r] = xorUpTo(r) ^ xorUpTo(l-1)  (prefix trick, xor is its own inverse).
 */
ll onesUpTo(ll x, int bit) {           // # of v in [0, x] with `bit` set
    if (x < 0) return 0;
    ll len = 1LL << (bit + 1), half = 1LL << bit;
    return (x / len) * half + max(0LL, x % len - half + 1);
}

ll countSetBits(ll l, ll r, int bit) { // # of v in [l, r] with `bit` set
    return onesUpTo(r, bit) - onesUpTo(l - 1, bit);
}

ll xorUpTo(ll n) {                     // 1 ^ 2 ^ ... ^ n   (n >= 0)
    switch (n % 4) {
        case 0:  return n;
        case 1:  return 1;
        case 2:  return n + 1;
        default: return 0;
    }
}
