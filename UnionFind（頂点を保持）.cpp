struct UnionFind
{
  vector<int> par;
  vector<vector<int>> vertex;

  UnionFind() {}
  UnionFind(int n) : par(n), vertex(n) { init(n); }

  void init(int n)
  {
    par.resize(n);
    vertex.resize(n);
    iota(all(par), 0);
    for (int i = 0; i < n; i++)
      vertex[i].emplace_back(i);
  }

  int root(int x)
  {
    if (x == par[x])
      return x;
    return par[x] = root(par[x]);
  }

  // size(x) > size(y) ならxの集合にyの集合をmerge
  // size(x) < size(y) ならyの集合にxの集合をmerge
  // size(x) = size(y) は不定
  void unite(int x, int y)
  {
    x = root(x);
    y = root(y);
    if (x == y)
      return;
    if (vertex[x].size() < vertex[y].size())
      swap(x, y);
    par[y] = x;
    while (!vertex[y].empty())
    {
      vertex[x].emplace_back(vertex[y].back());
      vertex[y].pop_back();
    }
  }

  bool same(int x, int y) { return root(x) == root(y); }

  int size(int x) { return vertex[root(x)].size(); }

  vector<int> operator[](int i) { return vertex[root(i)]; }
};