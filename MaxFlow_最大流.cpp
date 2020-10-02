template <typename T = int, typename U = ll> class MaxFlow {
public:

    struct edge {
        T to;
        U cap, rev;
    };

    map<T, vector<edge> > G;
    map<T, bool> used;

    void add_edge(T from, T to, U cap) {
        G[from].push_back((edge){to, cap, G[to].size()});
        G[to].push_back((edge){from, 0, (U) G[from].size() - 1});
    }

    U dfs(T v, T t, U f) {
        if (v == t) return f;
        used[v] = true;
        for (auto&& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                U d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    U max_flow(T s, T t) { //sからtへの最大流
        U flow = 0;
        while (1) {
            used.clear();
            U f = dfs(s, t, INF);
            if (f == 0) return flow;
            flow += f;
        }
    }
};