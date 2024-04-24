struct KthAnc {
    vvi up;
    vi d;
    KthAnc(vvi& C, int root = 0) : up(64 - __builtin_clzll(sz(C)), vi(sz(C))), d(sz(C)) { dfs(C, root, root); }
    void dfs(vvi& adj, int from, int par) {
        up[0][from] = par;
        for (int i = 1; i < sz(up); i++)
            up[i][from] = up[i - 1][up[i - 1][from]];
        for (auto to : adj[from]) {
            if (to == par) continue;
            d[to] = 1 + d[from];
            dfs(adj, to, from);
        }
    }
    int kthAnc(int v, int k) {
        for (int i = 0; i < sz(up); i++)
            if ((k >> i) & 1) v = up[i][v];
        return v;
    }
    int lca(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        u = kthAnc(u, d[u] - d[v]);
        if (u == v) return u;
        for (int i = sz(up); i--;) {
            int ua = up[i][u], va = up[i][v];
            if (ua != va) u = ua, v = va;
        }
        return up[0][u];
    }
    int dist(int a, int b) { return d[a] + d[b] - 2 * d[lca(a, b)]; }
};