class BinaryTrie {

    static const int MAXBITS = 29;
    class Node {
    public:
        Node* child[2];
        int freq[2];
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
            if (cur->child[c] == nullptr) cur->child[c] = new Node();
            cur->freq[c]++;
            cur = cur->child[c];
        }
    }

    void del(Node* cur, int n, int i) {

        if (i == -1) return;
        bool c = n>>i&1;
        del(cur->child[c], n, i-1);

        cur->freq[c]--;

        if (!cur->freq[c]) {
            delete cur->child[c];
            cur->child[c] = nullptr;
        }
    }

    void del(int n) {
        del(root,n,MAXBITS);
    }

};