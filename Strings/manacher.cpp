/*
 * MANACHER — ALL palindromic substrings in O(n)
 * ---------------------------------------------
 * d1[i] = # of ODD palindromes centered at i  (= radius incl. center)
 *         longest odd palindrome centered at i has length 2*d1[i] - 1.
 * d2[i] = # of EVEN palindromes centered BETWEEN i-1 and i
 *         longest even one there has length 2*d2[i].
 *   e.g. "abaa": d1 = 1 2 1 1, d2 = 0 0 0 1  ("aa" centered between index 2,3)
 *
 * RECALL — same z-box idea as z-function: keep the rightmost known palindrome
 * [l, r]; inside it, position i mirrors to l+r-i, so d[i] starts from the
 * mirror's value (capped by the box), then extends by brute force. O(n) amortized.
 *
 * INSTANT ANSWERS AFTER O(n) BUILD:
 *   - longest palindromic substring: max over 2*d1[i]-1 and 2*d2[i].
 *   - is s[l..r] a palindrome, O(1):   (len = r-l+1)
 *       len odd :  d1[(l+r)/2]     >= (len+1)/2
 *       len even:  d2[(l+r+1)/2]   >= len/2
 *   - total # of palindromic substrings = sum(d1) + sum(d2).
 */
vector<int> d1, d2;

void manacher(const string& s) {
    int n = sz(s);
    d1.assign(n, 0); d2.assign(n, 0);

    for (int i=0, l=0, r=-1; i<n; i++) {                  // odd lengths
        int k = (i > r) ? 1 : min(d1[l+r-i], r-i+1);      // mirror value, capped
        while (0 <= i-k && i+k < n && s[i-k] == s[i+k]) k++;   // extend
        d1[i] = k--;
        if (i+k > r) l = i-k, r = i+k;                    // new rightmost palindrome
    }

    for (int i=0, l=0, r=-1; i<n; i++) {                  // even lengths
        int k = (i > r) ? 0 : min(d2[l+r-i+1], r-i+1);
        while (0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) k++;
        d2[i] = k--;
        if (i+k > r) l = i-k-1, r = i+k;
    }
}
