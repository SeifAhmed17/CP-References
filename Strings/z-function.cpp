/*
 * Z-FUNCTION — O(n)
 * -----------------
 * z[i] = length of the longest common prefix of s and s[i..]   (z[0] = n by convention)
 *   e.g. "aabxaab" -> z = 7 1 0 0 3 1 0
 *
 * RECALL — the z-box [l, r): the rightmost segment matched against the prefix.
 * Inside it, s[i..] looks like s[i-l..], so z[i] starts from min(z[i-l], r-i)
 * for free, then extends by brute force (each extension pushes r forward ->
 * total O(n) amortized).
 *
 * KMP's pi or Z? Same power, interchangeable. Z is often more intuitive:
 * "how far does the string match ITSELF starting here".
 *
 * USES:
 *   - matching: z on  p + '#' + t ; z[i] == |p| -> occurrence of p at t[i - |p| - 1].
 *   - "is s a concatenation of k copies": z[n/k] stuff / periods.
 *   - string compression, distinct-prefix tricks, comparing suffix vs whole string.
 */
vector<int> zFunction(const string& s) {
    int n = sz(s);
    vector<int> z(n); z[0] = n;
    for (int i=1, l=0, r=0; i<n; i++) {           // [l, r) = rightmost z-box
        if (i < r) z[i] = min(r - i, z[i-l]);     // free start, capped by the box edge
        while (i + z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;   // extend by hand
        if (i + z[i] > r) l = i, r = i + z[i];    // new rightmost box
    }
    return z;
}

// all START positions (0-indexed) of pattern p inside text t
vector<int> matches(const string& t, const string& p) {
    int m = sz(p);
    vector<int> z = zFunction(p + '#' + t), res;
    for (int i=m+1; i<sz(z); i++)
        if (z[i] == m) res.pb(i - m - 1);
    return res;
}
