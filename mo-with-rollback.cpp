

class MO_With_Rollbacks {


    struct Query {
        int l, r, iq;
        bool operator<(const Query& other) const {
            return r < other.r;
        }
    };

    struct State {
        //
    };

    MO_With_Rollbacks(vector<int>& a, vector<pair<int,int>>& quer) {
        
    }

    vector<int> MO()
    {
        int bCnt = (n+SQ-1)/SQ;
        vector<vector<Query>> queries(bCnt);
        for (int i=0; i<q; i++) {
            int l, r; cin >> l >> r, --l ,--r;
            queries[l/SQ].pb({l,r,i});
        }
        for (auto& qu : queries) sort(all(qu));

        int checkpoint, ans;
        stack<State> changes;

        auto reset = [&] {
            //
        };

        auto rollback = [&] {
            while (sz(changes) > checkpoint) {
                auto& c = changes.top(); changes.pop();
                // assign old values
            }
        };

        auto add = [&] (int idx) {
            //
        };


        
        for (int ib=0; ib<bCnt; ib++) {

            reset();

            int lBlock = ib*SQ, rBlock = min(n-1, lBlock+SQ-1);
            int R = rBlock + 1;

            for (const auto& [l, r, iq] : queries[ib]) {

                if (r <= rBlock) {

                    // brute force 

                    answer[iq] = ret;

                    // rollback
                    
                    continue;
                }

                while (R <= r) add(R++);
                checkpoint = sz(changes);

                for (int j=rBlock; j>=l; j--) add(j);

                answer[iq] = ans;

                rollback();
            }
        }

        return answer;
    }
};






