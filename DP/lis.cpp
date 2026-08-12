/*
 * LIS — Longest Increasing Subsequence, O(n log n), with full reconstruction
 * --------------------------------------------------------------------------
 * RECALL — the invariant: d[len-1] = the SMALLEST possible tail value of an
 * increasing subsequence of length len. d is always sorted, so a[i] can extend
 * the longest length whose tail is < a[i] — found by binary search; a[i] then
 * becomes a better (smaller) tail for that length.
 * (d is NOT an actual subsequence! reconstruction needs the par[] bookkeeping.)
 *
 * >>> THE ONE SWITCH <<<
 *   STRICTLY increasing   : lower_bound   (as written)
 *   NON-DECREASING (ties ok): upper_bound  — that's the entire change
 * Longest strictly DECREASING: run on negated values (or reversed array).
 *
 * SNIPPET (inside solve). Needs n, a. Produces:
 *   sz(d)   = LIS length
 *   lis     = one actual LIS (values; use indices via par-chain if needed)
 *   lenAt[i]= length of the best increasing subsequence ENDING at i (often useful alone)
 */
vector<int> d;                        // d[len-1] = best (smallest) tail for that len
    vector<int> lenAt(n), par(n), idxOfLen;   // idxOfLen[len-1] = index holding that tail
    for (int i=0; i<n; i++) {
        int j = lower_bound(all(d), a[i]) - d.begin();   // upper_bound -> non-decreasing
        if (j == sz(d)) d.pb(a[i]), idxOfLen.pb(i);   // extends the longest -> new length
        else d[j] = a[i], idxOfLen[j] = i;            // better (smaller) tail for length j+1
        lenAt[i] = j + 1;
        par[i] = j ? idxOfLen[j-1] : -1;      // who comes before me in MY subsequence
    }

    vector<int> lis;                          // reconstruct by walking parents
    for (int cur = idxOfLen.back(); ~cur; cur = par[cur]) lis.pb(a[cur]);
    reverse(all(lis));
