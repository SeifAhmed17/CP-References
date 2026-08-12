/*
 * SEGMENT TREE (recursive) — point update, range query. O(log n) each.
 * --------------------------------------------------------------------
 * 0-INDEXED. query(l, r) is INCLUSIVE on both ends.
 *
 * USAGE:
 *   SegmentTree st; st.init(n);
 *   st.update(pos, val);      // a[pos] = val  (assignment, not +=; change in update() if needed)
 *   st.query(l, r);
 *
 * CHANGE HERE (the only two spots that define "what the tree computes"):
 *   1) merge()      — sum / min / max / gcd / max-subarray-struct / ...
 *   2) Node()       — the NEUTRAL element, must satisfy merge(x, neutral) = x:
 *                     sum -> 0, min -> INF, max -> -INF, gcd -> 0.
 *      (query returns Node() for fully-outside ranges, so a wrong neutral = wrong answers!)
 *   Put anything you need inside Node (e.g. {sum, prefix, suffix, best} for max subarray)
 *   and combine the fields in merge().
 *
 * NOTES:
 *   - Size padded up to a power of two; leaves beyond n hold Node() so they're harmless.
 *   - Memory: allocates 4*TREESIZE but 2*TREESIZE is enough (TREESIZE already padded) —
 *     wasteful but safe; shrink if memory-tight.
 *   - To BUILD from an initial array in O(n): see lazy-seg-tree.cpp's Build (same idea),
 *     or just call update n times (O(n log n), usually fine).
 */
class SegmentTree {

    struct Node {
        int val;
        Node(int x = 0) : val(x) {}     // CHANGE: neutral element (0 for sum, INF for min...)
    };

    int TREESIZE;
    vector<Node> tree;

    Node merge(const Node& nl, const Node& nr) { return Node(nl.val + nr.val); }  // CHANGE

    Node query(int l, int r, int idx, int lx, int rx) {
        if (rx < l || lx > r) return Node();      // fully outside -> neutral
        if (lx >= l && rx <= r) return tree[idx]; // fully inside  -> take node

        int mid = (lx + rx) >> 1;                 // children: 2i+1 = [lx,mid], 2i+2 = (mid,rx]
        return merge(query(l, r, 2*idx+1, lx, mid), query(l, r, 2*idx+2, mid+1, rx));
    }

    void update(int pos, int newVal, int idx, int lx, int rx) {
        if (lx == rx) {                 // reached the leaf
            tree[idx] = Node(newVal);   // CHANGE here for a[pos] += x style updates
            return;
        }

        int mid = (lx + rx) >> 1;
        if (pos <= mid) update(pos, newVal, 2*idx+1, lx, mid);
        else update(pos, newVal, 2*idx+2, mid+1, rx);

        tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);   // recompute on the way up
    }

public:

    SegmentTree(){}

    void init(const int& n) {
        TREESIZE = 1;
        while (TREESIZE < n) TREESIZE <<= 1;    // pad to power of two
        tree.assign(4 * TREESIZE, Node());      // 2*TREESIZE suffices — see header
    }

    int query(int l, int r) { return query(l, r, 0, 0, TREESIZE-1).val; }

    void update(int pos, int newVal) { update(pos, newVal, 0, 0, TREESIZE-1); }
};
