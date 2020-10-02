template <typename T = ll>
struct Tree
{
  int V;
  using P = pair<int, ll>;
  vector<vector<P>> E;
  vector<int> par;
  vector<int> depth;
  vector<int> sub;
  vector<T> dist;
  vector<vector<int>> par_double;

  Tree(int V_) : V(V_)
  {
    E.resize(V);
    depth.resize(V);
    dist.resize(V);
    sub.resize(V);
  }

  void add_E(int a, int b, T w = T(1), bool direction = false)
  {
    E[a].push_back(make_pair(b, w));
    if (!direction)
      E[b].push_back(make_pair(a, w));
  }

  int dfs(int p, int d, T w)
  {
    sub[p] = 1;
    for (auto pi : E[p])
    {
      int v = pi.first;
      if (par[p] == v)
        continue;
      par[v] = p;
      depth[v] = d + 1;
      dist[v] = w + pi.second;
      sub[p] += dfs(v, depth[v], dist[v]);
    }
    return sub[p];
  }

  void make_tree(int root = 0)
  {
    calculated = false;
    par.assign(V, -1);
    par_double.assign(V, vector<int>(25));
    depth[root] = 0;
    dist[root] = T(0);
    dfs(root, 0, 0);
  }

  bool calculated;
  void calc_double()
  {
    for (int i = 0; i < V; i++)
      par_double[i][0] = par[i];

    for (int k = 0; k < 24; k++)
    {
      for (int i = 0; i < V; i++)
      {
        if (par_double[i][k] == -1)
          par_double[i][k + 1] = -1;
        else
          par_double[i][k + 1] = par_double[par_double[i][k]][k];
      }
    }
  }

  int getLCA(int a, int b)
  {
    if (!calculated)
    {
      calc_double();
      calculated = true;
    }
    if (a == b)
      return a;
    if (depth[a] < depth[b])
      swap(a, b);
    for (int k = 24; k >= 0; k--)
    {
      if (par_double[a][k] != -1 && depth[par_double[a][k]] >= depth[b])
        a = par_double[a][k];
    }
    if (a == b)
      return a;
    for (int k = 24; k >= 0; k--)
    {
      if (par_double[a][k] != -1 && par_double[a][k] != par_double[b][k])
      {
        a = par_double[a][k];
        b = par_double[b][k];
      }
    }
    return par_double[a][0];
  }

  int length(int a, int b)
  {
    return depth[a] + depth[b] - 2 * depth[getLCA(a, b)];
  }

  int distance(int a, int b)
  {
    return dist[a] + dist[b] - 2 * dist[getLCA(a, b)];
  }

  T diameter(int &a, int &b)
  {
    T Max(-1);
    for (int i = 0; i < V; i++)
    {
      if (Max < distance(0, i))
        Max = distance(0, i), a = i;
    }
    for (int i = 0; i < V; i++)
    {
      if (Max < distance(a, i))
        Max = distance(a, i), b = i;
    }
    return Max;
  }

  T diameter()
  {
    int a, b;
    return diameter(a, b);
  }

  int diameter_l(int &a, int &b)
  {
    int Max = -1;
    for (int i = 0; i < V; i++)
    {
      if (Max < length(0, i))
        Max = length(0, i), a = i;
    }
    for (int i = 0; i < V; i++)
    {
      if (Max < length(a, i))
        Max = length(a, i), b = i;
    }
    return Max;
  }

  int diameter_l()
  {
    int a, b;
    return diameter_l(a, b);
  }
};