/* 
Pass maxn as LARGER than actual max size 
Ensure all array inputs are in [0, MOD)
Create global instance of struct NTT
*/

#include "../mint.h"

using i32 = int32_t;
using i64 = int64_t;
template <i32 maxn>
struct NTT {
    constexpr static i32 lg2(i32 n) { 
        if (n == 1) return 0;
        return 32 - __builtin_clz(n - 1); 
    }
    
    const static i32 MAXN = 1 << lg2(maxn), MOD = 998244353, root = 3;
    i32 rev[MAXN], rt[MAXN];

    i32 mul(i32 a, i32 b) { return (i64)a * b % MOD; }
    i32 sub(i32 a, i32 b) { return b > a ? a - b + MOD : a - b; }
    i32 add(i32 a, i32 b) { return a + b >= MOD ? a + b - MOD : a + b; }

    i32 binExp(i32 base, i64 exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        rt[1] = 1;
        for (i32 k = 1; k < lg2(MAXN); k++) {
            i32 z[] = {1, binExp(root, (MOD - 1) >> (k + 1))};
            for (i32 i = (1 << k); i < 2 << k; i++)
                rt[i] = mul(rt[i / 2], z[i & 1]);
        }
    }
    void ntt(i32 *a, i32 n) {
        for (i32 i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (i32 i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (i32 k = 1; k < n; k *= 2)
            for (i32 i = 0; i < n; i += 2 * k)
                for (i32 j = 0; j < k; j++) {
                    i32 z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    i32 in[2][MAXN];
    template<typename T>
    vector<T> multiply(const vector<T> &a, const vector<T> &b) {
        if (a.empty() || b.empty())
            return {};
        int size = sz(a) + sz(b) - 1, n = 1 << lg2(size);
        fill(in[0], in[0] + n, 0), fill(in[1], in[1] + n, 0);
        copy(all(a), in[0]), copy(all(b), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<T>(in[0], in[0] + size);
    }
};