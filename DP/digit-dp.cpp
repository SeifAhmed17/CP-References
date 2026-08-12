/*
 * DIGIT DP — count numbers in a range with a digit property, O(len * STATES * 10)
 * -------------------------------------------------------------------------------
 * THE FRAME (memorize this, it never changes):
 *   answer for [L, R]  =  f(R) - f(L-1)        <- reduces everything to f(X) = count in [0, X]
 *   go(pos, state, tight, started):
 *     pos     = which digit of X we're placing (left to right)
 *     tight   = are we still GLUED to X's prefix? (if yes, digit can't exceed X's digit;
 *               once we place something smaller, tight becomes false FOREVER -> free digits)
 *     started = have we placed a nonzero digit yet? (false = still in leading zeros;
 *               matters when the property cares about actual digits, e.g. "no repeated
 *               digit", where leading zeros must NOT count as the digit 0)
 *     state   = THE problem-specific part (example below: digit sum mod K)
 *
 * MEMOIZE only (!tight && started) states: tight paths are a single chain down X
 * (visited once anyway) and not-started is a single all-zeros chain. So dp[][]
 * needs no tight/started dimensions -> small and simple.
 *
 * EXAMPLE WIRED IN: how many numbers in [0, X] have digit sum divisible by K.
 * ADAPT: replace `state`'s meaning + the base-case check + the transition line.
 * Common states: sum mod K, last digit (adjacent constraints), bitmask of used
 * digits, "contains 13" flag, count of some digit — anything small.
 *
 * PITFALLS:
 *   - memset dp to -1 INSIDE f(X) (each X is a fresh memo — state meanings collide).
 *   - f(L-1) with L = 0 -> f(-1): must return 0 (guard below).
 *   - the empty/never-started path represents the number 0 — decide if the base
 *     case should count it (here: yes, sum 0 divides K) and mind it when L = 0.
 */
string s;                 // X as a string of digits
int K;                    // example parameter
ll dp[20][200];           // dp[pos][state] for the (!tight && started) universe

ll go(int pos, int state, bool tight, bool started) {
    if (pos == sz(s)) return state == 0;              // CHANGE: does `state` satisfy the property?

    if (!tight && started && dp[pos][state] != -1) return dp[pos][state];

    ll res = 0;
    int lim = tight ? s[pos]-'0' : 9;                 // glued -> can't exceed X's digit
    for (int dig=0; dig<=lim; dig++) {
        int nstate = (state + dig) % K;               // CHANGE: the transition
        // if the property ignores leading zeros, guard with:  started || dig > 0 ? ... : state
        res += go(pos+1, nstate, tight && dig == lim, started || dig > 0);
    }

    if (!tight && started) dp[pos][state] = res;
    return res;
}

ll f(ll x) {              // count of valid numbers in [0, x]
    if (x < 0) return 0;
    s = to_string(x);
    memset(dp, -1, sizeof dp);
    return go(0, 0, true, false);
}
// answer for [L, R] = f(R) - f(L-1)
