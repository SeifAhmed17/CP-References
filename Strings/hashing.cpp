/*
 * STRING HASHING (polynomial, DOUBLE hash) — substring compare in O(1)
 * --------------------------------------------------------------------
 * hash(s[0..i]) = s[0]*b^i + s[1]*b^(i-1) + ... + s[i]   (mod m), for TWO
 * independent (base, mod) pairs -> collision chance ~ 1/1e18, safe to treat
 * "hashes equal" as "strings equal".
 *
 * USAGE:
 *   init();                      // ONCE globally (fills power tables, needs N >= max length)
 *   Hash h(s);                   // O(|s|)
 *   h.get(l, r);                 // pair hash of s[l..r], 0-INDEXED INCLUSIVE, O(1)
 *   Hash h2(t); h.get(..) == h2.get(..)   // cross-string compare works (same bases)
 *
 * RECALL — how get() works: h1[r] holds hash of prefix 0..r; subtract prefix
 * 0..l-1 SHIFTED UP by b^(r-l+1) to align, i.e. hash(l..r) = h[r] - h[l-1]*b^len.
 *
 * NOTES / PITFALLS:
 *   - chars are mapped to (value + 1) so no character is 0 — otherwise "a" and "aa"
 *     would collide (leading zeros vanish).
 *   - b1, b2 must be > alphabet size. For mixed case/digits use e.g. 131, 137.
 *   - vs anti-hash hacks (Codeforces open hacking): randomize the bases at runtime,
 *     e.g. b1 = rand(256, mod1-2) using Other/random.cpp.
 *     For ECPC onsite nobody hacks you — fixed bases are fine.
 *
 * CLASSIC USES:
 *   - compare any two substrings / check palindrome (hash the reversed string too)
 *   - longest common prefix of two suffixes via binary search + get()
 *   - count distinct substrings of each length, string matching without KMP
 */
const int b1 = 41, b2 = 37, mod1 = 1e9+7, mod2 = 1e9+9;
int pw1[N], pw2[N];                     // pw[i] = b^i (precomputed powers)

void init() {
    pw1[0] = pw2[0] = 1;
    for (int i=1; i<N; i++) {
        pw1[i] = 1LL * pw1[i-1] * b1 % mod1;
        pw2[i] = 1LL * pw2[i-1] * b2 % mod2;
    }
}

class Hash
{
    int n;
    vector<int> h1, h2;                 // prefix hashes

public:
    Hash(const string& s): n(s.size()), h1(n), h2(n) {
        h1[0] = h2[0] = (unsigned char)s[0] + 1;          // +1: never map a char to 0!
        for (int i=1; i<n; i++) {
            int d = (unsigned char)s[i] + 1;
            h1[i] = (1LL*h1[i-1]*b1%mod1 + d)%mod1;
            h2[i] = (1LL*h2[i-1]*b2%mod2 + d)%mod2;
        }
    }

    pair<int,int> get(int l, int r) {   // hash of s[l..r], 0-indexed inclusive
        int x = (h1[r] - (1LL*(l?h1[l-1]:0)*pw1[r-l+1]%mod1) + mod1) % mod1;
        int y = (h2[r] - (1LL*(l?h2[l-1]:0)*pw2[r-l+1]%mod2) + mod2) % mod2;
        return {x, y};
    }
};
