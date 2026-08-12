/*
 * GEOMETRY BASICS — integer-only building blocks (no doubles until you must print)
 * --------------------------------------------------------------------------------
 * Coordinates up to 1e9 are safe: cross/dot/dist2 peak at ~8e18, fits ll.
 *
 * THE ONE TOOL THAT SOLVES 90% OF GEOMETRY — the cross product:
 *   cross(a, b)    = a.x*b.y - a.y*b.x     (of vectors)
 *   cross(o, a, b) = cross(a-o, b-o), its SIGN tells you where b is
 *                    relative to the line o->a:
 *        > 0  ->  b is to the LEFT  (counter-clockwise turn o->a->b)
 *        < 0  ->  b is to the RIGHT (clockwise turn)
 *        = 0  ->  o, a, b COLLINEAR
 *   |cross(o,a,b)| = 2 * area of triangle o,a,b.
 *
 * dot(a, b) > 0: angle < 90;  = 0: perpendicular;  < 0: angle > 90.
 *
 * PITFALLS:
 *   - NEVER compare double distances — compare SQUARED ll distances (dist2).
 *   - Read ints into ll immediately; subtraction before multiplication is what
 *     keeps everything in range.
 *   - Polygon functions expect vertices in order (CW or CCW), no repeated last point.
 */
struct P {
    ll x, y;
    P operator-(const P& o) const { return {x - o.x, y - o.y}; }
    P operator+(const P& o) const { return {x + o.x, y + o.y}; }
    bool operator<(const P& o) const { return x < o.x || (x == o.x && y < o.y); }
    bool operator==(const P& o) const { return x == o.x && y == o.y; }
};

ll cross(P a, P b) { return a.x*b.y - a.y*b.x; }
ll cross(P o, P a, P b) { return cross(a-o, b-o); }       // sign: see header
ll dot(P a, P b) { return a.x*b.x + a.y*b.y; }
ll dist2(P a, P b) { ll dx=a.x-b.x, dy=a.y-b.y; return dx*dx + dy*dy; }  // SQUARED distance
int sgn(ll v) { return (v > 0) - (v < 0); }

// is p on segment a-b (endpoints included)? collinear + inside the bounding box
bool onSeg(P a, P b, P p) {
    return cross(a, b, p) == 0
        && min(a.x,b.x) <= p.x && p.x <= max(a.x,b.x)
        && min(a.y,b.y) <= p.y && p.y <= max(a.y,b.y);
}

// do segments a-b and c-d share ANY point (crossing, touching, or overlapping)?
bool segIntersect(P a, P b, P c, P d) {
    int d1 = sgn(cross(c, d, a)), d2 = sgn(cross(c, d, b));
    int d3 = sgn(cross(a, b, c)), d4 = sgn(cross(a, b, d));
    if (d1 != d2 && d3 != d4) return true;   // proper crossing: each seg separates the other's ends
    return onSeg(a,b,c) || onSeg(a,b,d) || onSeg(c,d,a) || onSeg(c,d,b);  // touch / overlap cases
}

// TWICE the signed area of any simple polygon (shoelace).
// result > 0 -> vertices are CCW, < 0 -> CW. Real area = abs(...) / 2.0
// (keep the x2 version to stay in integers — area itself can be x.5)
ll area2(vector<P>& poly) {
    ll s = 0;
    for (int i=0, n=sz(poly); i<n; i++)
        s += cross(poly[i], poly[(i+1)%n]);
    return s;
}

// point vs simple polygon (ANY simple polygon, convex or not), O(n):
// returns 0 = outside, 1 = on the boundary, 2 = strictly inside   (ray casting)
int inPolygon(vector<P>& poly, P p) {
    int n = sz(poly), cnt = 0;
    for (int i=0; i<n; i++) {
        P a = poly[i], b = poly[(i+1)%n];
        if (onSeg(a, b, p)) return 1;
        cnt ^= ((p.y < a.y) - (p.y < b.y)) * cross(p, a, b) > 0;  // edge crosses the upward ray?
    }
    return cnt ? 2 : 0;
}
