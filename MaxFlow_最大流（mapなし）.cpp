const ll MAX_V = 210;

class MaxFlow {
public:

    struct edge {
        ll to;
        ll cap, rev;
    };

    vector<edge> G[MAX_V];
    bool used[MAX_V];

    void add_edge(ll from, ll to, ll cap) {
        G[from].push_back((edge){to, cap, (ll) G[to].size()});
        G[to].push_back((edge){from, 0, (ll) G[from].size() - 1});
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t) return f;
        used[v] = true;
        for (auto&& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) { //sからtへの最大流
        ll flow = 0;
        while (1) {
            rep(i, MAX_V) used[i] = false;
            ll f = dfs(s, t, INF);
            if (f == 0) return flow;
            flow += f;
        }
    }
};