vector<ll> p(n+1);
p[0] = 1; 
for (int i=1; i<=n; i++) {
    for (int k=1; ; k++) {
        ll g1 = 1LL * k * (3 * k - 1) / 2; 
        ll g2 = 1LL * k * (3 * k + 1) / 2; 

        if (g1 > i) break; 

        ll term = p[i - g1];
        if (g2 <= i) term = (term + p[i - g2]) % mod; 

        if (k & 1) p[i] = (p[i] + term) % mod; 
        else p[i] = (p[i] - term + mod) % mod; 
    }
}