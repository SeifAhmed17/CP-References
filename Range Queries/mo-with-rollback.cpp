/*
 * MO WITH ROLLBACKS ("Mo, add-only") — SKELETON, fill the marked spots
 * --------------------------------------------------------------------
 * Use when ADD is easy but DELETE is impossible/ugly:
 *   running max / "max frequency" / merging DSU components / max subarray-ish info.
 * Complexity: O(n*sqrt(q) + q*sqrt(n)) adds — no deletes ever happen.
 *
 * RECALL — how deletes are avoided:
 *   Group queries by BLOCK OF L; inside a block sort by r ASCENDING.
 *   For one block [lBlock, rBlock]:
 *     - R starts at rBlock+1 and only GROWS through the block's queries
 *       -> right-side adds are permanent for the block, never undone.
 *     - The left part (l .. rBlock) is small (<= SQ elements): add it, answer,
 *       then ROLLBACK just those adds (undo via a stack of old values).
 *     - Tiny queries fully inside the block (r <= rBlock) -> brute force over
 *       <= SQ elements directly, then undo.
 *   Rollback = restore recorded old values in reverse order. NO delete logic needed —
 *   that's the whole point (e.g. you can't "un-max" a running maximum, but you CAN
 *   restore its previous snapshot).
 *
 * TO USE: paste into solve(), declare n, q, SQ (~sqrt(n)), the array, and
 *   vector<int> answer(q); then fill every `//` hole below.
 */
class MO_With_Rollbacks {


    struct Query {
        int l, r, iq;
        bool operator<(const Query& other) const {
            return r < other.r;               // r ascending WITHIN a block (no snake here!)
        }
    };

    struct State {
        // one undo record: whatever add() overwrites, e.g. {int* where, int oldVal}
        // or {value, oldCnt} — enough to restore EXACTLY one add()'s damage
    };

    MO_With_Rollbacks(vector<int>& a, vector<pair<int,int>>& quer) {

    }

    vector<int> MO()
    {
        int bCnt = (n+SQ-1)/SQ;               // number of l-blocks
        vector<vector<Query>> queries(bCnt);  // bucket queries by block of l
        for (int i=0; i<q; i++) {
            int l, r; cin >> l >> r, --l ,--r;
            queries[l/SQ].pb({l,r,i});
        }
        for (auto& qu : queries) sort(all(qu));

        int checkpoint, ans;                  // ans = CURRENT maintained answer
        stack<State> changes;                 // undo log

        auto reset = [&] {
            // wipe the whole structure (called once per block): cnt[]=0, ans=0, clear changes
        };

        auto rollback = [&] {                 // undo everything after `checkpoint`
            while (sz(changes) > checkpoint) {
                auto& c = changes.top(); changes.pop();
                // restore c's old values (reverse order is automatic via the stack)
            }
        };

        auto add = [&] (int idx) {
            // a[idx] enters: PUSH the old state onto `changes` FIRST, then apply.
            // NOTE: `ans` itself must also be restorable -> record it in State too,
            //       or recompute it; easiest is to save {oldAns, ...} in every record.
        };



        for (int ib=0; ib<bCnt; ib++) {

            reset();                          // fresh structure for this block

            int lBlock = ib*SQ, rBlock = min(n-1, lBlock+SQ-1);
            int R = rBlock + 1;               // right pointer, only moves forward

            for (const auto& [l, r, iq] : queries[ib]) {

                if (r <= rBlock) {            // tiny query, lives inside the block

                    // brute force: for (int j=l; j<=r; j++) add(j);

                    answer[iq] = ans;

                    // rollback();  (undo ALL of it — set checkpoint=0 before, or loop-pop)

                    continue;
                }

                while (R <= r) add(R++);      // permanent right-side adds (survive the block)
                checkpoint = sz(changes);     // <- everything after this will be undone

                for (int j=rBlock; j>=l; j--) add(j);   // temporary left part

                answer[iq] = ans;

                rollback();                   // undo only the left part
            }
        }

        return answer;
    }
};
