const ll MAX_V = 1001*1001;

class dijkstra_pair {
private:

    struct edge {
        ll to;
        ll cost;
    };
    vector<edge> E[MAX_V];
    ll d[MAX_V];
    ll H, W;

public:

    dijkstra_pair(ll H_in, ll W_in) : H(H_in), W(W_in) {
    }

    void set_E(ll fi, ll fj, ll ti, ll tj, ll cost = 1) {
        E[fi * W + fj].push_back({ti * W + tj, cost});
    }

    ll get_d(ll vi, ll vj) {
        return d[vi * W + vj];
    }

    void calc(ll si, ll sj) {
        ll s = si * W + sj;
        priority_queue <pll, vector<pll>, greater<pll> > que;
        rep(i, MAX_V) d[i] = LINF; //INF
        que.emplace(0LL, s);
        d[s] = 0LL;
        while (!que.empty()) {
            pll p = que.top();
            que.pop();
            ll v = p.second;
            if (d[v] < p.first) continue;
            for (auto&& e : E[v]) {
                if (d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    que.emplace(d[e.to], e.to);
                }
            }
        }
    }
};