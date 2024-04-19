const int N = 5e5 + 10, LOGN = 18;
int L[N * LOGN], R[N * LOGN], ST[N * LOGN];
int nodeid = 0;
int update(int pos, int l, int r, int val, int id) {
    if (pos < l or pos > r) return id;
    int ID = ++nodeid, m = (l + r) / 2;
    if (l == r) return (ST[ID] = val, ID);
    L[ID] = update(pos, l, m, val, L[id]);
    R[ID] = update(pos, m + 1, r, val, R[id]);
    return (ST[ID] = ST[L[ID]] + ST[R[ID]], ID);
}

int query(int ql, int qr, int l, int r, int id) {
    if (ql > r or qr < l) return 0;
    if (ql <= l and r <= qr) return ST[id];
    int m = (l + r) / 2;
    return (query(ql, qr, l, m, L[id])) + query(ql, qr, m + 1, r, R[id]);
}

// searches lower_bound of k in str - strl
int descent(int l, int r, int k, int stl, int str) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    int leftVal = ST[L[str]] - ST[L[stl]];

    if (leftVal >= k) {
        return descent(l, mid, k, L[stl], L[str]);
    } else {
        return descent(mid + 1, r, k - leftVal, R[stl], R[str]);
    }
}