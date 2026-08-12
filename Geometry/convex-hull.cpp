/*
 * CONVEX HULL (monotone chain) + FARTHEST PAIR (rotating calipers)
 * ----------------------------------------------------------------
 * Needs P / cross / dist2 from geometry-basics.cpp.  O(n log n) (the sort dominates).
 *
 * hull(points) -> vertices of the convex hull in CCW order, starting from the
 * leftmost-lowest point. Handles duplicates and n <= 2. As written it DROPS
 * collinear boundary points (strict hull) — that's what you want 95% of the time.
 *
 * RECALL — monotone chain: sort by (x, y). Build the LOWER hull left->right:
 * keep the chain turning LEFT (CCW); a new point that makes the last turn
 * non-left (cross <= 0) pops the middle point. Then the UPPER hull right->left
 * the same way. Concatenate (each half omits its last point = other's first).
 *
 * CHANGE HERE: to KEEP collinear points on the hull, pop on `cross < 0` instead
 * of `cross <= 0` (both loops). Warning: calipers below then needs the strict hull.
 *
 * USES: min fence around points, farthest pair (below), hull + area2 for
 * "largest enclosed region" problems, check point vs CONVEX polygon in O(log n).
 */
vector<P> hull(vector<P> p) {
    sort(all(p));
    p.erase(unique(all(p)), p.end());          // exact duplicates break the chain logic
    int n = sz(p);
    if (n <= 2) return p;                      // hull is the points themselves

    vector<P> h(2*n);
    int k = 0;
    for (int i=0; i<n; i++) {                  // lower hull
        while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;   // pop non-left turns
        h[k++] = p[i];
    }
    for (int i=n-2, t=k+1; i>=0; i--) {        // upper hull (t protects the lower part)
        while (k >= t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k-1);                             // last point == first point, drop it
    return h;                                  // CCW order
}

/*
 * FARTHEST PAIR OF POINTS = diameter of the convex hull (squared).
 * Rotating calipers: walk edge i around the hull; the farthest vertex j from
 * edge (i, i+1) only ever moves FORWARD -> O(n) total after the hull.
 * "Farther from the edge" is compared by triangle area (cross), no doubles.
 * Pass the STRICT hull (default hull() above). Answer is sqrt(result) if needed.
 */
ll diameter2(vector<P>& h) {
    int n = sz(h);
    if (n <= 1) return 0;
    if (n == 2) return dist2(h[0], h[1]);
    ll best = 0;
    for (int i=0, j=1; i<n; i++) {
        while (cross(h[i], h[(i+1)%n], h[(j+1)%n]) > cross(h[i], h[(i+1)%n], h[j]))
            j = (j+1)%n;                       // advance the caliper
        best = max({best, dist2(h[i], h[j]), dist2(h[(i+1)%n], h[j])});
    }
    return best;
}
