/*
 * EXTENDED GCD + MODULAR INVERSE (any mod) + CRT
 * ----------------------------------------------
 * extgcd(a, b, x, y): returns g = gcd(a,b) and fills x, y with  a*x + b*y = g.
 *
 * WHAT IT UNLOCKS:
 *   1) INVERSE MOD ANY m (m need NOT be prime, unlike Fermat in combinatorics.cpp):
 *        inv(a, m) valid iff gcd(a, m) == 1.
 *   2) LINEAR DIOPHANTINE a*x + b*y = c:
 *        solvable iff g | c; scale: x0 = x*(c/g), y0 = y*(c/g);
 *        ALL solutions: x = x0 + t*(b/g), y = y0 - t*(a/g), t any integer
 *        (use that to shift x into a wanted range).
 *   3) LINEAR CONGRUENCE a*x ≡ b (mod m):
 *        solvable iff g = gcd(a,m) divides b; then x ≡ (b/g)*inv(a/g, m/g)  (mod m/g),
 *        i.e. g distinct solutions mod m.
 *   4) CRT below.
 *
 * CRT — combine  x ≡ r1 (mod m1)  and  x ≡ r2 (mod m2)  into one congruence.
 *   GENERAL version: m1, m2 do NOT need to be coprime.
 *   Returns {x, lcm(m1,m2)} with 0 <= x < lcm, or {-1, -1} if incompatible
 *   (possible only in the non-coprime case, when r1 ≢ r2 mod gcd).
 *   Fold a whole system by chaining: cur = crt(cur, next), ...
 *   !! pass 0 <= r < m (normalize with ((r%m)+m)%m first).
 *   Overflow-safe up to lcm ~ 9e18 (__int128 used at the one risky multiply).
 */
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) { x = 1; y = 0; return a; }
    ll x1, y1, g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll inv(ll a, ll m) {                 // inverse of a mod m — REQUIRES gcd(a, m) == 1
    ll x, y;
    extgcd(a, m, x, y);
    return ((x % m) + m) % m;
}

pair<ll,ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll x, y, g = extgcd(m1, m2, x, y);          // m1*x + m2*y = g
    if ((r2 - r1) % g) return {-1, -1};         // no solution
    ll l = m1 / g * m2;                         // lcm
    ll d = m2 / g;
    ll k = (r2 - r1) / g % d * (x % d) % d;     // how many m1-steps to add to r1
    if (k < 0) k += d;
    ll ans = r1 + (ll)((__int128)k * m1 % l);   // k*m1 can pass 9e18 mid-multiply
    return {ans % l, l};
}
