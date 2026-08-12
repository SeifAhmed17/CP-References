/*
 * SEGMENT TREE (iterative / "bottom-up") — point update, range query
 * ------------------------------------------------------------------
 * Same power as the recursive one but ~2-3x faster constant and works with
 * ANY n (no power-of-two padding; memory exactly 2n).
 *
 * 0-INDEXED, query(l, r) INCLUSIVE (converted to half-open [l, r+1) internally).
 *
 * LAYOUT RECALL: leaves live at tree[n .. 2n-1] (leaf i at n+i),
 * internal node i has children 2i and 2i+1, parent of i is i/2.
 * Query climbs from both ends inward, grabbing a node whenever it's
 * "sticking out" of the range (the l&1 / r&1 checks).
 *
 * CHANGE HERE:
 *   1) merge()  — sum / min / max / gcd / ...
 *   2) Node()   — the NEUTRAL element matching merge (sum->0, min->INF, ...)
 *   3) update() — currently ASSIGNS; make it `tree[pos].val += val` for increments.
 *
 * !! CAVEAT — NON-COMMUTATIVE merges (matrices, "function composition", hashes):
 *    this query accumulates the right side in reverse order. Fine for sum/min/max;
 *    for non-commutative ops keep two accumulators (resL, resR) and merge
 *    resL = merge(resL, tree[l++]) / resR = merge(tree[--r], resR), answer merge(resL, resR).
 *
 * BUILD from array in O(n): fill tree[n+i] = Node(a[i]),
 *   then for (i = n-1; i >= 1; i--) tree[i] = merge(tree[2i], tree[2i+1]).
 */
class SegmentTree {

    struct Node {
        int val;
        Node(int x = 0) : val(x) {}     // CHANGE: neutral element
    };

    int n;
    vector<Node> tree;

    Node merge(const Node& nl, const Node& nr) { return Node(nl.val + nr.val); }  // CHANGE

    Node queryy(int l, int r) {         // half-open [l, r)
        Node res = Node();
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) res = merge(res, tree[l++]);   // l is a right child -> take it, move right
            if (r&1) res = merge(res, tree[--r]);   // r is a right child -> take the one before
        }
        return res;
    }

public:
    SegmentTree(const int& _n){ init(_n); }

    void init(const int& _n) {
        n = _n;
        tree.assign(n<<1, Node());      // exactly 2n nodes
    }

    void update(int pos, int val) {     // a[pos] = val
        pos += n;                       // jump to the leaf
        tree[pos] = Node(val);
        while (pos > 1) {               // fix ancestors up to the root
            pos >>= 1;
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    int query(int l, int r) { return queryy(l, r+1).val; }   // inclusive wrapper
};
