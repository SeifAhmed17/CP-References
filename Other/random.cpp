/*
 * RANDOM — the ONLY rng you should use in CP (never rand()/srand: weak + 32767 cap on MSVC)
 * -----------------------------------------------------------------------------------------
 * rand(l, r) -> uniform integer in [l, r], BOTH INCLUSIVE. Type follows the args:
 *   rand(1, 100)  -> int      rand(1LL, (ll)1e18) -> ll     (don't mix int and ll args!)
 *
 * OTHER USES:
 *   shuffle(all(v), rng);              // kill adversarial input order (anti-quicksort tests)
 *   rng() by itself                    // raw random 64-bit number
 *
 * WHEN randomness saves you:
 *   - random bases/keys for hashing (Strings/hashing, multiset-hashing)
 *   - randomized algorithms: pick random pivot/sample, "guess a likely answer" tricks
 *   - stress-testing: generate small random tests to diff brute force vs solution
 */
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> T rand(T l, T r) { return uniform_int_distribution<T>(l, r)(rng); }
