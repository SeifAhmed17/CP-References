/*
 * PREFIX FUNCTION + KMP MATCHING — O(n)
 * -------------------------------------
 * pi[i] = length of the longest PROPER prefix of s[0..i] that is also a suffix
 *         of s[0..i]  ("border" length).   e.g. "abcab" -> pi = 0 0 0 1 2
 *
 * RECALL — the loop: to extend position i, try the previous border j = pi[i-1];
 * if s[i] doesn't match s[j], FALL BACK to the border-of-the-border pi[j-1],
 * repeat. Borders of borders enumerate ALL borders — that's the whole trick.
 *
 * PATTERN MATCHING: build pi on  p + '#' + t  ('#' = any char not in either
 * string — it stops borders from crossing the boundary). pi == |p| -> full match.
 *
 * CLASSIC FACTS (asked constantly):
 *   - smallest PERIOD of s = n - pi[n-1]; it tiles s perfectly iff n % period == 0.
 *   - all borders of s: pi[n-1], pi[pi[n-1]-1], ... (chain down to 0).
 *   - count occurrences of every prefix / build prefix automaton — extensions of pi.
 *   - "shortest string with s as prefix and suffix"-type tricks: think borders.
 */
vector<int> prefixFunction(const string& s) {
    int n = sz(s);
    vector<int> pi(n);
    for (int i=1; i<n; i++) {
        int j = pi[i-1];                          // best border so far
        while (j && s[i] != s[j]) j = pi[j-1];    // fall back through smaller borders
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// all START positions (0-indexed) of pattern p inside text t
vector<int> matches(const string& t, const string& p) {
    int m = sz(p);
    vector<int> pi = prefixFunction(p + '#' + t), res;
    for (int i=m+1; i<sz(pi); i++)
        if (pi[i] == m) res.pb(i - 2*m);          // i is in "combined" coords -> shift back
    return res;
}
