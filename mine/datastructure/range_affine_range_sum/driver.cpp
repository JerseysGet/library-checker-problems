#ifdef LOCAL
#include "include/include.h"
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#endif
#ifndef DEBUG
#undef deb
#undef debm
#undef debseg
#define deb(...)
#define debm(...)
#define debseg(...)
#endif

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> o_set;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the kth largest element.(0-based)
template <typename T>
using minHeap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxHeap = priority_queue<T>;
#define int long long
#define all(s) s.begin(), s.end()
#define sz(s) (int)s.size()
#define testcases \
    cin >> tt;    \
    for (i = 1; i <= tt; i++)
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(NULL);                \
    cout.tie(NULL)
using longer = __int128_t;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> vpii;
typedef vector<bool> vb;
const int INF = LONG_LONG_MAX;
const int M = 1e9 + 7;

#include "../lazy.h"


void solve(__attribute__((unused)) int tt) {
    int n, q; cin >> n >> q;
    vi arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<node> leaves(n);
    for (int i = 0; i < n; i++) {
        leaves[i].sum = arr[i];
        leaves[i].width = 1;
    }

    seg_tree_lazy<node, update> seg(n);
    seg.set_leaves(leaves);

    while (q--) {
        int type; cin >> type;
        int l, r; cin >> l >> r; r--;
        if (type == 0) {
            int b, c; cin >> b >> c;
            Mint bmint = b, cmint = c;
            seg.upd(l, r, {bmint, cmint});
        } else {
            cout << seg.query(l, r).sum << "\n";
        }
    }
}

int32_t main() {
#ifdef LOCAL
    chrono::time_point<chrono::steady_clock> start, end;
    start = chrono::steady_clock::now();
#else
    fast;
#endif

    int tt = 1;
    int i = 1;
    // testcases
        solve(i);

#ifdef LOCAL
    end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cerr << "Took " <<  1e3 * elapsed_seconds.count() << "ms " << endl;
#endif
}