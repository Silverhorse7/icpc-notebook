typedef long long ll;
const int N = 1e6 + 5;
int n;

struct segment {
    struct item {
        ll L, R, good;
    };

    item merge(item a, item b) {
        return {a.L + b.L - min(a.L, b.R), a.R + b.R - min(a.L, b.R), a.good + b.good + min(a.L, b.R)};
    }

    ll size;
    vector<item> seg;

    void init(ll n) {
        size = 1;
        while (size < n)size *= 2;
        seg.resize(2 * size);

    }

    void build(vector<char> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                if (a[lx] == ')')seg[x] = {0, 1, 0};
                else
                    seg[x] = {1, 0, 0};
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);//changeable
    }

    void build(vector<char> &a) {
        build(a, 0, 0, size);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1)//size of segment equal to 1
        {
            seg[x] = {v, 1};
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);

        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        seg[x] = merge(seg[2 * x + 1], seg[2 * x + 2]);//changable
    }

    void update(int i, int v) {
        update(i, v, 0, 0, size);
    }

    item query(int l, int r, int x, int lx, int rx) {
        if (lx >= r or l >= rx) return {0, 0,0};//changable too
        if (lx >= l and rx <= r) return seg[x];
        int m = (lx + rx) / 2;
        item s1 = query(l, r, 2 * x + 1, lx, m);
        item s2 = query(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);//changable
    }

    item query(int l, int r) {//Sum,min,max,....
        return query(l, r, 0, 0, size);
    }

};
