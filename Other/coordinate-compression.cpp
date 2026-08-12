/*
 * COORDINATE COMPRESSION — map big values to 0..k-1, order preserved. O(n log n)
 * ------------------------------------------------------------------------------
 * WHEN: values up to 1e9/1e18 but only n of them, and you need them as ARRAY
 * INDICES (Fenwick, segtree, cnt[] in Mo's, ...). Comparisons still work because
 * the mapping is monotonic: a[i] < a[j] before <=> after.
 *
 * SNIPPET (inside solve). After it:
 *   a[i]    = compressed rank in [0, k)   where k = sz(d)
 *   d[a[i]] = the ORIGINAL value (keep d around to answer/output real values!)
 *   rank of arbitrary x: lower_bound(all(d), x) - d.begin()
 *
 * NOTE: compressing MULTIPLE arrays together (queries + array values)?
 * Concatenate everything into d before sort+unique, then rank each against d.
 */
vector<int> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());   // sorted distinct values
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();  // value -> its rank
    }
