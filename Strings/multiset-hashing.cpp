/*
 * MULTISET HASHING — order-INDEPENDENT hashing (compare multisets in O(1))
 * ------------------------------------------------------------------------
 * Question it answers: "do these two collections contain exactly the same
 * elements with the same multiplicities?" — regardless of order.
 * (e.g. is substring A an ANAGRAM of substring B; are two subtrees equal as bags)
 *
 * IDEA: give every DISTINCT VALUE a random 5-dimensional vector (Hash()).
 * The hash of a multiset = plain SUM of the vectors of its elements.
 *   add element v    -> cur = cur + H[v]
 *   remove element v -> cur = cur - H[v]
 * Sum is commutative -> order can't matter. Forging a collision needs to hit
 * 5 independent random ~1e9 coordinates -> probability ~ 0.
 *
 * USAGE:
 *   map<int, Hash> H;  auto getH = [&](int v){ if (!H.count(v)) H[v] = Hash(); return H[v]; };
 *   Hash cur(0,0,0,0,0);               // empty multiset  (explicit zeros — Hash() is RANDOM!)
 *   cur = cur + getH(v);               // v enters
 *   cur = cur - getH(v);               // v leaves
 *   sliding window / two windows -> compare with ==
 *
 * NOTES:
 *   - No mod anywhere: coords stay < ~2e14 for 2e5 elements, fits ll fine.
 *   - PITFALL: default constructor Hash() generates a NEW RANDOM vector — that's the
 *     per-value generator. The "zero" hash must be built as Hash(0,0,0,0,0).
 *   - Works inside prefix sums too: pre[i] = pre[i-1] + H[a[i]] -> hash of any
 *     subarray = pre[r] - pre[l-1] -> "are these two ranges permutations of each other" in O(1).
 */
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> T rand(T l, T r) { return uniform_int_distribution<T>(l, r)(rng); }

struct Hash {
    ll a, b, c, d, e;
    Hash(ll _a, ll _b, ll _c, ll _d, ll _e):a(_a),b(_b),c(_c),d(_d),e(_e){}
    Hash() {                    // RANDOM vector — use once per distinct value
        a = rand(1, (int)1e9);
        b = rand(1, (int)1e9);
        c = rand(1, (int)1e9);
        d = rand(1, (int)1e9);
        e = rand(1, (int)1e9);
    }
    Hash operator+(const Hash& other) const {
        return Hash(a+other.a,b+other.b,c+other.c,d+other.d,e+other.e);
    }
    Hash operator-(const Hash& other) const {
        return Hash(a-other.a,b-other.b,c-other.c,d-other.d,e-other.e);
    }
    bool operator==(const Hash& other) const {
        return a==other.a&&b==other.b&&c==other.c&&d==other.d&&e==other.e;
    }
};
