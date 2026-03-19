ll c[N][N];

void pascal()
{
    for (int i=0; i<N; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j=1; j<i; j++) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
        }
    }
}