namespace Combinatorics
{
    ll mod;
    vector<ll> fact, InvFact;

    ll Pow(ll a, ll b)
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

    ll Inv(ll a) {return Pow(a, mod-2);}
    ll Add(ll a, ll b) {return ((a%mod)+(b%mod))%mod;}
    ll Mul(ll a, ll b) {return ((a%mod)*(b%mod))%mod;}
    ll Sub(ll a, ll b) {return ((a-b)%mod + mod)%mod;}
    ll Div(ll a, ll b) {return Mul(a, Inv(b));}

    void Init(ll n, ll x)
    {
        fact.resize(n+1); InvFact.resize(n+1);
        mod = x;

        fact[0] = 1;
        for(int i=1; i<=n; i++) fact[i] = Mul(fact[i-1], i);

        InvFact[n] = Inv(fact[n]);
        for(int i=n-1; i>=0; i--) InvFact[i] = Mul(InvFact[i+1], i+1);
    }

    ll nPr(ll n, ll r)
    {
        if(n < 0 || r < 0  || n < r) return 0;
        return Mul(fact[n], InvFact[n-r]);
    }

    ll nCr(ll n, ll r)
    {
        if(n < 0 || r < 0  || n < r) return 0;
        return Mul(nPr(n,r), InvFact[r]);
    }
};

using namespace Combinatorics;
