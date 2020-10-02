struct SCC
{
  int V;
  vector<vector<int>> G, Gr;
  vector<int> comp, order, used;

  SCC(int V_) : V(V_), G(V_), Gr(V_), comp(V_, -1), used(V_) {}

  void add_E(int a, int b)
  {
    G[a].emplace_back(b);
    Gr[b].emplace_back(a);
  }

  // 番号はトポロジカル順
  int operator[](int k) { return comp[k]; }

  void dfs(int idx)
  {
    if (used[idx])
      return;
    used[idx] = true;
    for (int to : G[idx])
      dfs(to);
    order.emplace_back(idx);
  }

  void rdfs(int idx, int cnt)
  {
    if (comp[idx] != -1)
      return;
    comp[idx] = cnt;
    for (int to : Gr[idx])
      rdfs(to, cnt);
  }

  // 多重辺が生えるので注意
  vector<vector<int>> build()
  {
    vector<vector<int>> res;
    for (int i = 0; i < G.size(); i++)
      dfs(i);
    reverse(begin(order), end(order));
    int ptr = 0;
    for (int i : order)
      if (comp[i] == -1)
        rdfs(i, ptr), ptr++;

    res.resize(ptr);
    for (int i = 0; i < G.size(); i++)
    {
      for (auto &to : G[i])
      {
        int x = comp[i], y = comp[to];
        if (x == y)
          continue;
        res[x].push_back(y);
      }
    }
    return res;
  }
};