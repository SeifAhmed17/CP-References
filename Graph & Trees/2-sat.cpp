/*
 * 2-SAT — satisfy a formula of (literal OR literal) clauses, O(vars + clauses)
 * ----------------------------------------------------------------------------
 * WHEN: n boolean choices, constraints pairing at most TWO of them:
 * "at least one of a,b", "a and b can't both be picked", "a forces b", ...
 *
 * LITERALS: variable v -> literal T(v) = 2v ("v is true"), F(v) = 2v+1 ("v false").
 * Negation of any literal x is x^1. Build clauses with the helpers:
 *   either(x, y)   : clause (x OR y)
 *   implies(x, y)  : x -> y
 *   setTrue(x)     : x must hold
 *   exactlyOne...  : see comments below
 *
 * RECALL — why SCC solves it: clause (x OR y) = implications ¬x->y and ¬y->x.
 * If x and ¬x end up in the same SCC -> contradiction -> UNSAT.
 * Otherwise set each variable to the literal whose SCC is LATER in topological
 * order (= closer to a sink = SMALLER Tarjan id, since Tarjan emits sinks first).
 *
 * USAGE:
 *   TwoSat ts(n);
 *   ts.either(ts.T(a), ts.F(b));          // a OR !b
 *   if (!ts.solve()) -> impossible; else ts.val[v] = chosen value of v.
 */
struct TwoSat {
    int n;                                // number of VARIABLES
    vector<vector<int>> g;                // implication graph on 2n literals
    vector<int> comp, in, low, stk;
    int timer = 1, sccId = 0;
    vector<bool> val;                     // answer (valid after solve() returns true)

    TwoSat(int vars): n(vars), g(2*vars), comp(2*vars,-1), in(2*vars,0), low(2*vars,0), val(vars) {}

    int T(int v) { return 2*v; }          // literal "v = true"
    int F(int v) { return 2*v+1; }        // literal "v = false"   (negate any literal: x^1)

    void either(int x, int y) {           // (x OR y)
        g[x^1].pb(y);                     // ¬x -> y
        g[y^1].pb(x);                     // ¬y -> x
    }
    void implies(int x, int y) { either(x^1, y); }        // x -> y
    void setTrue(int x)        { either(x, x); }          // force x
    void notBoth(int x, int y) { either(x^1, y^1); }      // NAND: at most one of x,y
    void exactlyOne(int x, int y) { either(x, y); notBoth(x, y); }   // XOR

    void tarjan(int u) {
        in[u] = low[u] = timer++;
        stk.pb(u);
        for (int v : g[u]) {
            if (!in[v]) { tarjan(v); low[u] = min(low[u], low[v]); }
            else if (comp[v] == -1) low[u] = min(low[u], in[v]);   // still on stack
        }
        if (in[u] == low[u]) {
            while (true) {
                int x = stk.back(); stk.pop_back();
                comp[x] = sccId;
                if (x == u) break;
            }
            sccId++;
        }
    }

    bool solve() {
        for (int i=0; i<2*n; i++) if (!in[i]) tarjan(i);
        for (int v=0; v<n; v++) {
            if (comp[2*v] == comp[2*v+1]) return false;   // v <-> ¬v  ->  UNSAT
            val[v] = comp[2*v] < comp[2*v+1];             // smaller id = closer to sink -> pick it
        }
        return true;
    }
};
