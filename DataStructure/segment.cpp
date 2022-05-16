	struct segment {
    struct item {//basically things u care about 
        long long segm, pref, suff, sum;
    };
    static item merge(item a, item b) { //how u want the parent node to prioritize 
        return {max({a.segm, b.segm, a.suff + b.pref}), max({a.pref, a.sum + b.pref}), max({b.suff, b.sum + a.suff}),
                a.sum + b.sum};
    }

    static item single(long long v) { //the value u want if u reached the ground (single node)
        if (v > 0)return {v, v, v, v};
        else
            return {0, 0, 0, v};
    }
    item netural_element={0,0,0,0};
    long long size=1;
    vector<item> seg;

    void init(long long n) {
        while (size < n)size *= 2;
        seg.resize(2 * size, {0, 0, 0, 0});

    }

    void build(vector<long long> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                seg[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void build(vector<long long> &a) {
        build(a, 0, 0, size);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1)//size of segment equal to 1
        {
            seg[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);

        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);
    }

    void update(int i, int v) {
        update(i, v, 0, 0, size);
    }

    item query(int l, int r, int x, int lx, int rx) {
        if (lx >= r or l >= rx) return netural_element;
        if (lx >= l and rx <= r) return seg[x];
        int m = (lx + rx) / 2;
        item s1 = query(l, r, 2 * x + 1, lx, m);
        item s2 = query(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    item query(int l, int r) {
        return query(l, r, 0, 0, size);
    }

};
