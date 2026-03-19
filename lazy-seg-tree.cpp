struct Node {
    static int DEFAULT_VALUE, DEFAULT_LAZY;
    int val, lazy;
    bool isLazy;

    Node(int x = DEFAULT_VALUE) : val(x), isLazy(false), lazy(DEFAULT_LAZY) {}

    void change(int x) {
        val += x;
        lazy += x;
        isLazy = true;
    }
};
int Node::DEFAULT_VALUE = 0, Node::DEFAULT_LAZY = 0;

class SegmentTree {
private:
    int TREESIZE;
    vector<Node> tree;

    Node merge(const Node &nl, const Node &nr) { return Node(nl.val + nr.val); }

    void Build(const vector<int> &a, int idx, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int) a.size()) tree[idx] = Node(a[lx]);
            else tree[idx] = Node();
            return;
        }

        int mid = (lx + rx) >> 1;
        Build(a, 2 * idx + 1, lx, mid);
        Build(a, 2 * idx + 2, mid + 1, rx);

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }


    void propagate(int idx, int lx, int rx) {
        if (lx == rx || !tree[idx].isLazy) return;

        tree[2 * idx + 1].change(tree[idx].lazy);
        tree[2 * idx + 2].change(tree[idx].lazy);

        tree[idx].isLazy = false;
        tree[idx].lazy = Node::DEFAULT_LAZY;
    }

    Node query(int l, int r, int idx, int lx, int rx) {
        propagate(idx, lx, rx);

        if (lx >= l && rx <= r) return tree[idx];
        if (rx < l || lx > r) return Node();

        int mid = (lx + rx) >> 1;
        Node nLeft = query(l, r, 2 * idx + 1, lx, mid);
        Node nRight = query(l, r, 2 * idx + 2, mid + 1, rx);

        return merge(nLeft, nRight);
    }

    void update(int l, int r, int newVal, int idx, int lx, int rx) {
        propagate(idx, lx, rx);

        if (lx >= l && rx <= r) {
            tree[idx].change(newVal);
            return;
        }
        if (rx < l || lx > r) return;

        int mid = (lx + rx) >> 1;
        update(l, r, newVal, 2 * idx + 1, lx, mid);
        update(l, r, newVal, 2 * idx + 2, mid + 1, rx);

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

public:
    SegmentTree(const vector<int> &a) {
        TREESIZE = 1;
        while (TREESIZE < (int) a.size()) TREESIZE <<= 1;
        tree.resize(2 * TREESIZE);
        Build(a, 0, 0, TREESIZE - 1);
    }

    int query(int l, int r) { return query(l, r, 0, 0, TREESIZE - 1).val; }

    void update(int l, int r, int newVal) { update(l, r, newVal, 0, 0, TREESIZE - 1); }
};