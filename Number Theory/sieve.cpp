bool prime[N];
vector<int> primes;

void Sieve()
{
    fill(prime,prime+N,true);
    prime[0] = prime[1] = false;

    for (ll i=2; i*i<N; i++) {
        if (prime[i]) {
            primes.pb(i);
            for (ll j=i*i; j<N; j+=i) {
                prime[j] = false;
            }
        }
    }
}