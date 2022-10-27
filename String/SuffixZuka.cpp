struct SuffixArray {
    string S;
    vector<int> sa;
    vector<int> lcp;

    SuffixArray(string &s) {
        S = s;
        s += '$';
        int n = s.length();
        vector<int> p(n), c(n);
        vector<pair<char, int>> v(n);

        for (int i = 0; i < n; i++)
            v[i] = {s[i], i};

        sort(v.begin(), v.end());

        for (int i = 0; i < n; i++)
            p[i] = v[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (v[i].first == v[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }

        int k = 0;
        while ((1 << k) < n) {
            for (int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;

            vector<int> cnt(n), pos(n);
            vector<int> newP(n), newC(n);

            for (auto &it: c) cnt[it]++;
            for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
            for (auto &it: p) newP[pos[c[it]]++] = it;
            p = newP;

            newC[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                if (cur == prev)
                    newC[p[i]] = newC[p[i - 1]];
                else
                    newC[p[i]] = newC[p[i - 1]] + 1;
            }
            c = newC;
            k++;
        }
        sa = p;

        k = 0;
        lcp = vector<int>(n);
        for (int i = 0; i < n - 1; i++) {
            int pi = c[i];
            int j = p[pi - 1];
            while (s[i + k] == s[j + k])
                k++;
            lcp[pi] = k;
            k = max(0LL, k - 1);
        }
    }

    vector<int> getSa() const {
        return sa;
    }

    vector<int> getLCP() const {
        return lcp;
    }

    int count(string &t) {
        if (t.length() >= sa.size())
            return 0;

        int s = 1, e = sa.size() - 1, mid, L = -1, R = -1;
        while (s <= e) {
            mid = (s + e) >> 1;
            string x = S.substr(sa[mid], min(sz(t), sz(S) - sa[mid]));
            if (x == t)
                L = mid, e = mid - 1;
            else if (x > t)
                e = mid - 1;
            else
                s = mid + 1;
        }
        if (L == -1)
            return 0;
        s = 1, e = sa.size() - 1;
        while (s <= e) {
            mid = (s + e) >> 1;
            string x = S.substr(sa[mid], min(sz(t), sz(S) - sa[mid]));
            if (x == t)
                R = mid, s = mid + 1;
            else if (x > t)
                e = mid - 1;
            else
                s = mid + 1;
        }
        return R - L + 1;
    }
};
