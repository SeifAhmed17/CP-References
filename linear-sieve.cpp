int spf[N];
vector<int> primes;

void LinearSieve() {
    for (int i=2; i<N; i++) {
        if (!spf[i]) {
            spf[i] = i;
            primes.pb(i);
        }

        for (int j=0; j<sz(primes) && i * primes[j]<N && primes[j] <= spf[i]; j++) {
            spf[i*primes[j]] = primes[j];
        }
    }
}