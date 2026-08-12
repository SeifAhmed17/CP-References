/*
 * BINARY TRIE — numbers as bit-strings (MSB first). THE tool for XOR problems.
 * ----------------------------------------------------------------------------
 * insert / del / maxXor in O(MAXBITS) each.
 *
 * CHANGE HERE: MAXBITS = highest bit index.
 *   29 covers values < 2^30. For long long values change: int -> ll, 1<<i -> 1LL<<i,
 *   MAXBITS -> 59 (or 62), and `bool c = n>>i&1` stays fine.
 *
 * RECALL — why a trie: walking from the top bit, at each level you can CHOOSE
 * the child that makes the current answer-bit 1 (greedy is optimal because a
 * higher bit beats all lower bits combined).
 *
 * freq[c] = how many stored numbers go through child c (supports duplicates;
 * del() frees a branch when its freq hits 0, so `child != NULL` == "branch alive").
 *
 * CLASSIC USES:
 *   - max XOR pair in an array: insert all, maxXor(a[i]) over i
 *   - max XOR subarray: prefix XORs + this
 *   - online "insert numbers / query best xor with x" sets
 *
 * PITFALL: del(n) assumes n IS in the trie (like trie.cpp). maxXor assumes
 * the trie is non-empty.
 */
class BinaryTrie {

    static const int MAXBITS = 29;      // CHANGE: 29 -> values < 2^30; 59+ll for big values
    class Node {
    public:
        Node* child[2];
        int freq[2];                    // freq[c] = numbers passing through child c
        Node() {
            memset(child,0,sizeof child);
            memset(freq,0,sizeof freq);
        }
    };
    Node* root = new Node();

public:
    void insert(int n) {
        Node* cur = root;
        for (int i=MAXBITS; i>=0; i--) {
            bool c = n>>i&1;
            if (cur->child[c] == NULL) cur->child[c] = new Node();
            cur->freq[c]++;
            cur = cur->child[c];
        }
    }

    // unwind the path, decrement freqs, free dead branches
    void del(Node* cur, int n, int i) {

        if (i == -1) return;
        bool c = n>>i&1;
        del(cur->child[c], n, i-1);

        cur->freq[c]--;

        if (!cur->freq[c]) {
            delete cur->child[c];
            cur->child[c] = NULL;
        }
    }

    void del(int n) {                   // !! only call if n is currently in the trie
        del(root,n,MAXBITS);
    }

    // max of (x XOR y) over all stored y — greedy: prefer the OPPOSITE bit
    int maxXor(int x) {
        Node* cur = root;
        int res = 0;
        for (int i=MAXBITS; i>=0; i--) {
            bool c = x>>i&1;
            if (cur->child[!c]) {           // opposite bit available -> answer bit = 1
                res |= 1<<i;                // (1LL<<i for the ll version!)
                cur = cur->child[!c];
            }
            else cur = cur->child[c];       // forced to match -> answer bit = 0
        }
        return res;
    }
};
