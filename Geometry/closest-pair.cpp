/*
 * CLOSEST PAIR OF POINTS — O(n log n) sweep line. Returns SQUARED distance.
 * -------------------------------------------------------------------------
 * Needs P / dist2 from geometry-basics.cpp. n >= 2. Duplicates -> returns 0.
 *
 * RECALL — the sweep: process points left to right, keep an "active strip" of
 * points whose x is within D = sqrt(best) of the current point, ordered by y
 * (the set). For each new point only candidates with |dy| <= D matter — and a
 * D x 2D box can only hold O(1) points that are pairwise >= D apart, so the
 * inner loop is amortized constant. best only shrinks -> total O(n log n).
 *
 * The only double-ish moment is computing D = ceil(sqrt(best)) to bound the
 * strip; all COMPARISONS stay in integers (dist2), so precision can't hurt
 * correctness — D is just a (safe, rounded-up) search radius.
 */
ll closestPair(vector<P> p) {
    sort(all(p));                              // by x (then y) — P's operator<
    set<pair<ll,ll>> strip;                    // {y, x} of points in the active strip
    ll best = LLONG_MAX;
    int j = 0;                                 // strip's left edge (index into p)
    for (int i=0; i<sz(p); i++) {
        ll D = (ll)ceill(sqrtl((long double)best));
        while (j < i && p[i].x - p[j].x >= D)  // too far left to ever matter -> evict
            strip.erase({p[j].y, p[j].x}), j++;

        for (auto it = strip.lower_bound({p[i].y - D, LLONG_MIN});
             it != strip.end() && it->first <= p[i].y + D; ++it)
            best = min(best, dist2({it->second, it->first}, p[i]));

        strip.insert({p[i].y, p[i].x});
    }
    return best;                               // squared! sqrt only for output
}
