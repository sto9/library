class UnionFind {
public:
    vector<int> par, rank_;

    UnionFind(int n = 200010) : par(n), rank_(n, 0) {
        rep(i, n) par[i] = i;
    }

    int root(int x) {
        return par[x] == x ? x : par[x] = root(par[x]);
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;

        if (rank_[x] < rank_[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
};