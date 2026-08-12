/*
 * COMBINATORICS (factorials + modular inverse)
 * --------------------------------------------
 * nCr / nPr in O(1) per query after O(n) precompute.
 *
 * REQUIREMENT: mod must be PRIME (inverse uses Fermat: a^(mod-2) = a^-1).
 *              If mod is NOT prime -> use Pascal's triangle (ncr-pascal.cpp)
 *              or factor out common primes manually.
 *
 * USAGE:
 *   Combinatorics C;
 *   C.Init(maxN, 1e9+7);   // maxN = largest n you will ever ask about
 *   C.nCr(n, r); C.nPr(n, r);
 *   Also gives you safe modular ops: Add / Sub / Mul / Div / Pow / Inv.
 *
 * RECALL - common formulas:
 *   - Stars and bars: #solutions of x1+...+xk = n (xi >= 0) = C(n+k-1, k-1)
 *   - Catalan(n) = C(2n, n) / (n+1) = C(2n,n) - C(2n,n+1)
 *     (balanced brackets, binary trees, non-crossing paths)
 *   - Multiset permutations: n! / (c1! * c2! * ...)
 *   - Hockey stick: sum_{i=r..n} C(i, r) = C(n+1, r+1)
 */
class Combinatorics
{
public:
    ll mod;
    vector<ll> fact, InvFact;

    ll Pow(ll a, ll b) // binary exponentiation, O(log b)
    {
        ll res = 1;
        a %= mod;
        while(b)
        {
            if(b&1) res = (res * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return res;
    }

    ll Inv(ll a) {return Pow(a, mod-2);}                  // ONLY valid for prime mod, gcd(a,mod)=1
    ll Add(ll a, ll b) {return ((a%mod)+(b%mod))%mod;}
    ll Mul(ll a, ll b) {return ((a%mod)*(b%mod))%mod;}
    ll Sub(ll a, ll b) {return ((a-b)%mod + mod)%mod;}    // handles negatives correctly
    ll Div(ll a, ll b) {return Mul(a, Inv(b));}

    void Init(ll n, ll x) // call ONCE with the max n needed; O(n + log mod)
    {
        fact.resize(n+1); InvFact.resize(n+1);
        mod = x;

        fact[0] = 1;
        for(int i=1; i<=n; i++) fact[i] = Mul(fact[i-1], i);

        // one Pow call, then walk down: InvFact[i] = InvFact[i+1] * (i+1)
        InvFact[n] = Inv(fact[n]);
        for(int i=n-1; i>=0; i--) InvFact[i] = Mul(InvFact[i+1], i+1);
    }

    ll nPr(ll n, ll r) // ordered pick: n! / (n-r)!
    {
        if(n < 0 || r < 0  || n < r) return 0; // out-of-range = 0, so you can call it blindly
        return Mul(fact[n], InvFact[n-r]);
    }

    ll nCr(ll n, ll r) // unordered pick: n! / (r! (n-r)!)
    {
        if(n < 0 || r < 0  || n < r) return 0;
        return Mul(nPr(n,r), InvFact[r]);
    }
};
