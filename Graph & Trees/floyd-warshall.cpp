/*
 * FLOYD-WARSHALL — ALL-pairs shortest paths, O(n^3), n up to ~400-500
 * -------------------------------------------------------------------
 * Handles negative EDGES fine; detects negative CYCLES (see below).
 *
 * RECALL — d[i][j] after iteration k = shortest i->j path using only
 * intermediate vertices from {0..k}.  >>> k MUST be the OUTERMOST loop <<<
 * (k inside i/j is the classic silent-wrong-answer bug).
 *
 * SETUP (snippet, inside solve):
 *   d[i][i] = 0; d[u][v] = min edge weight (parallel edges: take min!); else INF.
 *
 * NOTES:
 *   - the INF guards below avoid INF + w overflow/poisoning; alternatively use
 *     INF = 1e18/2 and clamp, but the guards are cleaner.
 *   - NEGATIVE CYCLE: after the loops, d[x][x] < 0 for some x  <=>  neg cycle.
 *     Pair (i,j) has dist -infinity iff it goes through one:
 *       exists x with d[i][x] != INF && d[x][j] != INF && d[x][x] < 0.
 *   - path reconstruction: keep nxt[i][j] = first hop of best i->j; on improve:
 *     nxt[i][j] = nxt[i][k]; walk nxt from i until j.
 *   - also good for transitive closure (bitset version) and min/max bottleneck
 *     ("minimize the maximum edge"): replace + with max and min stays min.
 */
ll d[MAXN][MAXN];        // MAXN ~ 500 -> 2 MB of ll, fine

void floyd(int n) {
    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++) {
            if (d[i][k] == INF) continue;            // nothing goes through k from i
            for (int j=0; j<n; j++) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
}
