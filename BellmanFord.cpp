template<typename T = ll, typename U = ll> class BellmanFord {
public:

    struct edge {
        T from, to;
        U cost;
    };

    ll V; //頂点数（なくてもよい）
    vector<edge> E;
    map<T, U> d;

    BellmanFord(ll V_num = 2510) : V(V_num) {
    }

    void calc(T s) {
        d.clear();
        rep(i, V + 1) d[i] = LINF;
        d[s] = U(0);
        while (1) {
            bool update = false;
            for (auto e : E) {
                //if (d.find(e.from) == d.end()) d[e.from] = LINF;
                //if (d.find(e.to) == d.end()) d[e.to] = LINF;
                if (d[e.from] != LINF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) return;
        }
    }

    bool calc_and_find_negative_loop(T s, T g) {
        d.clear();
        map<T, U> negative;
        rep(i, V + 1) d[i] = LINF;
        d[s] = U(0);

        rep(i, V) {
            bool update = false;
            for (auto e : E) {
                //if (d.find(e.from) == d.end()) d[e.from] = LINF; (map使うときの初期化用)
                //if (d.find(e.to) == d.end()) d[e.to] = LINF;
                if (d[e.from] != LINF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                    if (i == V - 1) negative[e.from] = negative[e.to] = true;
                }
            }
            if (!update) return false;
        }
        return negative[g];
    }

    bool find_any_negative_loop() {
        map<T, U> d_;
        rep(i, V) for (auto e : E) {
            if (d_[e.to] > d_[e.from] + e.cost) {
                d_[e.to] = d_[e.from] + e.cost;
                if (i == V - 1) return true;
            }
        }
        return false;
    }
};