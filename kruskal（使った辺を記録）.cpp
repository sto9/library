struct UnionFind
{
  vector<int> par, rank_;

  UnionFind() {}
  UnionFind(int n) : par(n), rank_(n, 0) { iota(begin(par), end(par), 0); }

  int root(int x) { return par[x] == x ? x : par[x] = root(par[x]); }

  bool same(int x, int y) { return root(x) == root(y); }

  void unite(int x, int y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
      return;

    if (rank_[x] < rank_[y])
    {
      par[x] = y;
    }
    else
    {
      par[y] = x;
      if (rank_[x] == rank_[y])
        rank_[x]++;
    }
  }
};

template <typename T>
struct kruskal
{
  UnionFind uf;
  kruskal(int n = 200010) : uf(n) {}

  struct edge
  {
    int u, v;
    T cost;
    int num;
  };

  vector<edge> E;
  set<int> used_num;
  void add_E(int s, int t, T w, int i) { E.push_back({s, t, w, i}); }

  T calc()
  {
    sort(E.begin(), E.end(), [](edge &e1, edge &e2) { return e1.cost < e2.cost; });
    T res = 0;
    for (auto e : E)
    {
      if (!uf.same(e.u, e.v))
      {
        uf.unite(e.u, e.v);
        res += e.cost;
        used_num.insert(e.num);
      }
    }
    return res;
  }

  bool used(int i) { return used_num.count(i); }
};