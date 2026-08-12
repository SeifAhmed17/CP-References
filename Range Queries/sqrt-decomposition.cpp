/*
 * SQRT DECOMPOSITION — O(sqrt(n)) per query/update, dead simple to bend
 * ---------------------------------------------------------------------
 * Split the array into blocks of size SQ ~ sqrt(n); keep an aggregate per block.
 * Query [l, r]: whole blocks inside use the aggregate, the two ragged ends brute force.
 *
 * WHEN over a segtree (which is O(log n) and usually better for plain sum/min):
 *   - the block aggregate is something a segtree can't merge easily:
 *     SORTED block (-> "count elements > x in range" via binary search per block),
 *     frequency map per block, "best pair inside block", etc.
 *   - lazy-style tricks: tag whole blocks, rebuild only ragged blocks (rebuild = O(SQ)).
 *   - you're out of time to debug a segtree — this is 15 lines and hard to get wrong.
 *
 * As written: point ASSIGN + range SUM, 0-indexed inclusive.
 * CHANGE HERE: what b[] stores + how update/query maintain it (see WHEN above).
 */
int SQ;
vector<ll> a, b;                       // b[k] = aggregate (sum) of block k

void build(int n) {                    // call after filling a; O(n)
    SQ = (int)sqrtl(n) + 1;
    b.assign(n / SQ + 1, 0);
    for (int i=0; i<n; i++) b[i / SQ] += a[i];
}

void update(int i, ll x) {             // a[i] = x
    b[i / SQ] += x - a[i];             // fix the aggregate, not rebuild
    a[i] = x;
}

ll query(int l, int r) {               // sum of a[l..r]
    ll sum = 0;
    for (int i=l; i<=r; ) {
        if (i % SQ == 0 && i + SQ - 1 <= r) {   // block fully inside -> take aggregate
            sum += b[i / SQ];
            i += SQ;
        }
        else sum += a[i++];                     // ragged edge -> element by element
    }
    return sum;
}
