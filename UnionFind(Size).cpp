class UnionFind
{
private:
  vector<int> par, sizes;

public:
  UnionFind(int n = 200010) : par(n), sizes(n, 1)
  {
    rep(i, n) par[i] = i;
  }

  int root(int x)
  {
    if (x == par[x])
      return x;
    return par[x] = root(par[x]);
  }

  void unite(int x, int y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
      return;
    if (sizes[x] < sizes[y])
      swap(x, y);
    par[y] = x;
    sizes[x] += sizes[y];
  }

  bool same(int x, int y)
  {
    return root(x) == root(y);
  }

  int size(int x)
  {
    return sizes[root(x)];
  }
};