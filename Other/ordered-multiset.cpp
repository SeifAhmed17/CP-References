/*
 * ORDERED SET / MULTISET (GNU pb_ds) — std::set + ORDER STATISTICS in O(log n)
 * ----------------------------------------------------------------------------
 * The two extra superpowers over std::set:
 *   s.order_of_key(x)  -> how many elements are STRICTLY LESS than x  (x's rank)
 *   s.find_by_order(i) -> iterator to the i-th smallest (0-indexed); *it to read
 * -> "k-th smallest" and "count elements < x" without a Fenwick.
 *
 * ordered_set<T>      : unique elements, everything works like std::set.
 *
 * ordered_multiset<T> : duplicates via the less_equal comparator HACK — the tree
 * thinks equal elements are "different", which BREAKS some members:
 *   !! find(x)  -> ALWAYS returns end()          (never use)
 *   !! erase(x) -> silently erases NOTHING        (never use)
 *   !! lower_bound / upper_bound SWAP meanings   (lower_bound acts like upper_bound & vice versa)
 *   OK: insert, order_of_key (still = count of elements < x), find_by_order.
 *
 *   ERASE ONE COPY of x (the only safe way):
 *     auto it = ms.find_by_order(ms.order_of_key(x));      // iterator to first occurrence of x
 *     if (it != ms.end() && *it == x) ms.erase(it);        // guard: x might be absent
 *
 * Include the two headers below (they're not in bits/stdc++.h on some setups).
 */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T>
using ordered_multiset =  tree<T, null_type, less_equal<T>, rb_tree_tag,  tree_order_statistics_node_update>;
